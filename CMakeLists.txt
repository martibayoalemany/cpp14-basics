cmake_minimum_required(VERSION 3.2.2)

project(cpp14_basics)

if (DEBUG)
    MESSAGE("Cmake building in debug mode")
else()
    MESSAGE("Cmake building in release mode")
endif()

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

message("COMPILER_ID : " ${CMAKE_CXX_COMPILER_ID})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")        
    set(CMAKE_CXX_FLAGS " -g -O0 -Wall -std=c++14")
    MESSAGE("Using clang")
else()
    set(GCC_COVERAGE_COMPILE_FLAGS " -g -O0 -Wall -lpthread -std=c++14 -ggdb")
    MESSAGE("Not Using clang")
endif()

set(GTEST_INCLUDE_DIRS
    cpp/test
)

set(CMAKE_PREFIX_PATH /usr/local;.)
foreach(path ${CMAKE_PREFIX_PATH})
  message("Path: " ${path})
endforeach(path)

find_package(Threads)
find_package(GTest)
#find_package(GTestLocal REQUIRED)
#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

#set(LOCAL_GTEST_LIBRARY ./modules/googletest/googlemock)
#find_library(GTEST_LIBRARIES 
#                NAMES gtest                      
#                      gtest_main
#                PATHS "${LOCAL_GTEST_LIBRARY}"
#                PATH_SUFFIXES lib)


#find_library(GMOCK_LIBRARY 
#                NAMES gmock                      
#                      gmock_main
#                PATHS "${LOCAL_GTEST_LIBRARY}"
#                PATH_SUFFIXES lib)

file(GLOB_RECURSE SOURCE_FILES
        cpp/*
        )

file(GLOB TEST_FILES
    test/*
)
file(GLOB_RECURSE HEADER_FILES
    cpp/*    
)
include_directories(${HEADER_FILES})
add_executable(cpp14_basics main.cpp ${SOURCE_FILES} ${HEADER_FILES})
#add_executable(cpp14_basics_tests ${SOURCE_FILES} ${TEST_FILES} ${HEADER_FILES})

target_link_libraries(cpp14_basics ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(cpp14_basics_tests ${GTEST_LIBRARIES} ${GMOCK_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
