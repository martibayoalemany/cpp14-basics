//
// Created by username on 09.05.17.
//

#include "car.h"
#include <thread>

std::string Car::toString() {
    return this->name;
}

void *PrintThreadId(void *threadid){
    long tid;
    tid = (long)threadid;
    // std::thread::id id = std::this_thread::get_id();
    printf("ThreadId: %ld\n", tid);
}

void Car::pthread_create_check() {
    const int NUM_THREADS = 5;
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintThreadId, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
}