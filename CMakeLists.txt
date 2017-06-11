cmake_minimum_required(VERSION 3.2.2)

project(cpp14_basics)

if (DEBUG)
    MESSAGE("Cmake building in debug mode")
else()
    MESSAGE("Cmake building in release mode")
endif()

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")        
    set(CMAKE_CXX_FLAGS " -g -O0 -Wall -std=c++14")
    MESSAGE("Using clang")
else()
    set(GCC_COVERAGE_COMPILE_FLAGS " -g -O0 -Wall -lpthread -std=c++14")
    MESSAGE("Not Using clang")
endif()

set(CMAKE_PREFIX_PATH /usr/local;.)
foreach(path ${CMAKE_PREFIX_PATH})
  message("Path: " ${path})
endforeach(path)

find_package(Threads)
#find_package(GTestLocal REQUIRED)
find_package(GTest REQUIRED)

set(SOURCE_FILES
        cpp/utils/Utils.cpp
        cpp/utils/Utils.h
        cpp/utils/compat.cpp
        cpp/Tables/Table.cpp 
        cpp/Tables/Table.h 
        cpp/Tables/Table2.cpp 
        cpp/Tables/Table2.h
        cpp/Tables/OnTheFlyTable.cpp 
        cpp/Tables/OnTheFlyTable.h
        cpp/Tables/RandomTable.cpp 
        cpp/Tables/RandomTable.h 
        cpp/Tables/TableInPrivate.cpp 
        cpp/Tables/TableInPrivate.h
        cpp/Tables/TableInProtected.cpp 
        cpp/Tables/TableInProtected.h 
        cpp/Tables/TableInPrivateChild.cpp
        cpp/Tables/TableInPrivateChild.h 
        cpp/Tables/AbsoluteTable.cpp 
        cpp/Tables/AbsoluteTable.h 
        cpp/Tables/TableClient.cpp 
        cpp/Tables/TableClient.h
        cpp/multithreading/te_lock_guard.cpp 
        cpp/multithreading/te_lock_guard.h 
        cpp/exceptions/not_implemented_exception.cpp 
        cpp/exceptions/not_implemented_exception.h
        cpp/main.cpp)

file(GLOB TEST_FILES
    cpp/Tables/test/*
)
file(GLOB HEADER_FILES
    cpp/Tables/*.h
)

include_directories(cpp14_basics_tests ${GTEST_LIBRARIES} ${HEADER_FILES})

add_executable(cpp14_basics ${SOURCE_FILES})
#add_executable(cpp14_basics_tests ${SOURCE_FILES} ${TEST_FILES})

target_link_libraries(cpp14_basics ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(cpp14_basics_tests ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
