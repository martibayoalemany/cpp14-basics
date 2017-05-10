cmake_minimum_required(VERSION 3.5)
project(cpp14_basics)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-lpthread -std=c++14")
set (CMAKE_CXX_COMPILER   "/usr/bin/clang++")
#set (CMAKE_CXX_COMPILER   "/usr/bin/gcc")

if (DEBUG)
    MESSAGE("Cmake building in debug mode")
    #set(CMAKE_CXX_FLAGS " -g -O0 -Wall -fsanitize=safe-stack -std=c++14 -Wsuggest-override")
    set(CMAKE_CXX_FLAGS " -g -O0 -Wall -std=c++1z -Wsuggest-override")
else()
    MESSAGE("Cmake building in release mode")
    set(CMAKE_CXX_FLAGS "-g -O3 -Wall -std=c++1z")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    MESSAGE("Using clang")
else()
    MESSAGE("Not Using clang")
endif()

#find_package(Boost)
find_package(Threads)

#------------------------
# cpp14_basics executable
#-------------------------

set(SOURCE_FILES
        cpp/car.cpp cpp/car.h
        cpp/Tables/Table.cpp cpp/Tables/Table.h cpp/Tables/Table2.cpp cpp/Tables/Table2.h
        cpp/Tables/OnTheFlyTable.cpp cpp/Tables/OnTheFlyTable.h
        cpp/Tables/RandomTable.cpp cpp/Tables/RandomTable.h cpp/Tables/TableInPrivate.cpp cpp/Tables/TableInPrivate.h
        cpp/Tables/TableInProtected.cpp cpp/Tables/TableInProtected.h cpp/Tables/TableInPrivateChild.cpp
        cpp/Tables/TableInPrivateChild.h cpp/Tables/TableInProtectedChild.cpp cpp/Tables/TableInProtectedChild.h
        cpp/Tables/AbsoluteTable.cpp cpp/Tables/AbsoluteTable.h cpp/Tables/TableClient.cpp cpp/Tables/TableClient.h)

add_executable(cpp14_basics main.cpp ${SOURCE_FILES})

target_link_libraries(cpp14_basics ${CMAKE_THREAD_LIBS_INIT})

#------------------------
# unit test executable
#-------------------------
enable_testing()
find_package(GTest REQUIRED)
include_directories( ${GTEST_INCLUDE_DIRS} )


#find_package(PkgConfig)
#pkg_check_modules(GTEST REQUIRED gtest>=1.7.0)
#pkg_check_modules(GMOCK REQUIRED gmock>=1.7.0)

include_directories(
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIRS}
)

set(GTEST_DYNAMIC_LIBRARIES /usr/lib/x86_64-linux-gnu/libpthread.so
        /usr/local/lib/libgtest.so
        /usr/local/lib/libgtest_main.so
        /usr/local/lib/libgmock.so
        /usr/local/lib/libgmock_main.so )

set(GTEST_STATIC_LIBRARIES /usr/lib/x86_64-linux-gnu/libpthread.a
        /usr/local/lib/libgtest.a
        /usr/local/lib/libgtest_main.a
        /usr/local/lib/libgmock.a
        /usr/local/lib/libgmock_main.a )

add_executable(runUnitTests ${SOURCE_FILES} cpp/Tables/test/Table_unittest.cpp)

target_link_libraries(runUnitTests ${GTEST_DYNAMIC_LIBRARIES}
                        ${CMAKE_THREAD_LIBS_INIT}
                        )
add_test(
        NAME runUnitTests
        COMMAND runUnitTests
)
