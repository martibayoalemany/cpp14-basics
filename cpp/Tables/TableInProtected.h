//
// Created by malemany on 29/01/17.
//

#ifndef C_SAMPLE_3_TABLEINPROTECTED_H
#define C_SAMPLE_3_TABLEINPROTECTED_H


#include "Table.h"

class TableInProtected : protected Table {
    public:
        string getBaseString() {
            return this->PROTECTED_BASE_STRING;
        }
};

class TableInProtectedChild : TableInProtected {
    public:
        string getBaseString() {
            return this->PROTECTED_BASE_STRING;
        }
};

#endif //C_SAMPLE_3_TABLEINPROTECTED_H
