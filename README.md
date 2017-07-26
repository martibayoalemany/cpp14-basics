# C++ 14 Basics
[![StackShare](https://img.shields.io/badge/tech-stack-0690fa.svg?style=flat)](https://stackshare.io/graphai/graphai)
[![Build Status](https://travis-ci.org/martibayoalemany/cpp14-basics.svg?branch=master)](https://travis-ci.org/martibayoalemany/cpp14-basics.svg?branch=master)


### Overview
- Multithreading, pointers, signals, lambdas (cpp/Utils.cpp) 
- Exception handling (cpp/Tables/Table.cpp)
- Stl, iterators, timing, [algorithms](http://en.cppreference.com/w/cpp/algorithm) (cpp/main.cpp) 
- Google Test (cpp/Tables/test/Table\_unittest.cpp)

### Conan
```
conan install .. --build googletest
```

### Creates a new travis cofiguration
```
conan new cpp14-basic/1.0.0@user/testings -t -s -cilg -cis
```
