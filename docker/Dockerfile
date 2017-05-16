FROM gcc:latest

RUN  apt-get update && apt-get install cmake -y && cmake --version

RUN  cd /root && \
     apt-get install libgtest-dev -y && \
	cd /usr/src/googletest/ && \
        cmake -rf . && cmake .  -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON &&\
        make && make install

RUN cd /root && \
    mkdir -p /root/.ssh && \
    ssh-keyscan bitbucket.org >> /root/.ssh/known_hosts && \
    git clone -b github https://github.com/martibayoalemany/cpp14-basics.git && \
    echo `ls -al`
 
RUN apt-get install clang -y 

RUN cd /root/cpp14-basics &&\
    cmake -rf .  && cmake . -DCMAKE_CXX_COMPILER=`which clang++` && make 

RUN ls -al /root/cpp14-basics/bin

# TODO: Fix the compilation with gcc
RUN cd /root/cpp14-basics && make clean &&\
    cmake -rf .  && cmake . -DCMAKE_CXX_COMPILER=`which gcc` && make

RUN ls -al /root/cpp14-basics/bin

#-----------------------
# Documentation
#-----------------------
RUN apt-get install doxygen graphviz && \
    cd /root/cpp-14-basics && cmake -rf . -DBUILD_DOCUMENTATION=ON && \
    make doc

#-----------------------
# Bazel
#-----------------------
#RUN echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list && \
#    curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add - && \

#RUN sudo apt-get update && sudo apt-get install bazel && \
#    sudo apt-get upgrade bazel && \
#    sudo apt-get install openjdk-8-jdk && \
#    sudo apt-get install pkg-config zip g++ zlib1g-dev unzip

#------------------------------------------
# Install cmake from source code
#------------------------------------------
# cd /root && \
#	wget https://cmake.org/files/v3.8/cmake-3.8.1.tar.gz && \
#	tar xvfz cmake-3.8.1.tar.gz && \
##	cd /root/cmake-3.8.1 && \
#	./bootstrap && make && make install

#------------------------------------------
# Install googletest from source code
#------------------------------------------
# wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz && \
# tar xvfz release-1.7.0.tar.gz && \
# cd /root/googletest-release-1.7.0 && \

#------------------------------------------
# Install googletest from git
#------------------------------------------
#RUN
    # git clone https://github.com/google/googletest.git && \
    # cd googletest && \
