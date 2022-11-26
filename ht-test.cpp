#include "ht.h"
#include "hash.h"
#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <functional>
using namespace std;
int main()
{
    DoubleHashProber<std::string, MyStringHash > dh;
    HashTable<std::string, int, DoubleHashProber<std::string, MyStringHash >, std::hash<std::string>, std::equal_to<std::string> > ht(0.7, dh);

    for(size_t i = 0; i < 10; i++){
        std::stringstream ss;
        ss << "hi" << i;
        ht.insert({ss.str(), i});
    }
    if( ht.find("hi1") != nullptr ){
        cout << "Found hi1" << endl;
        ht["hi1"] += 1;
        cout << "Incremented hi1's value to: " << ht["hi1"] << endl;
    }
    if( ht.find("doesnotexist") == nullptr ){
        cout << "Did not find: doesnotexist" << endl;
    }
    cout << "HT size: " << ht.size() << endl;
    ht.remove("hi7");
    ht.remove("hi9");
    cout << "HT size: " << ht.size() << endl;
    if( ht.find("hi9") != nullptr ){
        cout << "Found hi9" << endl;
    }
    else {
        cout << "Did not find hi9" << endl;
    }
    ht.insert({"hi7",17});
    cout << "size: " << ht.size() << endl;

    string s1("hi1"), s2("hi2"), s3("hi3"), s4("antidisestablishmentarianism");
    MyStringHash h1;
    cout << s1 << " " << h1(s1) << endl;
    cout << s2 << " " << h1(s2) << endl;
    cout << s3 << " " << h1(s3) << endl;
    cout << s4 << " " << h1(s4) << endl;
    return 0;
}
