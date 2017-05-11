//
// Created by malemany on 28/01/17.
//

#ifndef C_SAMPLE_3_ONTHEFLYTABLE_H
#define C_SAMPLE_3_ONTHEFLYTABLE_H


#include "Table.h"

/**
 * Overload of the class table with a different generation strategy
 */
class OnTheFlyTable : public virtual Table {

    public:
    OnTheFlyTable() : Table("OnTheFlyTable") {

    }
    OnTheFlyTable(bool force_on_the_fly, int maxNum) : Table(maxNum) {

    }

    /**
     * @returns At each call from 1 to infinity, numbers between {1,2,4,8,16,24}
     */
    virtual int generateNum() override {
        auto&& function  = [this] ()  {
                                        static int i = 0;
                                        int arr[] = {1,2,4,8,16,24};
                                        if(i < getMaxNum()) return arr[(i++) % 6];
                                        else {
                                            i = 0;
                                            return 0;
                                        }
                                    };
        return function();
    };

    virtual string getTypeName() override {
        return "OnTheFlyTable";
    };

 };


#endif //C_SAMPLE_3_ONTHEFLYTABLE_H
