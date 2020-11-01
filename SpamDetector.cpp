#include "HashMap.hpp"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>

#define NUM_OF_ARGS 3
#define NUM_OF_COLS 2

#define NUM_OF_ARGS_MSG "Usage: SpamDetector <database path> <message path> <threshold>"
#define INVALID_MSG "Invalid input"
#define COMMA ","
#define SPACE_CHAR ' '
#define SPAM "SPAM"
#define NOT_SPAM "NOT_SPAM"
#define ENTER '\r'

/**
 * This function receives a string and checks if it contains more than 1 comma
 * @param line- the string to check
 */
void findDoubleComma(const std::string &line)
{
    std::size_t found = line.find(COMMA);
    found = line.find(COMMA, found + 1);
    if (found != std::string::npos)
    {
        throw std::invalid_argument(INVALID_MSG);
    }
}

/**
 * This function receives a string and checks if it contains only digits
 * @param num - the string to check
 * @return true- if the string contains only digits, false-otherwise
 */
bool isNumber(std::string &num)
{
    if (num[num.length() - 1] == ENTER)
    {
        num = num.erase(num.length() - 1);
    }
    for (char ch : num)
    {
        if (isdigit(ch) == 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * This function converts chars in string into lowercase letters
 * @param data - the string to convert
 */
void makeLower(std::string &data)
{
    std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c)
    { return std::tolower(c); });
}


/**
 * Parser for the database file
 * @param database - the file to parse
 * @param hashMap - the map to insert the data from the database file
 */
void databaseParser(std::ifstream &database, HashMap<std::string, int> &hashMap)
{
    if (!database.is_open())
    {
        throw std::invalid_argument(INVALID_MSG);
    }
    std::string line;
    std::vector<std::string> parameters;
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{COMMA};
    //reads one line at a time
    while (std::getline(database, line))
    {
        //check if the the line is empty or contains only spaces
        if (line.empty() || line.find_first_not_of(SPACE_CHAR) == std::string::npos)
        {
            database.close();
            throw std::invalid_argument(INVALID_MSG);
        }

        //exit if there is more than 1 comma
        findDoubleComma(line);
        tokenizer tok{line, sep};
        parameters.assign(tok.begin(), tok.end());

        //check if the line contains exactly 2 columns
        if (parameters.size() != NUM_OF_COLS)
        {
            database.close();
            throw std::invalid_argument(INVALID_MSG);
        }

        //check if the second argument is a number
        if (!isNumber(parameters[1]))
        {
            database.close();
            throw std::invalid_argument(INVALID_MSG);
        }

        std::string badWord = parameters[0];
        int score = std::stoi(parameters[1]);

        //check if the given score is within the given range
        if (score < 0)
        {
            database.close();
            throw std::invalid_argument(INVALID_MSG);
        }

        //convert every char to lower case
        makeLower(badWord);

        //finally after validating all arguments, insert the line to the hashMap
        hashMap.insert(badWord, score);
    }
    database.close();
}

/**
 * Parser for the message file
 * @param messageFile - the message file to read
 * @return a string with the message file content
 */
std::string messageParser(std::ifstream &messageFile)
{
    if (!messageFile.is_open())
    {
        throw std::invalid_argument(INVALID_MSG);
    }
    std::string line;
    std::string message;
    while (std::getline(messageFile, line))
    {
        message += line + ENTER;
    }

    //convert every char to lower case
    makeLower(message);
    messageFile.close();
    return message;
}

/**
 * This function checks that the threshold argument received is valid
 * @param strThreshold - the threshold argument received
 * @return an int type with the received threshold value
 */
int thresholdParser(std::string &strThreshold)
{
    if (!isNumber(strThreshold))
    {
        throw std::invalid_argument(INVALID_MSG);
    }
    int threshold = std::stoi(strThreshold);

    if (threshold <= 0)
    {
        throw std::invalid_argument(INVALID_MSG);
    }
    return threshold;
}

/**
 * This function compares the message to the hashMap database and decides if the message is spam
 * or not
 * @param message - the message to check is spam
 * @param hashMap - the hashMap object containing the received database
 * @param threshold - the score from which the message considers a spam
 */
void isSpam(const std::string &message, const HashMap<std::string, int> &hashMap, int threshold)
{
    int messageScore = 0;
    HashMap<std::string, int>::const_iterator it = hashMap.begin();
    while (it != hashMap.end())
    {

        //save the bad word to search for, and its matching score
        std::string badWord = (*it).first;
        int score = (*it).second;

        //search the message, and update the total message score
        std::size_t found = message.find(badWord);
        while (found != std::string::npos)
        {
            messageScore += score;
            found = message.find(badWord, found + 1);
        }
        ++it;
    }
    if (messageScore >= threshold)
    {
        std::cout << SPAM << std::endl;
    }
    else
    {
        std::cout << NOT_SPAM << std::endl;
    }
}


int main(int argc, char *argv[])
{
    if (argc != NUM_OF_ARGS + 1)
    {
        std::cerr << NUM_OF_ARGS_MSG << std::endl;
        return EXIT_FAILURE;
    }

    //if the files does not exists- exit failure
    if (!boost::filesystem::exists(argv[1]) || !boost::filesystem::exists(argv[2]))
    {
        std::cerr << INVALID_MSG << std::endl;
        return EXIT_FAILURE;
    }

    //if one or both of the files are empty- print "NOT_SPAM"
    if (boost::filesystem::is_empty(argv[1]) || boost::filesystem::is_empty(argv[2]))
    {
        std::cout << NOT_SPAM << std::endl;
        return EXIT_SUCCESS;
    }
    try
    {
        std::string strThreshold = argv[3];
        int threshold = thresholdParser(strThreshold);

        HashMap<std::string, int> hashMap;

        //open and parse the database, close after
        std::ifstream database(argv[1]);
        databaseParser(database, hashMap);

        //open and parse messageFile, close after
        std::ifstream messageFile(argv[2]);
        std::string message = messageParser(messageFile);

        isSpam(message, hashMap, threshold);
    }
    catch (...)
    {
        std::cerr << INVALID_MSG << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

