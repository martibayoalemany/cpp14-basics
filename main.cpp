#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <bitset>
#include <deque>
#include <bits/forward_list.h>
#include <chrono>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>
#include <bits/unordered_set.h>
#include <list>
#include <fstream>
#include <sstream>
#include "cpp/Utils.h"

using namespace std;

int main(int argc, char **argv) {

    // error: excess elements in array initializer
    // array<int, 3> arr2 ={{2, 3, 4, 5}};

    array<int,20> arr3 = {10,2};
    for_each(arr3.begin(), arr3.end(), [=] (int i) {cout << i;});

    vector<int> vec = {1,2,3,4,5};
    for_each(vec.begin(), vec.end(), [=](int i) {cout << i ;});

    int sum = 0;
    using Iter = std::vector<int>::iterator;
    for(Iter it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }
    cout << sum << endl;

    //-----------
    // bitset
    //-----------
    std::bitset<16> bar(0xfa2);
    std::bitset<16> baz(std::string("010111110001"));
    cout << baz << endl;

    //-----------
    // array
    //-----------
    array<int,3> arr = {1,2,3};
    void(*print)(int i) = [] (int i) { std::cout << i << " "; };
    for_each(arr.begin(), arr.end(), print);
    cout << endl;

    //-----------
    // deque
    //-----------
    deque<int> dq(10);
    cout << " s : " << dq.size() << " isEmpty : " << dq.empty() << " maxSize : " << dq.max_size() << endl;
    //--
    typedef vector<int>::iterator It;
    for(It it = vec.begin(); it < vec.end(); it++) {
        dq.push_front(*it);
    }
    cout << " s : " << dq.size() << " isEmpty : " << dq.empty() << " maxSize : " << dq.max_size() << endl;
    //--
    dq.insert(dq.begin()+2, arr.begin(), arr.begin()+2);
    cout << " s : " << dq.size() << " isEmpty : " << dq.empty() << " maxSize : " << dq.max_size() << endl;
    //--
    int array[] = {0,1,2,3,4,5};
    dq.insert(dq.begin()+2, array, array+2);
    cout << " s : " << dq.size() << " isEmpty : " << dq.empty() << " maxSize : " << dq.max_size() << endl;

    //-----------
    // forward_list
    //-----------
    // TODO: this does not compile with clang 3.8
    /*
    forward_list<int> fwl (20,20);
    cout << " forward_list" << endl;
    for_each(fwl.begin(), fwl.end(), [] (int i) { cout << i << endl;});
     */


    //-----------
    // list
    //-----------
    std::list<int> ints = {1,2,3,4,5,6,8,9,20};
    auto it = ints.begin();
    while( it != ints.end()) {
        cout << *it << endl;
        ++it;
    }
    auto val = binary_search(ints.begin(), ints.end(), 22);
    cout << val << endl;

    string str = "hello world";
    reverse(str.begin(), str.end());
    cout << str << endl;

    auto any_even = std::any_of(ints.cbegin(), ints.cend(), [](int i) { return i % 2 == 0;});
    cout << "any even " << any_even << endl;


    //-----------
    // mismatch
    //-----------
    string a = "abcdefghijkl";
    string b = "abcdeghijkl";
    cout << " mismatch -> " << string(a.cbegin(), mismatch(a.cbegin(), a.cend(), b.cbegin()).first) << endl;

    //-----------
    // search
    //-----------
    vector<int> cs = {};
    for(int i = 0; i < 2000; i++)
        cs.push_back(rand());
    vector<int> search_for = {};
    for(int i = 20; i < 30; i++)
        search_for.push_back(cs[i]);
    /*
    std::random_device rd;
    std::mt19937 g(rd());
    random_shuffle(search_for.begin(), search_for.end(), g);
    */
    auto result = find_first_of(cs.begin(), cs.end(), search_for.begin(), search_for.end() );

    if(result == cs.end())
        cout << " No elements found" << endl;
    else if(result  != cs.end())
        cout << " Found a match at " << distance(cs.begin(), result) << endl;

    //------------
    // std:: search
    //------------
    {
        std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
        std::string needle = "pisci";
        auto its = std::search(in.begin(), in.end(), needle.begin(), needle.end());
        if (its != in.end())
            std::cout << "The string " << needle << " found at offset "
                      << its - in.begin() << '\n';
        else
            std::cout << "The string " << needle << " not found\n";
    }

    chrono::steady_clock::time_point st_now = chrono::steady_clock::now();
    fstream textFile;
    textFile.open("/home/malemany/txt/text.txt", ios::in);
    stringstream buffer;
    buffer << textFile.rdbuf();
    textFile.close();
    chrono::steady_clock::time_point en_now = chrono::steady_clock::now();

    cout << " Read file in " << chrono::duration_cast<chrono::microseconds>(en_now - st_now).count() << endl;

    st_now = chrono::steady_clock::now();
    string in = buffer.str();
    cout << " File size : " << in.size() << endl;
    std::string needle = "percent";
    auto its = std::search(in.begin(), in.end(), needle.begin(), needle.end());
    if (its != in.end())
        std::cout << "The string " << needle << " found at offset "
                  << its - in.begin() << '\n';
    else
        std::cout << "The string " << needle << " not found\n";
    en_now = chrono::steady_clock::now();
    cout << " Search in file in " << chrono::duration_cast<chrono::microseconds>(en_now - st_now).count() << endl;

    //-----------
    // algorithms
    //-----------
    vector<int> as = {1,2,3,4,5,6};
    vector<int> bs = {7,8,9,10};
    for(int i = 0; i < 20; i++)
        for_each(as.begin(), as.end(), [&bs] (int i) { bs.push_back(i);});
    cout << bs.size() << " / " << bs.max_size() << endl;

    auto tmp = search(bs.begin(), bs.end(), as.begin(), as.end());
    cout << "search " << (tmp.base() - as.begin().base())/sizeof(int) << endl;

    cout << " copy_if " << endl;
    list<int> target = {};
    auto less_than_3 = [] (int i) { return i < 3;};
    copy_if(bs.begin(), bs.end(), target.begin(), less_than_3);
    cout << " less_than_3" << target.size() << " / " << bs.size() << endl;

    /* vector<int> l;
     move(bs.begin(), bs.end, std::back_inserter(l));
     cout << "search " << bs.size() << " " << l.size() << endl;
     */
    //-----------
    // map
    //-----------
    map<string,int> maps;
    maps["hello"] = 2;
    maps["best"] = 3;
    for(auto&p : maps)
        cout << p.first << " -> " << p.second << endl;

    map<string,int> maps2 = {
            {"hello", 1},
            {"world", 2},
            {"earth", 3},
            {"fire", 5}
    };

    for(auto&p : maps2)
        cout << p.first << " -> " << p.second << endl;

    //-----------
    // set
    //-----------
    set<string> setOfNumbers = {"first","second", "first"};
    cout << "setOfNumbers " << setOfNumbers.size() << endl;

    //-----------
    // stack
    //-----------
    std::stack<int> stacks;
    stacks.push(2);
    stacks.emplace(3);
    stacks.push(4);

    // cout << a << " -> " << b << endl;
    cout << "stack " << stacks.size() << endl;
    do {
        int iTmp = stacks.top();
        cout << iTmp << endl;
        stacks.pop();
    } while(stacks.size() > 0);
    //-----------
    // unordered_map
    //-----------
    std::map<std::string, std::string> uno_maps = {{"Washington", "US"},  {"Madrid", "Spain"}, {"London", "UK"}};
    for(auto it : uno_maps) {
        cout << it.first << " -> " << it.second << endl;
    }
    unordered_map<string,string> un_uno_maps = {{"Washington", "US"},  {"Madrid", "Spain"}, {"London", "UK"}};
    for(auto it : un_uno_maps) {
        cout << it.first << " -> " << it.second << endl;
    }
    //-----------
    // unordered_set
    //-----------
    unordered_set<string> setOfNumbers2 = {"first","second", "first", "third"};
    cout << "setOfNumbers2 " << setOfNumbers2.size() << endl;
    cout << " --- " << endl;
    for(auto num : setOfNumbers)
        cout << num << endl;
    cout << " --- " << endl;
    for(auto num : setOfNumbers2)
        cout << num << endl;

    //-----------
    // clocks
    //-----------

    chrono::system_clock::time_point st_sys_now = chrono::system_clock::now();
    chrono::steady_clock::time_point st_std_now = chrono::steady_clock::now();
    chrono::high_resolution_clock::time_point st_high_now = chrono::high_resolution_clock::now();
    vector<int> vector;
    for(int i = 0; i < 1000000; i++) {
        vector.push_back(rand());
    }

    chrono::system_clock::time_point en_sys_now = chrono::system_clock::now();
    chrono::steady_clock::time_point en_std_now = chrono::steady_clock::now();
    chrono::high_resolution_clock::time_point en_high_now = chrono::high_resolution_clock::now();

    cout << "system clock : " << std::chrono::duration_cast<chrono::microseconds>(en_sys_now - st_sys_now).count() << endl;
    cout << "steady clock : " << std::chrono::duration_cast<chrono::microseconds>(en_std_now - st_std_now).count() << endl;
    cout << "high clock : " << std::chrono::duration_cast<chrono::microseconds>(en_high_now - st_high_now).count() << endl;

    /**
     * Checking casting and inheritance
     */
/*
    AbsoluteTable table;
    cout << "Just the absolute table -> " << table.getTypeName() << endl;
    cout << "Through the fly branch -> " << table.OnTheFlyTable::getTypeName() << endl;
    cout << "Through the random branch -> " << table.RandomTable::getTypeName() << endl;
    Table* base = (Table*) &table;
    cout << "Through polymorphism into base -> " << base->getTypeName() << endl;
    RandomTable* random = (RandomTable*) &table;
    cout << "Through polymorphism into random -> " << random->getTypeName() << endl;
    OnTheFlyTable* fly = (OnTheFlyTable*) &table;
    cout << "Through polymorphism into fly-> " << fly->getTypeName() << endl;

*/
    // Unit testing
    // printf("Running main() from gtest_main.cc\n");
    // testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();


}
