# C++ 14 Basics #
A project with some C++14 code basics

The project is cmake based. 
This are some of the commands you might need to install and compile.  

### Update cmake
```
wget https://cmake.org/files/v3.8/cmake-3.8.1.tar.gz
tar xvfz cmake-3.8.1.tar.gz
./bootstrap && make && make install
```

### Builds the project
```
sudo apt-get install clang
sudo apt-get -f install libboost-all-dev libgtest-dev

cmake -rf . // clean
cmake --build . // build 
```