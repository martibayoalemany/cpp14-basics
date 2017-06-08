# C++ 14 Basics
[![Build Status](https://travis-ci.org/martibayoalemany/cpp14-basics.svg?branch=github)](https://travis-ci.org/martibayoalemany/cpp14-basics)

### Overview
Some snippets of code to refresh the knowledge in C++.

- Multithreading, pointers, signals, lambdas (cpp/Utils.cpp) 
- Exception handling (cpp/Tables/Table.cpp)
- Stl, iterators, timing, [algorithms](http://en.cppreference.com/w/cpp/algorithm) (main.cpp) 
- Google Test (cpp/Tables/test/Table\_unittest.cpp)

### Install cmake
```
wget https://cmake.org/files/v3.8/cmake-3.8.1.tar.gz
tar xvfz cmake-3.8.1.tar.gz
./bootstrap && make && make install
```

### Builds the project with docker (clang and gcc)
```
docker build docker
```

### Builds the project and install google test with apt
```
sudo apt-get install clang
sudo apt-get -f install libboost-all-dev libgtest-dev

cmake -rf . // clean
cmake --build . // build 
```
