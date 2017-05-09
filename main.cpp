#include <iostream>
#include "cpp/car.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto lambda = [] (auto a) { std::cout << "sa_handler: " << a << std::endl;};
    Car* car = new Car();
    car->pthread_create_check();
    cout << car->toString() << endl;

    return 0;
}