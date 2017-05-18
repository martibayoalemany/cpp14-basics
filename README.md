# C++ 14 Basics

A project with some C++14 code basics

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
