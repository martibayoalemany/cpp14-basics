//
// Created by malemany on 29/01/17.
//

#ifndef C_SAMPLE_3_ABSOLUTETABLE_H
#define C_SAMPLE_3_ABSOLUTETABLE_H


#include "OnTheFlyTable.h"
#include "RandomTable.h"

class AbsoluteTable : public RandomTable, public OnTheFlyTable {

    public:
    AbsoluteTable() {

    }

    virtual int generateNum() {
        return OnTheFlyTable::generateNum();
    }

    virtual string getTypeName() {
        return "AbsoluteTable";
    };

    private:

};


#endif //C_SAMPLE_3_ABSOLUTETABLE_H
