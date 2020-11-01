#include <vector>
#include <iostream>
#include <tuple>

#define INIT_CAPACITY 16
#define EMPTY_SIZE 0
#define FAIL -1
#define UPPER_LOAD_FACTOR 0.75
#define LOWER_LOAD_FACTOR 0.25
#define INVALID_ARG_MSG "Invalid arguments- vectors with different size"
#define INVALID_KEY_MSG "Invalid argument- key is not in the map"
#define INCREASE_DECREASE_FACTOR 2


//////////////////////////////// Bucket object //////////////////////////////////////




/**
 * A Buckets object class
 * @tparam KeyT- the generic type for the map key values
 * @tparam ValueT- the generic type for the map values
 */
template<class KeyT, class ValueT>
class Buckets
{
public:
    /**
     * Constructor for Buckets class
     */
    Buckets();

    /**
     * This method adds an element to the end of the bucket
     * @param key- the map key value
     * @param val- the value to insert the map according to the giving key
     */
    void addToBucket(KeyT key, ValueT val);

    /**
     * This function replaces the bucket element with the same key to the new value
     * @param key- the key to replace its value
     * @param val- the value to replace for the giving key
     */
    void replaceVal(KeyT key, ValueT val);

    /**
    * This function checks if the bucket contains the giving key
    * @param key- the key to search for in the bucket
    * @return -1 if the key is not in the bucket, the key's index otherwise
    */
    int containKey(KeyT key);

    /**
    * This function checks if the bucket is empty or not
    * @return- true if the bucket is empty or false otherwise
    */
    bool isBucketEmpty();

    /**
     * A getter function for the inventory property of the Buckets object
     * @return the inventory property of the Buckets object
     */
    std::vector<std::pair<KeyT, ValueT>> &getInventory();

    /**
     * This function cleans the bucket from all its elements if not empty
     */
    void clearBucket();

    /**
    * This function removes the value associated with the giving key
    * @param key- the key to remove its value
    */
    void erase(KeyT key);

protected:
    std::vector<std::pair<KeyT, ValueT>> inventory;
    bool emptyBucket;
};

/**
 * Constructor for Buckets class
 * @param key- the map key value
 * @param val- the value to insert the map according to the giving key
 */
template<class keyT, class valueT>
Buckets<keyT, valueT>::Buckets() : emptyBucket(true)
{}

/**
 * This method adds an element to the end of the bucket
 * @param key- the map key value
 * @param val- the value to insert the map according to the giving key
 */
template<class keyT, class valueT>
void Buckets<keyT, valueT>::addToBucket(keyT key, valueT val)
{
    int key_index = containKey(key);
    if (key_index != FAIL)
    {
        this->inventory[key_index] = std::make_pair(key, val);
    }
    else
    {
        inventory.push_back(std::make_pair(key, val));
        if (isBucketEmpty())
        {
            this->emptyBucket = false;
        }
    }
}

/**
* This function checks if the bucket contains the giving key
* @param key- the key to search for in the bucket
* @return -1 if the key is not in the bucket, the key's index otherwise
*/
template<class keyT, class valueT>
int Buckets<keyT, valueT>::containKey(keyT key)
{
    if (isBucketEmpty())
    {
        return FAIL;
    }
    for (typename std::vector<std::pair<keyT, valueT>>::size_type i = 0; i < inventory.size(); i++)
    {
        if ((this->inventory[i]).first == key)
        {
            return i;
        }
    }
    return FAIL;
}

/**
 * This function checks if the bucket is empty or not
 * @return- true if the bucket is empty or false otherwise
 */
template<class keyT, class valueT>
bool Buckets<keyT, valueT>::isBucketEmpty()
{
    return this->emptyBucket;
}

/**
 * A getter function for the inventory property of the Buckets object
 * @return the inventory property of the Buckets object
 */
template<class keyT, class valueT>
std::vector<std::pair<keyT, valueT>> &Buckets<keyT, valueT>::getInventory()
{
    return this->inventory;
}

/**
 * This function cleans the bucket from all its elements if not empty
 */
template<class keyT, class valueT>
void Buckets<keyT, valueT>::clearBucket()
{
    if (!isBucketEmpty())
    {
        this->inventory.erase(this->inventory.begin(), this->inventory.end());
    }
    this->emptyBucket = true;
}

/**
 * This function replaces the bucket element with the same key to the new value
 * @param key- the key to replace its value
 * @param val- the value to replace for the giving key
 */
template<class keyT, class valueT>
void Buckets<keyT, valueT>::replaceVal(keyT key, valueT val)
{
    // use of containKey only to find the key's index, the map handles the case the key is not in
    // the map
    int bucketInd = containKey(key);
    this->inventory[bucketInd] = std::make_pair(key, val);
}

/**
 * This function removes the value associated with the giving key
 * @param key- the key to remove its value
 */
template<class keyT, class valueT>
void Buckets<keyT, valueT>::erase(keyT key)
{
    for (int i = 0; i < (int) inventory.size(); i++)
    {
        if ((inventory[i]).first == key)
        {
            inventory.erase(inventory.begin() + i);
        }
    }
    if (inventory.size() == EMPTY_SIZE)
    {
        this->emptyBucket = true;
    }
}


//////////////////////////////// HashMap object //////////////////////////////////////

/**
 * A HashMap object class
 * @tparam KeyT- the generic type for the map key values
 * @tparam ValueT- the generic type for the map values
 */
template<class KeyT, class ValueT>
class HashMap
{
public:
    //////////////////////////////// const_iterator object ////////////////////////////////
    /**
     * A const_iterator object class
     */
    class const_iterator
    {
    private:
        Buckets<KeyT, ValueT> *mapToIter;
        int bucketIndex;
        int mapIndex;
        int capacity;
    public:
        typedef const_iterator self_type;
        typedef int difference_type;
        typedef std::pair<KeyT, ValueT> value_type;
        typedef std::pair<KeyT, ValueT> *pointer;
        typedef std::pair<KeyT, ValueT> &reference;
        typedef std::forward_iterator_tag iterator_category;

        /**
         * The constructor for const_iterator class
         * @param mapToIter- the hashMap to iter
         * @param capacity- the capacity property of the given hashMap
         */
        explicit const_iterator(Buckets<KeyT, ValueT> *mapToIter = nullptr,
                                int capacity = EMPTY_SIZE,
                                bool isEndCalled = false) : mapToIter(mapToIter),
                                                            bucketIndex(EMPTY_SIZE),
                                                            capacity(capacity)
        {
            if (isEndCalled)
            {
                mapIndex = this->capacity;
            }
            else
            {
                bool hasMoreValues = false;
                for (int i = 0; i < capacity; i++)
                {
                    if (!mapToIter[i].isBucketEmpty())
                    {
                        hasMoreValues = true;
                        mapIndex = i;
                        break;
                    }
                }
                if (!hasMoreValues)
                {
                    mapIndex = this->capacity;
                }
            }
        }

        /**
         * This function returns a const_iterator of the next element to iterate
         * @return a const_iterator of the next element to iterate
         */
        self_type &operator++()
        {
            // if the bucket contains more elements to iter, increase bucketIndex
            if (bucketIndex < (int) mapToIter[mapIndex].getInventory().size() - 1)
            {
                bucketIndex++;
                return *this;
            }
                // else, need to move along the map elements
            else
            {
                this->bucketIndex = 0;
                for (int i = mapIndex + 1; i < capacity; i++)
                {
                    if (!mapToIter[i].isBucketEmpty())
                    {
                        this->mapIndex = i;
                        return *this;
                    }
                }
                this->mapIndex = capacity;
                return *this;
            }
        }

        /**
         * This function is a postfix increment
         * @return a const_iterator
         */
        self_type operator++(int)
        {
            const_iterator toReturn = (*this);
            ++(*this);
            return toReturn;
        }

        /**
         * An equality comparison operator for const_iterator
         * @param it- the const_iterator to compare
         * @return true- if the objects are equal, false otherwise
         */
        bool operator==(const_iterator const &it) const
        {
            return this->mapIndex == it.mapIndex && this->bucketIndex == it.bucketIndex;
        }

        /**
         An inequality comparison operator for const_iterator
         * @param it- the const_iterator to compare
         * @return true- if the objects are not equal, false otherwise
         */
        bool operator!=(const_iterator const &it) const
        {
            return this->mapIndex != it.mapIndex || this->bucketIndex != it.bucketIndex;
        }

        /**
         * This function dereference's the const_iterator as an rvalue
         * @return an std::pair<keyT, valueT> of the const_iterator value
         */
        reference operator*() const
        {
            return this->mapToIter[this->mapIndex].getInventory()[this->bucketIndex];
        }

        /**
         * This function dereference's the const_iterator as an rvalue
         * @return an std::pair<keyT, valueT> of the const_iterator value
         */
        pointer operator->() const
        {
            return &this->mapToIter[this->mapIndex].getInventory()[this->bucketIndex];
        }
    };

    /**
     * The default constructor for HashMap class
     * @tparam keyT- the generic type for the map key values
     * @tparam valueT- the generic type for the map values
     */
    HashMap();

    /**
     * A constructor for HashMap class that receives 2 vectors- one for keys and one for values and
     * inserts them to the hashMap
     * @param key- the keys vector to insert
     * @param value - the values vector to insert
     */
    HashMap(std::vector<KeyT> key, std::vector<ValueT> value);

    /**
     * This is a copy constructor for HashMap object
     * @param mapToCopy- the HashMap object to copy from
     */
    HashMap(const HashMap &mapToCopy);

    /**
     * This is a move constructor for HashMap object
     * @param mapToMove- - the HashMap object to move from
     */
    HashMap(HashMap && mapToMove) noexcept;

    /**
     * The destructor for HashMap class
     */
    ~HashMap();

    /**
     * A getter function for the size property of the HashMap object
     * @return the size property of the HashMap object
     */
    int size() const;

    /**
     * A getter function for the capacity property of the HashMap object
     * @return the capacity property of the HashMap object
     */
    int capacity() const;

    /**
     * This function determine if the map is empty or not
     * @return- true if the map is empty, false otherwise
     */
    bool empty() const;

    /**
     * This function inserts an element- pair of the received key and value to the Map
     * @param key- the key to insert to the map
     * @param val- the value associated with the giving key
     * @return true if the insert was successful or false otherwise
     */
    bool insert(KeyT key, ValueT val);

    /**
    * This function checks if the map contains the giving key
    * @param key- the key to search for in the map
    * @return false if the key is not in the map, true otherwise
     */
    bool containsKey(const KeyT &key) const;

    /**
     * This function returns the valueT type value associated with the giving key
     * @param key- the key to return its associated value
     * @return the valueT type value associated with the giving key
     */
    ValueT &at(const KeyT &key) const;

    /**
     * This function removes the value associated with the giving key
     * @param key- the key to remove its value
     * @return- true if the removal was successful, false otherwise
     */
    bool erase(const KeyT &key);

    /**
     * This function returns this HashMap current loadFactor
     * @return this HashMap current loadFactor
     */
    double getLoadFactor() const;

    /**
     * This function returns the bucket size of the giving key
     * @param key- the key of the wanted bucket
     * @return-the bucket size of the giving key
     */
    int bucketSize(const KeyT &key) const;

    /**
     * This function receives a key and returns the index of the matching bucket
     * @param key- the key to hash
     * @return- the index of the matching bucket
     */
    int bucketIndex(const KeyT &key) const;

    /**
     * This function cleans the hashMap from all its elements
     */
    void clear();


    /**
     * This function returns an iterator points to the last element of the map
     * @return an iterator points to the last element of the map
     */
    const_iterator end() const;

    /**
     * This function returns an iterator points to the first element of the map
     * @return an iterator points to the first element of the map
     */
    const_iterator begin() const;

    /**
     * This function returns a const iterator points to the last element of the map
     * @return a const iterator points to the last element of the map
     */
    const const_iterator cend() const;

    /**
     * This function returns a const iterator points to the first element of the map
     * @return a const iterator points to the first element of the map
     */
    const const_iterator cbegin() const;

    /**
     * This function is a const brackets indexing operator for HashMap object
     * @param key- the key to access it's value
     * @return the value associated with the giving key
     */
    ValueT operator[](const KeyT key) const;

    /**
     * This function is a brackets indexing operator for HashMap object
     * @param key- the key to access it's value
     * @return the value associated with the giving key
     */
    ValueT &operator[](const KeyT key);

    /**
     * This function is a comparison operator for HashMap
     * @param m- the HashMap ro compare to
     * @return true, if the given map is equal to this map, or false otherwise
     */
    bool operator==(const HashMap &m) const;

    /**
     * This function is a comparison operator for HashMap
     * @param m- the HashMap ro compare to
     * @return false, if the given map is equal to this map, or true otherwise
     */
    bool operator!=(const HashMap &m) const;

    /**
     * This function is a copy assignment operator for HashMap
     * @param m- the map to assign
     * @return the HashMap object after assignment
     */
    HashMap &operator=(const HashMap &m);

    /**
     * This function is a move assignment operator for HashMap
     * @param m- the map to assign
     * @return the HashMap object after assignment
     */
    HashMap &operator=(HashMap && m) noexcept;

protected:
    int mapCapacity;
    int mapSize;
    bool runOverDuplicate;
    Buckets<KeyT, ValueT> *theMap;

    /**
    * This function receives a key and returns its hashing value
    * @param key- the key to hash
    * @return- the hash value of the giving key
    */
    int getHashIndex(KeyT key, int capacity) const;

    /**
     * This function rehashes the Map into a new received size
     * @param newSize- the new size of the map
     */
    void rehash(int newSize);


};

/**
 * The default constructor for HashMap class
 * @tparam KeyT- the generic type for the map key values
 * @tparam ValueT- the generic type for the map values
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap() : mapCapacity(INIT_CAPACITY), mapSize(EMPTY_SIZE), runOverDuplicate
        (false)
{
    theMap = new(std::nothrow) Buckets<KeyT, ValueT>[mapCapacity]();
    if (this->theMap == nullptr)
    {
        throw std::bad_alloc();
    }
}

/**
 * A constructor for HashMap class that receives 2 vectors- one for keys and one for values and
 * inserts them to the hashMap
 * @param key- the keys vector to insert
 * @param value - the values vector to insert
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(std::vector<KeyT> key, std::vector<ValueT> value) :
        mapCapacity(INIT_CAPACITY), mapSize(EMPTY_SIZE), runOverDuplicate(true)
{
    // if the mapSize of the vectors does not match-exception
    if (key.size() != value.size())
    {
        throw std::invalid_argument(INVALID_ARG_MSG);
    }

    theMap = new(std::nothrow) Buckets<KeyT, ValueT>[mapCapacity]();
    if (this->theMap == nullptr)
    {
        throw std::bad_alloc();
    }
    //insert each pair of key and value while the runOverDuplicate flag is on- if a key is
    // already n the map, run it over
    for (int i = 0; i < (int) key.size(); i++)
    {
        insert(key[i], value[i]);
    }
    this->runOverDuplicate = false;
}

/**
 * A getter function for the size property of the HashMap object
 * @return the size property of the HashMap object
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::size() const
{
    return this->mapSize;
}

/**
 * A getter function for the capacity property of the HashMap object
 * @return the capacity property of the HashMap object
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::capacity() const
{
    return this->mapCapacity;
}

/**
 * This function determine if the map is empty or not
 * @return- true if the map is empty, false otherwise
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::empty() const
{
    return this->mapSize == EMPTY_SIZE;
}

/**
 * This function returns this HashMap current loadFactor
 * @return this HashMap current loadFactor
 */
template<class KeyT, class ValueT>
double HashMap<KeyT, ValueT>::getLoadFactor() const
{
    return ((double) this->mapSize) / ((double) this->mapCapacity);
}

/**
* This function checks if the map contains the giving key
* @param key- the key to search for in the map
* @return false if the key is not in the map, true otherwise
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::containsKey(const KeyT &key) const
{
    int hashIndex = getHashIndex(key, capacity());
    return theMap[hashIndex].containKey(key) != FAIL;
}

/**
 * This function returns the bucket size of the giving key
 * @param key- the key of the wanted bucket
 * @return-the bucket size of the giving key
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucketSize(const KeyT &key) const
{
    int hashIndex = getHashIndex(key, capacity());
    if (theMap[hashIndex].containKey(key) == FAIL)
    {
        throw std::invalid_argument(INVALID_KEY_MSG);
    }
    return this->theMap[hashIndex].getInventory().size();
}

/**
 * This function receives a key and returns the index of the matching bucket
 * @param key- the key to hash
 * @return- the index of the matching bucket
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucketIndex(const KeyT &key) const
{
    if (theMap[getHashIndex(key, capacity())].containKey(key) == FAIL)
    {
        throw std::invalid_argument(INVALID_KEY_MSG);
    }
    return getHashIndex(key, capacity());
}

/**
 * This function cleans the hashMap from all its elements
 */
template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::clear()
{
    for (int i = 0; i < capacity(); i++)
    {
        this->theMap[i].clearBucket();
    }
    this->mapSize = EMPTY_SIZE;
}

/**
 * This function removes the value associated with the giving key
 * @param key- the key to remove its value
 * @return- true if the removal was successful, false otherwise
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::erase(const KeyT &key)
{
    if (!containsKey(key))
    {
        return false;
    }
    int hashIndex = getHashIndex(key, capacity());
    this->theMap[hashIndex].erase(key);
    this->mapSize--;
    if (getLoadFactor() < LOWER_LOAD_FACTOR)
    {
        rehash(this->mapCapacity / INCREASE_DECREASE_FACTOR);
    }
    return true;
}

/**
 * This function receives a key and returns its hashing value
 * @param key- the key to hash
 * @return- the hash value of the giving key
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::getHashIndex(KeyT key, int capacity) const
{
    return ((int) std::hash<KeyT>{}(key)) & (capacity - 1);
}


/**
 * This function returns the valueT type value associated with the giving key
 * @param key- the key to return its associated value
 * @return the valueT type value associated with the giving key
 */
template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::at(const KeyT &key) const
{
    // if the key is not in the matching bucket, the bucketIndex function will throw exception
    int mapIndex = bucketIndex(key);
    int bucketInd = this->theMap[mapIndex].containKey(key);
    return (this->theMap[mapIndex].getInventory()[bucketInd]).second;
}

/**
 * This function inserts an element- pair of the received key and value to the Map
 * @param key- the key to insert to the map
 * @param val- the value associated with the giving key
 * @return true if the insert was successful or false otherwise
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::insert(KeyT key, ValueT val)
{

    // if the key is already in the map, and this is a regular call to insert, do nothing
    if (containsKey(key) && !this->runOverDuplicate)
    {
        return false;
    }
        // if the key is already in the map, and this is a call to insert from the constructor,
        // replace the value for the matching key
    else if (containsKey(key) && this->runOverDuplicate)
    {
        int mapIndex = getHashIndex(key, capacity());
        this->theMap[mapIndex].replaceVal(key, val);
        return true;
    }

        //the key is not in the map, add a new value
    else
    {
        this->mapSize++;
        if (getLoadFactor() > UPPER_LOAD_FACTOR)
        {
            rehash(this->mapCapacity * INCREASE_DECREASE_FACTOR);
        }

        int mapIndex = getHashIndex(key, capacity());
        theMap[mapIndex].addToBucket(key, val);
        return true;
    }
}

/**
 * This function rehashes the Map into a new received size
 * @param newSize- the new size of the map
 */
template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::rehash(int newSize)
{
    Buckets<KeyT, ValueT> *newMap = new(std::nothrow) Buckets<KeyT, ValueT>[newSize];
    if (newMap == nullptr)
    {
        throw std::bad_alloc();
    }
    const_iterator it = begin();
    const const_iterator it_end = end();
    while (it != it_end)
    {
        KeyT key = (*it).first;
        ValueT val = (*it).second;
        int index = getHashIndex(key, newSize);
        newMap[index].addToBucket(key, val);
        ++it;
    }

    delete[]theMap;
    this->theMap = newMap;
    this->mapCapacity = newSize;
}

/**
 * This function returns an iterator points to the last element of the map
 * @return an iterator points to the last element of the map
 */
template<class KeyT, class ValueT>
typename HashMap<KeyT, ValueT>::const_iterator HashMap<KeyT, ValueT>::end() const
{
    return const_iterator((this->theMap), this->mapCapacity, true);

}

/**
 * This function returns an iterator points to the first element of the map
 * @return an iterator points to the first element of the map
 */
template<class KeyT, class ValueT>
typename HashMap<KeyT, ValueT>::const_iterator HashMap<KeyT, ValueT>::begin() const
{
    return const_iterator((theMap), this->mapCapacity);
}

/**
 * This function returns a const iterator points to the last element of the map
 * @return a const iterator points to the last element of the map
 */
template<class KeyT, class ValueT>
const typename HashMap<KeyT, ValueT>::const_iterator HashMap<KeyT, ValueT>::cend() const
{
    const_iterator it = const_iterator((this->theMap), this->mapCapacity, true);
    return it;
}

/**
 * This function returns a const iterator points to the first element of the map
 * @return a const iterator points to the first element of the map
 */
template<class KeyT, class ValueT>
const typename HashMap<KeyT, ValueT>::const_iterator HashMap<KeyT, ValueT>::cbegin() const
{
    const_iterator it = const_iterator((this->theMap), this->mapCapacity);
    return it;
}

/**
 * The destructor for HashMap class
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::~HashMap()
{
    delete[] theMap;
}

/**
 * This is a copy constructor for HashMap object
 * @param mapToCopy- the HashMap object to copy from
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap &mapToCopy) : mapCapacity(mapToCopy.capacity()),
                                                           mapSize(mapToCopy.size()),
                                                           runOverDuplicate(false)
{
    this->theMap = new(std::nothrow) Buckets<KeyT, ValueT>[this->mapCapacity];
    if (this->theMap == nullptr)
    {
        throw std::bad_alloc();
    }
    const_iterator it = mapToCopy.cbegin();
    const_iterator it_end = mapToCopy.cend();
    while (it != (it_end))
    {
        KeyT key = (*it).first;
        ValueT val = (*it).second;
        int index = getHashIndex(key, capacity());
        this->theMap[index].addToBucket(key, val);
        ++it;
    }
}

/**
 * This is a move constructor for HashMap object
 * @param mapToMove- - the HashMap object to move from
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(HashMap && mapToMove) noexcept
{
    this->theMap = mapToMove.theMap;
    mapToMove.theMap = nullptr;
    this->mapCapacity = mapToMove.mapCapacity;
    this->runOverDuplicate = mapToMove.runOverDuplicate;
}

/**
 * This function is a brackets indexing operator for HashMap object
 * @param key- the key to access it's value
 * @return the value associated with the giving key
 */
template<class KeyT, class ValueT>
ValueT HashMap<KeyT, ValueT>::operator[](const KeyT key) const
{
    if (containsKey(key))
    {
        return at(key);
    }
    else
    {
        return ValueT();
    }
}

/**
 * This function is a brackets indexing operator for HashMap object
 * @param key- the key to access it's value
 * @return the value associated with the giving key
 */
template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::operator[](const KeyT key)
{
    if (!containsKey(key))
    {
        insert(key, ValueT());
    }
    return at(key);
}

/**
 * This function is a comparison operator for HashMap
 * @param m- the HashMap ro compare to
 * @return true, if the given map is equal to this map, or false otherwise
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator==(const HashMap &m) const
{
    if (size() != m.size())
    {
        return false;
    }
    const_iterator thisItCur = begin();
    const_iterator mItCur = m.cbegin();

    const_iterator thisItEnd = end();

    while (thisItCur != thisItEnd)
    {
        if ((*thisItCur) != (*mItCur))
        {
            return false;
        }
        ++thisItCur;
        ++mItCur;
    }
    return true;
}

/**
 * This function is a comparison operator for HashMap
 * @param m- the HashMap ro compare to
 * @return false, if the given map is equal to this map, or true otherwise
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator!=(const HashMap &m) const
{
    if (size() != m.size())
    {
        return true;
    }
    const_iterator thisItCur = begin();
    const_iterator mItCur = m.cbegin();

    const_iterator thisItEnd = end();

    while (thisItCur != thisItEnd)
    {
        if ((*thisItCur) != (*mItCur))
        {
            return true;
        }
        ++thisItCur;
        ++mItCur;
    }
    return false;
}

/**
 * This function is a copy assignment operator for HashMap
 * @param m- the map to assign
 * @return the HashMap object after assignment
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> &HashMap<KeyT, ValueT>::operator=(const HashMap &m)
{
    *this = HashMap(m);
    return *this;
}

/**
 * This function is a move assignment operator for HashMap
 * @param m- the map to assign
 * @return the HashMap object after assignment
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> &HashMap<KeyT, ValueT>::operator=(HashMap && m) noexcept
{
    std::swap(theMap, m.theMap);
    this->mapSize = m.mapSize;
    this->mapCapacity = m.mapCapacity;
    this->runOverDuplicate = m.runOverDuplicate;
    return *this;
}
