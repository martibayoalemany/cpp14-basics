cmake_minimum_required(VERSION 3.5)
project(cpp14_basics)

#find_package(Boost)
find_package(Threads)

#------------------------------------------------------------------------------
# Source code
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-lpthread")
set(GCC_COVERAGE_COMPILE_FLAGS "-std=gnu++11")
set(SOURCE_FILES main.cpp cpp/car.cpp cpp/car.h)
add_executable(cpp14_basics ${SOURCE_FILES})

target_link_libraries(cpp14_basics
        ${CMAKE_THREAD_LIBS_INIT}
        ${CPM_LIBRARIES})


