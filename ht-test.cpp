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
    HashTable<
        std::string, 
        int, 
        DoubleHashProber<std::string, MyStringHash >, 
        std::hash<std::string>, 
        std::equal_to<std::string> > ht(0.7, dh);

    // This is just arbitrary code. Change it to test whatever you like about your 
    // hash table implementation.
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




    cout <<"====\n\n\n=====MYTESTS=====\n\n\n=====" << '\n';

    cout <<"Inserting duplicates" <<endl;
    HashTable<string,int,DoubleHashProber<string,MyStringHash>> ht1(0.7,dh);
    
    ht1.insert({"dup", 1});
    ht1.insert({"dup", 99}); //update not insert

    cout << "dup val: " << ht1["dup"] << " ::: shoulder be 99" << endl;
    cout << "size: " << ht1.size() << "::: shoulde be 1" <<endl;




    cout << "\n\n\n\n===================\nRemoving missing Keys " << endl;
    HashTable<string,int,DoubleHashProber<string,MyStringHash>> ht2(0.7,dh);

    ht2.insert({"a", 1});
    ht2.remove("nothing");

    cout <<"size:: " << ht2.size() << "::::shoulder be 1"<< endl;

    cout <<"\n\n\n\n\n========\n\n Resize Test \n\n ========\n" << endl;
        HashTable<string,int,DoubleHashProber<string,MyStringHash>> ht4(0.4,dh);

    
    for(int i = 0; i < 20; ++i){
        ht4.insert({"k" + to_string(i), i});
    }
    bool ok = true;
    for(int i = 0; i <20; ++i){
        auto p = ht4.find("k" + to_string(i));
        if(p == nullptr || p->second != i){
            ok = false;
        }

    }

    cout << "RESIZEWORKED?" << (ok ? "YES" : "NO") << endl;
    cout <<"size: " << ht4.size() << " ;; ; ;; SHOULDBE20" <<endl;

    cout << "\n\n\n==========\nDelete resizen\n\n\n====" <<endl;
    HashTable<string,int,DoubleHashProber<string,MyStringHash>> ht5(0.3,dh);

    for(int i =0; i <15; i++){
        ht5.insert({"r"+to_string(i),i});
    }

    ht5.remove("r3");
    ht5.remove("r7");
    ht5.remove("r11");
    
    ht5.insert({"trigger", 100});

    cout << "find r3" << (ht5.find("r3") == nullptr ? "nullptr": "found")<<endl;
    cout << "find r7" << (ht5.find("r7") == nullptr ? "nullptr": "found")<<endl;
    cout << "find r111" << (ht5.find("r11") == nullptr ? "nullptr": "found")<<endl;
    cout << "triggere::: " << ht5["trigger"] << endl;



    cout << "\n\n\n======PROBING\n\n\n\n\n"<< endl;
    HashTable<string,int,LinearProber<string>> ht6(0.99);
    try {
        for(int i = 0; i < 11; ++i){
            ht6.insert({"p"+to_string(i),i});
        }
        cout << "inserted without failing WORKEWDDDDD" <<endl;

    }catch(const logic_error& e){
        cout <<"Dumbahh this shit did not work youre cooked gng" << e.what() << endl;
    }

    return 0;
}
