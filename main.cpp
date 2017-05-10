#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <bitset>
#include <deque>
#include <bits/forward_list.h>
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




}
