//
// Created by username on 11.05.17.
//

#ifndef CPP14_BASICS_TE_LOCK_GUARD_H
#define CPP14_BASICS_TE_LOCK_GUARD_H


#include <type_traits>
#include <mutex>
#include <chrono>
#include <iostream>
#include "../exceptions/not_implemented_exception.h"


/*
 This code does not compile yet, we use te_lock_guard to fix this here
#define synchronized2(m) \
    for(unique_lock<std::recursive_mutex> lk(m); lk; lk.unlock())
*/

/**
 * synchronized macro dealing with lock guards in a java like way
*/
#define synchronized(m) \
    for(te_lock_guard lk(m); lk; )


namespace detail {

    struct locker_unlocker_base {
        virtual void lock() const = 0;
        virtual void unlock() const = 0;
    };

    template<class Mutex>
    struct locker_unlocker : public locker_unlocker_base  {
        locker_unlocker(Mutex &m) : m_m{&m} {}
        void lock() const { m_m->lock(); }
        void unlock() const { m_m->unlock(); }
        Mutex *m_m;
    };

}

class te_lock_guard  {
public:
    template<class Mutex>
    te_lock_guard(Mutex &m) {
        new (&m_buf) detail::locker_unlocker<Mutex>(m);
    }

    operator bool() const { return true; }

private:
    std::aligned_storage<sizeof(detail::locker_unlocker<std::mutex>), alignof(detail::locker_unlocker<std::mutex>)>::type m_buf;
};


#endif //CPP14_BASICS_TE_LOCK_GUARD_H
