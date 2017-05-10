//
// Created by malemany on 28/01/17.
//

#ifndef C_SAMPLE_3_TABLE_H
#define C_SAMPLE_3_TABLE_H
#include <iostream>
#include <exception>
#include <vector>

using namespace std;

class Table  {
    private:
        const std::string mode;
        int maxNum;
    protected :
        const string PROTECTED_BASE_STRING = "PROTECTED BASE STRING";
    public :
        Table()  {

        };
        Table(int maxNum) {this->maxNum = maxNum;};
        Table(const char* mode) : mode(std::string(mode)), maxNum(6) { };
        virtual ~Table() {};
        virtual void doExecute();
        int doReturnInteger();
        bool doCheckExceptions();
        std::string getMode() { return mode;}
        std::string getName() { return "Table";}
        virtual int generateNum() {
            static int i = 0;
            if(i > getMaxNum()) return 0;
            return i++;
        };
        virtual int getMaxNum() {
            return maxNum;
        }
        virtual bool isPositive() {
            return true;
        }

        virtual string getTypeName() {
            return "Table";
        };

    friend class TableInPrivateChild;
};

class custom_exception : std::exception
{
public:
    custom_exception() { };
    custom_exception(const custom_exception& e) {
        cout << " copy constructor called" << endl;
    };

    ~custom_exception() noexcept {
        cout << "destructor called" <<endl;
    };

    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT override {
        return "custom exception";
    };
};

class custom_exception2
{
public:
    custom_exception2() { }

    custom_exception2(const custom_exception2& e) {
        cout << " reference copy constructor called" << endl;
    }
    ~custom_exception2() {
        cout << "destructor called" << endl;
    }
    const char* what() const noexcept {
        return "custom exception";
    }
};

#endif //C_SAMPLE_3_TABLE_H
