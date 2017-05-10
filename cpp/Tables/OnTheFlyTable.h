//
// Created by malemany on 28/01/17.
//

#ifndef C_SAMPLE_3_ONTHEFLYTABLE_H
#define C_SAMPLE_3_ONTHEFLYTABLE_H


#include "Table.h"

class OnTheFlyTable : public virtual Table {

    public:
    OnTheFlyTable() : Table("OnTheFlyTable") {

    }
    OnTheFlyTable(bool force_on_the_fly, int maxNum) : Table(maxNum) {

    }
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

    /**
     * warning: 'getTypeName' overrides a member function but is not marked 'override' [-Winconsistent-missing-override]
     * <remark> <br/>we can write override to prevent the warning </remark>
     */
    virtual string getTypeName() {
        return "OnTheFlyTable";
    };

 };


#endif //C_SAMPLE_3_ONTHEFLYTABLE_H
