//
// Created by malemany on 29/01/17.
//

#ifndef C_SAMPLE_3_TABLEINPRIVATE_H
#define C_SAMPLE_3_TABLEINPRIVATE_H


#include "Table.h"

class TableInPrivate : private virtual Table {
    public:
        string getBaseString() {
            return this->PROTECTED_BASE_STRING;
        }


};


#endif //C_SAMPLE_3_TABLEINPRIVATE_H
