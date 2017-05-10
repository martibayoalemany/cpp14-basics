cmake_minimum_required(VERSION 3.5)
project(cpp14_basics)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-lpthread -std=c++14")
set (CMAKE_CXX_COMPILER             "/usr/bin/clang++")

if (DEBUG)
    # -Wno-unknown-pragmas -Wno-reorder -Wno-sign-compare -Wno-switch
    MESSAGE("Cmake building in debug mode")
    set(CMAKE_CXX_FLAGS " -g -O0 -Wall -fsanitize=safe-stack -std=c++14")
else()
    MESSAGE("Cmake building in release mode")
    set(CMAKE_CXX_FLAGS "-g -O3 -Wall -std=c++14")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    MESSAGE("Using clang")
else()
    MESSAGE("Not Using clang")
endif()

#find_package(Boost)
find_package(Threads)
find_package(GTest REQUIRED)
include_directories( ${GTEST_INCLUDE_DIRS} )

set(GTEST_BOTH_LIBRARIES /usr/lib/x86_64-linux-gnu/libpthread.so
        /usr/local/lib/libgtest.so
        /usr/local/lib/libgtest_main.so
        /usr/local/lib/libgmock.so
        /usr/local/lib/libgmock_main.so )

set(SOURCE_FILES main.cpp
                    cpp/car.cpp cpp/car.h cpp/Utils.cpp cpp/Utils.h
                    cpp/Tables/Table.cpp cpp/Tables/Table.h cpp/Tables/Table2.cpp cpp/Tables/Table2.h
                    cpp/Tables/test/Table_unittest.cpp cpp/Tables/OnTheFlyTable.cpp cpp/Tables/OnTheFlyTable.h
                    cpp/Tables/RandomTable.cpp cpp/Tables/RandomTable.h cpp/Tables/TableInPrivate.cpp cpp/Tables/TableInPrivate.h
                    cpp/Tables/TableInProtected.cpp cpp/Tables/TableInProtected.h cpp/Tables/TableInPrivateChild.cpp
                    cpp/Tables/TableInPrivateChild.h cpp/Tables/TableInProtectedChild.cpp cpp/Tables/TableInProtectedChild.h
                    cpp/Tables/AbsoluteTable.cpp cpp/Tables/AbsoluteTable.h cpp/Tables/TableClient.cpp cpp/Tables/TableClient.h)

add_executable(cpp14_basics ${SOURCE_FILES})

target_link_libraries(cpp14_basics
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )