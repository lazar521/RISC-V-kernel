#include "../h/Scheduler.h"

_thread* Scheduler::idleThread = nullptr;
_threadList* Scheduler::readyThreads = nullptr;

void Scheduler::put(_thread* thread) {
    Scheduler::readyThreads->put(thread);
}

_thread* Scheduler::get(){
    _thread* retVal = Scheduler::readyThreads->get();

    if(retVal == nullptr){
        retVal = idleThread;
    }

    return retVal;
}

void Scheduler::initScheduler() {
    Scheduler::readyThreads = _threadList::create_threadList();
    thread_create(&Scheduler::idleThread,Scheduler::idleThreadBody, nullptr);
    Scheduler::get();   //thread_create automatically puts new thread in the scheduler, so we need to
}                       //remove the main thread from the scheduler since it is currently running

void Scheduler::idleThreadBody(void *) {
    while(true){
        thread_dispatch();
    }
}
