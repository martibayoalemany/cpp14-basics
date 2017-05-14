//
// Created by malemany on 28/01/17.
//

#include "../Table.h"
#include "../RandomTable.h"
#include "../OnTheFlyTable.h"
#include "../TableInProtected.h"
#include "../TableInPrivate.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>


using namespace std;
using ::testing::TestWithParam;
using ::testing::Bool;
using ::testing::Values;
using ::testing::Combine;
using ::testing::Types;
using ::testing::AtMost;
using ::testing::AtLeast;
using ::testing::InitGoogleTest;

TEST(Table, doReturnInteger) {
    Table t;
    EXPECT_EQ(5, t.doReturnInteger());
    EXPECT_GT(6, t.doReturnInteger());
}

TEST(Table, doCheckExceptions) {
    Table t;
    EXPECT_EQ(true, t.doCheckExceptions());
    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(t.doCheckExceptions());
    }
}

TEST(Table, getName) {
    Table t;
    EXPECT_STREQ("Table", t.getName().c_str());
}

TEST(Table, checkUnicode) {
    const wchar_t * mode_wc = L"modeÄÜÖ";
    Table* t = new Table(mode_wc);
    EXPECT_TRUE(t->getLMode() == mode_wc);
    EXPECT_TRUE(t->getLMode() == t->getLMode2());

    delete t;
}

TEST(Table, checkMovers) {
    Table t = Table(L"mover");
    Table t2 = Table(t);
    EXPECT_TRUE(t.getLMode() == t2.getLMode());

    // Check equality after a move
    wcout << t2.getLMode() << endl;
    Table t3 = std::move(t2);
    wcout << t2.getLMode() << endl;
    wcout << t3.getLMode() << endl;
    EXPECT_TRUE(t3.getLMode() == t.getLMode());
}

class TableTest : public testing::Test {
    protected:
        virtual void SetUp() {
            start_time = time(NULL);
            t1 = shared_ptr<Table>(new Table("Mode 1"));
            t2 = shared_ptr<Table>(new Table("Mode 2"));
            t3 = shared_ptr<Table>(new Table("Mode 3"));
        }

        virtual void TearDown() {
            const time_t end_time = time(NULL);
            EXPECT_TRUE(end_time - start_time <= 5);
        }

    shared_ptr<Table> t1;
    shared_ptr<Table> t2;
    shared_ptr<Table> t3;
    time_t start_time;
};

/**
 * Testing the table mode initialization
 */
TEST_F(TableTest, NamedConstructor) {
    EXPECT_STREQ("Mode 1", t1.get()->getMode().c_str());
    EXPECT_STREQ("Mode 2", t2.get()->getMode().c_str());
    EXPECT_STREQ("Mode 3", t3.get()->getMode().c_str());
}

/**
 * Typed test case
 */

template<class T>
Table* CreateCustomTable();

template<>
Table* CreateCustomTable<OnTheFlyTable> () {
    return new OnTheFlyTable;
}

template<>
Table* CreateCustomTable<RandomTable> () {
    return new RandomTable;
}

template<class T>
class TypedTests : public testing::Test {
    protected:
        TypedTests() : table(CreateCustomTable<T>())  {}
        virtual ~TypedTests() {
            try {
                delete table;
            }
            catch(...) {
                std::exception_ptr p = std::current_exception();
                cout << "Typed tests destructor " << (p ? p.__cxa_exception_type()->name() : "null") << endl;
            }
        }
        Table* table;
};

// Both tables behaves in a similar way, they return 0 at the seventh call
typedef Types<RandomTable, OnTheFlyTable> Implementations;

TYPED_TEST_CASE(TypedTests, Implementations);

TYPED_TEST(TypedTests, Check0After5Times) {
    for(int i = 0; i < 6; i++)
        EXPECT_TRUE(this->table->generateNum() >= 0);
    EXPECT_EQ(0, this->table->generateNum());
}

/**
 * Parameterized test cases, we try the series with different values as parameter
 */

class PrimeTableTest : public TestWithParam<::testing::tuple<int>> {
    protected:
        virtual void SetUp() {
            int max_num = ::testing::get<0>(GetParam());
            table = new OnTheFlyTable(true, max_num);
        }
        virtual void TearDown() {
            delete table;
            table = nullptr;
        }
        Table* table;
};

TEST_P(PrimeTableTest, ReturnAllPositives) {
    EXPECT_TRUE(table->isPositive());
    EXPECT_GE(10, table->getMaxNum());
    for(int i = 0; i < table->getMaxNum(); i++) {
        EXPECT_TRUE(table->generateNum() != 0);
    }
    EXPECT_TRUE(table->generateNum() == 0);
}

INSTANTIATE_TEST_CASE_P(MeaningfulTestParameters, PrimeTableTest, Values(1,2,3,4,5,6,10));

/**
* Testing inheritance
*/

TEST(Table_inheritance, doCheckInheritance) {
    TableInProtected ti_prot;
    TableInPrivate ti_priv;
}

/**
 * TODO: Solve the libraries issues otherwise gmock it crashes on destruction
 */

/**
 * Mock testing
*/
/*
class MockTable : public Table {
    public:
        MOCK_METHOD0(generateNum, int());
};
*/
/**
TEST(TableClient, Do5Calls) {
    MockTable tableMock;
    MockTable tableMock2;
    EXPECT_CALL(tableMock, generateNum()).Times(AtLeast(5));
    EXPECT_CALL(tableMock2, generateNum()).Times(AtMost(1));
    TableClient* client =  new TableClient(tableMock);
    client->doExecute();
}
 */

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
