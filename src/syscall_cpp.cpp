#include "../h/syscall_cpp.hpp"


void * operator new(uint64 size) {
    return mem_alloc(size);
}

void operator delete(void * addr) noexcept{
    mem_free(addr);
}

void *operator new[](size_t size) {
    return mem_alloc(size);
}

void operator delete[](void* addr) noexcept {
    mem_free(addr);
}




//              SEMAPHORES

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle,init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
    myHandle = nullptr;
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}



//             THREADS

Thread::Thread (void (*body)(void*), void* arg){
    this->body = body;
    this->arg = arg;
}

Thread::Thread() {
    body = nullptr;
    arg = nullptr;
}

Thread::~Thread() {
    _thread::destroyThread(myHandle);
}

void Thread::join() {
    thread_join(myHandle);
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::start() {
    if(body != nullptr) thread_create(&myHandle,body,arg);
    else thread_create(&myHandle,Thread::threadBodyWrapper,this);

    return 0;
}

int Thread::sleep(time_t time) {
    return time_sleep(time);
}


void Thread::threadBodyWrapper(void* obj) {
    Thread* thread = (Thread*) obj;
    thread->run();
}


//       PERIODIC THREAD

PeriodicThread::PeriodicThread(time_t period) : Thread() {
    this->period = period;
    finished = false;
}

void PeriodicThread::run() {
    while(finished == false){
        periodicActivation();
        time_sleep(period);
    }
}

void PeriodicThread::terminate() {
    finished = true;
}





//          CONSOLE


char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}


