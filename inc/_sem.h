#ifndef PROJECT_BASE__SEM_H
#define PROJECT_BASE__SEM_H

#include"../lib/hw.h"
#include"../h/_threadList.h"
#include"../h/Scheduler.h"

class _threadList;

class _sem {
public:
    static const uint64 SEM_SIZE_IN_BLOCKS;

    static int open(_sem**, uint32);
    static int close(_sem*);


    static int wait(_sem* );
    static int signal(_sem* );


private:
    static void unblockThreads(_sem *sem);

    int value;
    _threadList* blockedThreads;
};


typedef _sem* sem_t;


#endif //PROJECT_BASE__SEM_H
