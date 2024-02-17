#ifndef PROJECT_BASE__THREAD_H
#define PROJECT_BASE__THREAD_H

#include"../lib/hw.h"
#include"../h/Scheduler.h"
#include"../h/_timer.hpp"
#include"../h/MemoryAllocator.h"
#include"../h/printFucntions.h"
#include"../h/syscall_c.h"

class _thread {
public:
    static _thread* running;
    static const uint32 THREAD_SIZE_IN_BLOCKS;
    static bool asyncrhonousMode;

    uint64 sleepTime;
    _thread* nextThread;
    int returnValueFromSemaphore;


    bool isFinished() { return finished; };
    void setFinished(bool val) { finished = val; }

    void static thread_join(_thread*);
    static void destroyThread(_thread*);
    static void threadBodyWrapper();
    static int exit_thread();
    static int createThread(_thread** handle, void (*start_routine)(void*),void* arg,void* stack_space );
    static void dispatch();
    static void initMainThread();
    static void block();
    static void switchToUserMode();
    static void enableInterruptsInKernelMode();
    static void sleep(_thread*, uint64);
    static void setAsyncrhonousMode(bool val){ _thread::asyncrhonousMode = val; };

private:
    static void yield(_thread* oldThread, _thread* newThread );
    static void dropContext();
    static void unblockParentIfWaitingToJoin();


    _thread* parent;
    _thread* childBeingWaitedFor;
    bool isWaitingToJoin;
    void (*body)(void*);
    uint64* stack;
    void* arg;
    bool finished ;
    uint64 registers[34];  //32 GPR and 2 system registers (sepc and sstatus)

};





#endif //PROJECT_BASE__THREAD_H
