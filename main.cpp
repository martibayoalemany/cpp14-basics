#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include "cpp/Utils.h"

using namespace std;

int main(int argc, char **argv) {
    Utils::doMemoryAccess();

    array<int, 3> arr ={{2, 3, 4}};
    cout << arr[-1] << endl;

    // error: excess elements in array initializer
    // array<int, 3> arr2 ={{2, 3, 4, 5}};

    // 10 elements of value 10 ( warning)
    array<int,20> arr3 = {10,2};
    for_each(arr3.begin(), arr3.end(), [=] (int i) {cout << "{} init "<< i << endl;});

    vector<int> vec = {1,2,3,4,5};
    for_each(vec.begin(), vec.end(), [=](int i) {cout << i << endl;});




}

int main2(int argc, char **argv) {

    Utils::checkCarCreation();
    Utils::doHandleSignals(false);
    Utils::doMemoryAccess();
    Utils::doMultithreading();

    return 0;
}