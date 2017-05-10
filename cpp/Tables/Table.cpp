//
// Created by malemany on 28/01/17.
//

#include "Table.h"
#include "RandomTable.h"

using namespace std;

void Table::doExecute() {
    //auto exc = std::make_exception_ptr(new custom_exception());
    //std::rethrow_exception(exc);

    //throw new custom_exception;
    //throw custom_exception();
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