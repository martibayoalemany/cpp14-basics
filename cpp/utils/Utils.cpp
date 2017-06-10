//
// Created by username on 10.05.17.
//

#include "Utils.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <future>
#include <vector>
#include <csetjmp>
#include <memory>
#include <iostream>
#include <thread>

using namespace std;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::milliseconds ms;

jmp_buf long_jump_reference;

volatile sig_atomic_t signal_handling_result = 0;

void signal_action_handler(int sig, siginfo_t* info, void*) {
    std::stringstream log;
    if(signal_handling_result == 0)
      printf("Received signal (first time) %d - cod %d - signo %d\n", sig, info->si_code, info->si_signo);
    else
      printf("Received signal %d - cod %d - signo %d\n", sig, info->si_code, info->si_signo);    
    
    signal_handling_result = 1;
    longjmp(long_jump_reference, 1);
}

void Utils::setSignalHandler() {
    array<int, 3> arr ={{2, 3, 4}};
    cout << arr[2] << endl;    
    struct sigaction act;
    sigemptyset(&act.sa_mask);    
    act.sa_sigaction = signal_action_handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, 0);
}

void Utils::doInvalidMemoryAccess() {
    cout << "doInvalidMemoryAccess" << endl;
    Utils::setSignalHandler();

    string strarr[] = {"aaa", "aaaaa", "aaaaa!", "aaaaa"};
    const char * base = strarr[0].c_str();
    printf("Size of a pointer to a string %ld \n", sizeof(base));
    cout << "First Element: " << base  << endl;

    char* string1 = const_cast<char*>(std::string("hello").c_str());
    printf("%s\n", string1);
    printf("%s\n", (char *) (string1 + 2*sizeof(char)));
    printf("%s\n", (char *) (string1 + 3*sizeof(char)));

    // Access to a valid position
    char* tmp = string1 + 3 *sizeof(char);
    *tmp =  'f';
    printf("%s\n",(char*) tmp);

    char* string_ptr = const_cast<char*>("strgs");
    string_ptr = string_ptr + 6 * sizeof(char*);

    // We set the sigprogmask
    sigset_t* newSig =  new sigset_t {{SIGSEGV}};
    sigset_t* oldSig = nullptr;

    auto printSigs = [=](std::string desc, sigset_t* sig_set_ptr) {
        cout << desc << endl;
        using UL_type = unsigned long *;
        array<UL_type, 2> vec = {{(UL_type) newSig->__val}};
        for (array<unsigned long *, 2>::iterator it = vec.begin(); it != vec.end(); ++it)
            cout << *it << endl;
    };
    
    sigprocmask(SIG_BLOCK, newSig, oldSig);
    printSigs("-- new Sigs --", newSig);
    printSigs("-- old Sigs --", oldSig);
    
    if(setjmp(long_jump_reference) == 0){
        // We should get an SIGSEV signal
        *string_ptr = 'k';
    }

    printf("Enf of invalid memory access\n");

}

void Utils::doMultithreading() {

    std::promise<void> p;
    std::thread t1([&p, &t1] {
        cout << "std thread 1 started " << std::this_thread::get_id() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p.set_value();
        auto start = Time::now();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        auto end = Time::now();
        auto elapsed = end - start;
        cout << "std thread 1 waited " << elapsed.count() << endl;
        cout << "std thread 1 finished " << std::this_thread::get_id() << endl;

    });
    std::thread t2([&p, &t2] {
        cout << "std thread 2 started " << std::this_thread::get_id() << endl;
        auto start = Time::now();
        try {
            p.get_future().get();
            auto end = Time::now();
            auto duration = end - start;
            cout << " set value occurred " << duration.count() << endl;
        }
        catch(...) {
            cout << "Set value has not occurred " << endl;
        }
        cout << "std thread 2 finished " << std::this_thread::get_id() << endl;
    });

    t1.join();
    if(t2.joinable())
        t2.detach();


    // waiting in a condition variable
    // We need to acquire the unique_lock of the mutex before we call to wait or notify_one
    std::condition_variable cv;
    std::mutex m;
    bool flag = false;
    std::thread t3([&cv, &m, &flag] {
        std::unique_lock<std::mutex> lk(m);
        cout << endl << "t3 after unique_lock " << flag << endl;
        auto start = Time::now();
        cv.wait(lk);
        auto end = Time::now();
        auto elapsed = end - start;
        cout << endl << "t3 cv waited " << elapsed.count() << flag << endl;
        // Sleep some time to check that the main thread is blocked
        std::this_thread::sleep_for(std::chrono::duration_cast<ms>(std::chrono::milliseconds(1000)));
        //std::this_thread::sleep_for(2s);
    });

    {
        std::lock_guard<std::mutex> g(m);
        flag = true;
        cv.notify_one();
    }

    cout << "mutex unlocked" << endl;

    // The thread 3 will block one second after we call join
    auto start = Time::now();
    t3.join();
    fsec fs = Time::now() - start;
    cout << "Main thread was paused " << fs.count() << endl;
}

std::string Utils::toString() {
    return this->name;
}

void *PrintThreadId(void *threadid){
    long tid;
    tid = (long)threadid;
    // std::thread::id id = std::this_thread::get_id();
    printf("ThreadId: %ld\n", tid);
}

void Utils::pthread_create_check() {
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

// TODO : See compat.cpp there are some issues regarding gcc
/*
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
*/

