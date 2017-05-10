//
// Created by malemany on 29/01/17.
//

#ifndef C_SAMPLE_3_TABLECLIENT_H
#define C_SAMPLE_3_TABLECLIENT_H


#include "Table.h"

class TableClient {
    private:
        Table& strategy;
    public:
        TableClient(Table& strategy) : strategy(strategy){
        }

        bool doExecute() {
            for(int i=0; i<5;i++) {
                strategy.generateNum();
            }
            return true;
        }
};


#endif //C_SAMPLE_3_TABLECLIENT_H
