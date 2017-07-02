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

find_package(Threads)
include(build/conanbuildinfo.cmake)

conan_basic_setup()

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
target_link_libraries(cpp14_basics ${CMAKE_THREAD_LIBS_INIT} ${CONAN_LIBS})
