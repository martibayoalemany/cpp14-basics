//
// Created by username on 09.05.17.
//

#ifndef CPP14_BASICS_CAR_H
#define CPP14_BASICS_CAR_H
#include <iostream>
using namespace std;

class Car {
    private:
        std::string name;
    public:
        Car() {
            this->name = "Car name";
        };

        virtual ~Car() {
            cout << "Car was destructed" << endl;
        }

        std::string toString();

        void pthread_create_check();
};


#endif //CPP14_BASICS_CAR_H
