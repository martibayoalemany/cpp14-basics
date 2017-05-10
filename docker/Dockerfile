FROM gcc:latest

#RUN cd /root && \
#	wget https://cmake.org/files/v3.8/cmake-3.8.1.tar.gz && \
#	tar xvfz cmake-3.8.1.tar.gz && \
##	cd /root/cmake-3.8.1 && \
#	./bootstrap && make && make install 
RUN   apt-get update && apt-get install cmake -y && cmake --version
#RUN 
    # git clone https://github.com/google/googletest.git && \
    # cd googletest && \
RUN  cd /root && \
       # wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz && \
       # tar xvfz release-1.7.0.tar.gz && \
       # cd /root/googletest-release-1.7.0 && \
       apt-get install libgtest-dev -y && \
	cd /usr/src/googletest/ && \
        cmake -rf . && cmake .  -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON && make && make install    
RUN cd /root && \
    mkdir -p /root/.ssh && \
    ssh-keyscan bitbucket.org >> /root/.ssh/known_hosts && \
    git clone https://bitbucket.org/martibayoalemany/cpp-14-basics.git && \
 
RUN apt-get install clang -y && \  
    cmake -rf .  && \ cmake . -DCMAKE_CXX_COMPILER=`which clang++` &&\
    /root/cpp-14-basics/bin/runUnitTests

RUN cmake -rf .  && \ cmake . -DCMAKE_CXX_COMPILER=`which gcc` 
# TODO: Fix the compilation with gcc
 
 
