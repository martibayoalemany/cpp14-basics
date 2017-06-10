//
// Created by username on 10.05.17.
//

#ifndef CPP14_BASICS_UTILS_H
#define CPP14_BASICS_UTILS_H

#include<iostream>

using namespace std;

class Utils
{

  private:
    std::string name;

  public:
    static void doInvalidMemoryAccess();
    static void doMultithreading();
    static void setSignalHandler();

    Utils()
    {
        this->name = "Utils name";
    };

    virtual ~Utils()
    {
        cout << "Utils was destructed" << endl;
    }

    std::string toString();

    void pthread_create_check();
};

#endif //CPP14_BASICS_UTILS_H
