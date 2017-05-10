//
// Created by malemany on 29/01/17.
//

#ifndef C_SAMPLE_3_TABLEINPROTECTEDCHILD_H
#define C_SAMPLE_3_TABLEINPROTECTEDCHILD_H


#include "TableInProtected.h"

class TableInProtectedChild : TableInProtected {
    public:
        string getBaseString() {
            return this->PROTECTED_BASE_STRING;
        }
};


#endif //C_SAMPLE_3_TABLEINPROTECTEDCHILD_H
