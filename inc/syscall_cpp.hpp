#ifndef PROJECT_BASE_SYSCALL_CPP_HPP
#define PROJECT_BASE_SYSCALL_CPP_HPP


#include "syscall_c.h"
#include"_thread.h"
#include"_sem.h"
#include"../lib/console.h"

class _thread;
class _sem;

typedef _sem* sem_t;
typedef _thread* thread_t;


void* operator new (size_t);
void operator delete (void*) noexcept;
void* operator new[] (size_t);
void operator delete[] (void*) noexcept;


class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    void join();
    static void dispatch ();
    static int sleep (time_t);
protected:
    virtual void run () {}

    Thread ();

private:
    thread_t myHandle;
    void (*body)(void*); void* arg;

    static void threadBodyWrapper(void* obj);
};


class Semaphore {
public:
    explicit Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
private:
    sem_t myHandle;
};

class PeriodicThread : public Thread {
public:
    void terminate();

protected:
    PeriodicThread (time_t period);

    virtual void periodicActivation() {};

    void run() override;
private:
    time_t period;
    bool finished;
};


class Console {
public:
    static char getc();
    static void putc(char);
};





#endif //PROJECT_BASE_SYSCALL_CPP_HPP
