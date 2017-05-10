//
// Created by malemany on 28/01/17.
//

#include "Table.h"
#include "RandomTable.h"
#include <vector>

using namespace std;

void Table::doExecute() {
    static int i = -1;
    i++;
    cout << "---------------------------" << endl;
    switch (i) {
        case 0: {
            cout << i << " Thrown custom_exception2 " <<endl;
            throw custom_exception2();
            break;
        }
        case 1: {
            cout << i << " Thrown custom_exception exception_ptr " <<endl;
            auto exc = std::make_exception_ptr(new custom_exception());
            std::rethrow_exception(exc);
            break;
        }
        case 2: {
            cout << i << " Thrown new custom_exception " <<endl;
            throw new custom_exception;
            break;
        }
        case 3: {
            cout << i << " Thrown custom_exception " <<endl;
            throw custom_exception();
            break;
        }
    }
}


bool Table::doCheckExceptions() {
    Table* table = new RandomTable();
    try {
        table->doExecute();
    } catch(custom_exception2& exc) {
        cout << "catch as value2 " << exc.what() << endl;
    } catch(const std::logic_error& err) {
        cout << err.what() << endl;
    } catch(custom_exception& exc) {
        cout << "catch value " << exc.what() << endl;
    }
    catch (const exception& exc) {
        cout << "catch reference " << exc.what() << endl;
    }
    catch(const custom_exception* exc) {
        cout << "catch pointer " << exc->what() << endl;
        delete exc;
    }
    return true;
}

int Table::doReturnInteger() {
    return 5;
}