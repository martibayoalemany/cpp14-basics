//
// Created by username on 10.05.17.
//

#include "Utils.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <future>
#include "car.h"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::milliseconds ms;


void ouch(int sig) {
    printf("Ouch ! expected signal %d\n",sig);
}

void auch(int sig, siginfo_t* info, void*) {
    printf("Auch ! received signal %d - cod %d - signo %d ", sig, info->si_code, info->si_signo);
}

void Utils::doHandleSignals(bool is_active) {
    array<int, 3> arr ={{2, 3, 4}};
    cout << arr[2] << endl;

    string strarr[] = {"hello", "world", "hello!", "worldsss"};
    cout << strarr->length() << endl;

    struct sigaction act;
    sigemptyset(&act.sa_mask);
    //act.sa_handler = ouch;
    act.sa_sigaction = auch;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, 0);
    sigaction(SIGABRT, &act, 0);

    // -  SIGSEGV - (Signal Segmentation Violation) Invalid access to storage:
    // When a program tries to read or write outside the memory it has allocated.
    // ---
    // - SIGABRT - (Signal Abort) Abnormal termination, such as is initiated by the abort function.
    // signal(SIGSEGV, ouch);

    // Raises signals to be processed by the event handlers
    if(is_active)
        raise(SIGSEGV);

}

void Utils::doMemoryAccess() {
    string strarr[] = {"hello", "world", "hello!", "worldsss"};
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

    // Access to an invalid position seems to work
    char* string_ptr = "hello" ;
    string_ptr = string_ptr + 6 * sizeof(char*);
    *string_ptr = 'k';
    printf("%s\n",(char*) string_ptr);

}

void Utils::doMultithreading() {

    std::promise<void> p;
    std::thread t1([&p, &t1] {
        cout << "std thread 1 started " << std::this_thread::get_id() << endl;
        std::this_thread::sleep_for(1s);
        p.set_value();
        auto start = Time::now();
        std::this_thread::sleep_for(2s);
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

void Utils::checkCarCreation() {
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
