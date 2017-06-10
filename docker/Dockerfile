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
 
RUN sudo -s wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key|sudo apt-key add -&& \
    sudo -s deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.8 main | tee -a /etc/apt/sources.list && \
    sudo apt-get install clang-3.8 -y 

RUN cd /root/cpp14-basics &&\
    cmake -rf .  && cmake . -DCMAKE_CXX_COMPILER=`which clang++` && make 

RUN ls -al /root/cpp14-basics/bin
