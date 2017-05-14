//
// Created by malemany on 29/01/17.
//

#ifndef C_SAMPLE_3_TABLEINPRIVATECHILD_H
#define C_SAMPLE_3_TABLEINPRIVATECHILD_H


#include "TableInPrivate.h"

class TableInPrivateChild : public TableInPrivate {
    public:
        string getBaseString() {
            // Access to protected variables of the basis class through private inheritance because of friendship
            // return this->PROTECTED_BASE_STRING;
            return "No access to protected base string through private virtual inheritance";
        }
};


#endif //C_SAMPLE_3_TABLEINPRIVATECHILD_H
