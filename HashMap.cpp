////
//// Created by shir2 on 18/01/2020.
////
//
//#include <string>
//#include <iostream>
//#include <vector>
//#include "HashMap.hpp"
//using std::string;
//using std::cout;
//using std::endl;
//using std::vector;
//using std::pair;
//int main()
//{
//    HashMap<int,string> myMap{};
//    HashMap<int,string> myMap2{};
//    HashMap<int,string> myMap3({0,1,2},{"gadi","karin","shir"});
//    cout<<"capacity: "<<myMap3.capacity()<<endl;
//    cout<<"key index"<< (1337&15) <<endl;
//    const HashMap<int, int> map({1337}, {1337});
////    std::pair<int, int> expectedPair(1337, 1337);
//    auto it = myMap.begin();
//    auto it_end = myMap.end();
//    if(it==it_end){
//        cout<<"yes"<<endl;
//    }
//    int iters = 0;
//    for (const auto& kvp: myMap)
//    {
//        ++iters;
//    }
////    if(*it==expectedPair){
////        return 1;
////    }
////    cout<<"size: "<<myMap.size()<<endl;
//////    cout<<"key index"<< (0&15) <<endl;
////    myMap.insert(1,"gadi");
////    myMap.insert(2,"karin");
////    cout<<"capacity: "<<myMap.capacity()<<endl;
////    cout<<"size: "<<myMap.size()<<endl;
////
////    cout<<myMap.containsKey(1)<<endl; // return 1
////    cout<<myMap.containsKey(2)<<endl; // return 1
////    cout<<myMap.containsKey(3)<<endl; // return 0
////    cout<<myMap.at(1)<<endl; // return gadi
////    cout<<myMap.at(2)<<endl; // return karin
////    myMap.erase(2);
////    cout<<myMap.containsKey(2)<<endl; // return 0
////    cout<<"capacity: "<<myMap.capacity()<<endl;
////    cout<<"size: "<<myMap.size()<<endl;
////    cout<<"load factor: "<<myMap.getLoadFactor()<<endl;
////    cout<<"***check rehash for 20 inserts** "<<endl;
////    for(int i = 0;i<20;i++){
////        myMap.insert(i,"test");
////    }
////    cout<<"capacity: "<<myMap.capacity()<<endl;
////    cout<<"size: "<<myMap.size()<<endl;
////    cout<<"load factor: "<<myMap.getLoadFactor()<<endl;
////    for(int i = 20;i<30;i++){
////        myMap2.insert(i,"operator");
////    }
////    cout<<"***check operators** "<<endl;
////    cout<<myMap2[26]<<endl; // print operator
////    cout<<(myMap == myMap2)<<endl; //print 0
////    cout<<(myMap != myMap2)<<endl; //print 1
////    myMap = myMap2;
////    cout<<(myMap == myMap2)<<endl; //print 1
////    cout<<(myMap != myMap2)<<endl; //print 0
////    cout<<"size before clear: "<<myMap2.size()<<endl;
////    myMap2.clear();
////    cout<<"size after clear: "<<myMap2.size()<<endl; // size is 0
////    cout<<"after clear values are erased,0 if true:"<<myMap2.containsKey(23)<<endl; // print 0
////    for(int i = 20;i<30;i++){
////        myMap2.insert(i,"operator");
////    }
////    cout<<"capacity: "<<myMap2.capacity()<<endl;
////    cout<<"size: "<<myMap2.size()<<endl;
////    cout<<"load factor: "<<myMap2.getLoadFactor()<<endl;
////    cout<<"check [] "<<myMap2[25]<<endl;
////    cout<<"check [] "<<myMap2[35]<<endl;
////    cout<<"contains index 35 with no value,1 if true"<<myMap2.containsKey(35)<<endl;
////    myMap2[36]="shir";
////    cout<<myMap2.at(36)<<endl;
////    return 0;
//}
