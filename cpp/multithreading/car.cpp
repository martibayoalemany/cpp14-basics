//
// Created by username on 09.05.17.
//

#include "car.h"
#include <thread>
#include <sstream>

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


static void checkType() {
    unique_ptr<Car> car = std::unique_ptr<Car> {new Car()};
    car->pthread_create_check();
    cout << car->toString() << endl;

    stringstream sstr;

    sstr << "------------------- " << endl;
    sstr << "Copy assign. " << is_copy_assignable<Car>() << endl;
    sstr << "Copy constr. " << is_copy_constructible<Car>() << endl;
    sstr << "Triv. copy constr. " << is_trivially_copy_constructible<Car>() << endl;
    sstr << "No throw copy constr. " << is_nothrow_copy_constructible<Car>() << endl;
    sstr << "Move constr. " << is_move_constructible<Car>() << endl;
    sstr << "Triv. move constr. " << is_trivially_move_constructible<Car>() << endl;
    sstr << "No throw move constr. " << is_nothrow_move_constructible<Car>() << endl;
    cout << sstr.str() << endl;
}