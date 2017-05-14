//
// Created by malemany on 28/01/17.
//

#ifndef C_SAMPLE_3_RANDOMTABLE_H
#define C_SAMPLE_3_RANDOMTABLE_H


#include "Table.h"

class RandomTable : public virtual Table {

    public:
    RandomTable() : Table("RandomTable") {

    }
    /**
     * @returns Returns 0 at the seventh call otherwise call @see Table::generateNum
     */
    virtual int generateNum() override {
        static int i = 0;
        i++;
        if (i == 7)
            return 0;
        else
            return Table::generateNum();
    };
};


#endif //C_SAMPLE_3_RANDOMTABLE_H
