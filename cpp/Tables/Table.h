//
// Created by malemany on 28/01/17.
//

#ifndef C_SAMPLE_3_TABLE_H
#define C_SAMPLE_3_TABLE_H
#include <iostream>
#include <bits/unique_ptr.h>
#include <mutex>
#include <memory>
#include "../multithreading/te_lock_guard.h"

using namespace std;

class Table  {
    private:
        std::mutex mutex;
        const std::string mode;
        int maxNum;
        const std::string mode2;
        const std::wstring lmode;
        const std::wstring lmode2;

    protected :
        const string PROTECTED_BASE_STRING = "PROTECTED BASE STRING";
    public :
        Table()  {

        };
        Table(int maxNum) {this->maxNum = maxNum;};
        /**
         * Initializing non unicode version
         */
        Table(const char* mode) : mode(std::string(mode)), maxNum(6), mode2(mode) { };
        /**
         * Initializing unicode version
         */
        Table(const wchar_t* lmode) : maxNum(6), lmode(std::wstring(lmode)), lmode2(lmode) {

        };

        Table(const Table& inst) : mode(inst.mode), maxNum(inst.maxNum), mode2(inst.mode2),
                                   lmode(inst.lmode), lmode2(inst.lmode2) {

            cout << "Table reference constructor was used" << endl;
        }

        Table(Table&& inst ) :  mode(std::move(inst.mode)), maxNum(std::move(inst.maxNum)),
                                 mode2(std::move(inst.mode2)),
                                 lmode(std::move(inst.lmode)), lmode2(std::move(inst.lmode2)){

            cout << "Table move constructor was used" << endl;
        }

        // Assign operator deleted
        Table& operator=(const Table& inst) = delete;

        // Move assign operator deleted
        Table& operator=( Table&& inst ) = delete;


        inline bool isUnicode() const {
            return not lmode.empty() && mode.empty();
        }

        virtual ~Table() {
            cout  << "Table destructor called" << endl;
        };

        virtual void doExecute();
        int doReturnInteger();
        bool doCheckExceptions();
        // std::string
        std::string getMode() { return mode;}
        // Same as @see Table::getMode() different initialization
        std::string getMode2() { return mode2;}
        // Non empty in unicode mode (wstring)
        std::wstring getLMode() { return lmode;}
        // Non empty in unicode mode (wstring), copy of @see Table::getLMode()
        std::wstring getLMode2() { return lmode2;}
        std::string getName() { return "Table";}

        /**
         * @return After Table::getMaxNum calls are reach, it returns always 0
         */
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
