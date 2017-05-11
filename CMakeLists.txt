cmake_minimum_required(VERSION 3.5)
project(cpp14_basics)

if (DEBUG)
    MESSAGE("Cmake building in debug mode")
else()
    MESSAGE("Cmake building in release mode")
endif()

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_COMPILER   "/usr/bin/clang++")
#set (CMAKE_CXX_COMPILER   "/usr/bin/gcc")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # For secure code
    # -fsanitize=safe-stack
    set(ASAN_SYMBOLIZER_PATH "/usr/bin/llvm-symbolizer-3.8")
    set(CMAKE_CXX_FLAGS " -g -O0 -Wall -fsanitize=address -g memory-leak.c -std=c++14 -Wsuggest-override")
    MESSAGE("Using clang")
else()
    set(GCC_COVERAGE_COMPILE_FLAGS "-lpthread -std=c++14")
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

add_executable(cpp14_basics main.cpp ${SOURCE_FILES} cpp/multithreading/te_lock_guard.cpp cpp/multithreading/te_lock_guard.h cpp/exceptions/not_implemented_exception.cpp cpp/exceptions/not_implemented_exception.h)

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
        /usr/local/lib/libgtest_main.so)
# TODO: We got a crash with gmock
#        /usr/local/lib/libgmock.so
#        /usr/local/lib/libgmock_main.so )

set(GTEST_STATIC_LIBRARIES /usr/lib/x86_64-linux-gnu/libpthread.a
        /usr/local/lib/libgtest.a
        /usr/local/lib/libgtest_main.a)
# TODO: We got a crash with gmock
#        /usr/local/lib/libgmock.a
#        /usr/local/lib/libgmock_main.a )

add_executable(runUnitTests ${SOURCE_FILES} cpp/Tables/test/Table_unittest.cpp)

target_link_libraries(runUnitTests ${GTEST_DYNAMIC_LIBRARIES}
                        ${CMAKE_THREAD_LIBS_INIT}
                        )
add_test(
        NAME runUnitTests
        COMMAND runUnitTests
)

#------------------------
# Documentation with doxygen
#-------------------------

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in doc/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()