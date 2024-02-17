#ifndef PROJECT_BASE_SCHEDULER_H
#define PROJECT_BASE_SCHEDULER_H

#include"_threadList.h"
#include"MemoryAllocator.h"
#include"../h/syscall_c.h"

class _thread;
class _threadList;

class Scheduler {
public:
    static void put(_thread* thread);
    static _thread* get();

    static _thread* idleThread;

    static void initScheduler();

private:
    static _threadList* readyThreads;

    static void idleThreadBody(void*);

};


#endif //PROJECT_BASE_SCHEDULER_H
