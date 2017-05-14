//
// Created by username on 11.05.17.
//

#ifndef CPP14_BASICS_NOT_IMPLEMENTED_EXCEPTION_H
#define CPP14_BASICS_NOT_IMPLEMENTED_EXCEPTION_H


#include <exception>

class not_implemented_exception : std::exception
{
public:
    not_implemented_exception() { };
    //not_implemented_exception(const not_implemented_exception& e) = delete;

    virtual const char* what()  const /*_GLIBCXX_USE_NOEXCEPT */ noexcept override {
        return "not implemented exception";
    };
};


#endif //CPP14_BASICS_NOT_IMPLEMENTED_EXCEPTION_H
