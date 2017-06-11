FROM gcc:latest

RUN wget https://cmake.org/files/v3.8/cmake-3.8.1.tar.gz && \
    tar xvfz cmake-3.8.1.tar.gz && \
    ./bootstrap && make && make install 

#RUN  apt-get update && apt-get install cmake -y && cmake --version

RUN  cd /root && \
     apt-get install libgtest-dev -y && \
	cd /usr/src/googletest/ && \
        cmake -rf . && cmake .  -DBUILD_SHARED_LIBS=ON  &&\
        make && make install

RUN cd /root && \
    # Activate ssh-keyscan for bitbucket based gits
    # mkdir -p /root/.ssh && \
    # ssh-keyscan bitbucket.org >> /root/.ssh/known_hosts && \
    git clone -b github https://github.com/martibayoalemany/cpp14-basics.git && \
    echo `ls -al`
 
RUN wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | apt-key add - && \
    deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.8 main | tee -a /etc/apt/sources.list && \
    apt-get update && \
    apt-get install clang-3.8 -y 

RUN cd /root/cpp14-basics && \
    cmake -rf .  && cmake . -DCMAKE_CXX_COMPILER=`which clang++` && make 

RUN ls -al /root/cpp14-basics/bin


