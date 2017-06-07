# C++ 14 Basics

### Overview
Some snippets of code to refresh the knowledge in C++ and try the new capabilities of C++ 14. 
Intended only to check corner cases.

- Multithreading, pointers, signals, lambdas (cpp/Utils.cpp) 
- Exception handling (cpp/Tables/Table.cpp)
- Stl, iterators, timing, [algorithms](http://en.cppreference.com/w/cpp/algorithm) (cpp/main.cpp) 
- Google Test (cpp/Tables/test/Table\_unittest.cpp)


### Dependency manager (options)
- CPM and Bazel are partially included 
- Try Biicode it seems is the only supported by versioneye
- Install the libraries using apt and include them using CMake and findPackage

### Continuous integration server
Checked github and travis. 
Drawback, you don't have access to a travis shell,
unless you run your own build server. Therefore I needed a new commit per change
that I wanted to try, which was pretty cumbersome. The travis documentation might
help getting further with the possibilites of travis.

### Update cmake
```
wget https://cmake.org/files/v3.8/cmake-3.8.1.tar.gz
tar xvfz cmake-3.8.1.tar.gz
./bootstrap && make && make install
```

### Builds the project with docker (clang and gcc)
```
docker build docker
```

### Builds the project
```
sudo apt-get install clang
sudo apt-get -f install libboost-all-dev libgtest-dev

cmake -rf . // clean
cmake --build . // build 
```
