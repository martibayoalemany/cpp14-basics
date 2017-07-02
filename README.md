# C++ 14 Basics
[![Build Status](https://travis-ci.org/martibayoalemany/cpp14-basics.svg?branch=master)](https://travis-ci.org/martibayoalemany/cpp14-basics)

### Overview
Some snippets of code to refresh the knowledge in C++.
Intended only to check corner cases.

- Multithreading, pointers, signals, lambdas (cpp/Utils.cpp) 
- Exception handling (cpp/Tables/Table.cpp)
- Stl, iterators, timing, [algorithms](http://en.cppreference.com/w/cpp/algorithm) (cpp/main.cpp) 
- Google Test (cpp/Tables/test/Table\_unittest.cpp)


### Configuration

- It is a CMake project but it has some configuration of the modules at scripts/init_modules.sh

### Use conan
```
conan install .. --build googletest
```
