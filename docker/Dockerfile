FROM gcc:latest

RUN cd /root && \
	wget https://cmake.org/files/v3.8/cmake-3.8.1.tar.gz && \
	tar xvfz cmake-3.8.1.tar.gz && \
	cd /root/cmake-3.8.1 && \
	./bootstrap && make && make install 
RUN apt-get update && apt-get install git wget 
    # git clone https://github.com/google/googletest.git && \
    # cd googletest && \
RUN  cd /root && wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz && \
	tar xvfz release-1.7.0.tar.gz    
RUN cd /root/googletest-release-1.7.0/ && \
	cmake -rf . && cmake -DBUILD_SHARE_LIBS=ON --build . && make && make install
RUN cd /root && \
    git clone git@bitbucket.org:martibayoalemany/cpp-14-basics.git && \
    cd cpp-14-basics && cmake -rf . && cmake --build . && \
    /root/cpp-14-basics/bin/runUnitTests

	 
