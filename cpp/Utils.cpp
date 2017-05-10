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
#include "car.h"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::milliseconds ms;

jmp_buf return_to_top_level;

volatile sig_atomic_t fatal_error_in_progress = 0;

void ouch(int sig) {
    printf("Ouch ! expected signal %d\n",sig);
}

void auch(int sig, siginfo_t* info, void*) {
    if (fatal_error_in_progress)
        printf("Auch !! received signal %d - cod %d - signo %d\n", sig, info->si_code, info->si_signo);
    else
        printf("Auch ! received signal %d - cod %d - signo %d\n", sig, info->si_code, info->si_signo);
    fatal_error_in_progress = 1;

    longjmp (return_to_top_level, 1);

    // It prevents "auch" to re-enter with the same signal
    // signal (sig, SIG_DFL);
    // raise (sig);
}

void Utils::setSignalHandler() {
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
}

void Utils::doMemoryAccess() {
    Utils::setSignalHandler();

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

    // We are gonna produce SIGSEGV
    // -  SIGSEGV - (Signal Segmentation Violation) Invalid access to storage:
    // When a program tries to read or write outside the memory it has allocated.

    char* string_ptr = const_cast<char*>("hello");
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

    // TODO: This does not mask SIGSEGV
    sigprocmask(SIG_BLOCK, newSig, oldSig);
    printSigs("-- new Sigs --", newSig);
    printSigs("-- old Sigs --", oldSig);

    // We access here an invalid memory and we expect a SIGSEGV
    if(setjmp(return_to_top_level) == 0){
        *string_ptr = 'k';
    }
    printf("SIGSEGV does not crash the process, as we use setjmp and longjmp to skip the offending code\n");

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
