#ifndef PROJECT_BASE__TIMER_HPP
#define PROJECT_BASE__TIMER_HPP

#include "_thread.h"
#include"../lib/hw.h"

class _thread;

class _timer {
public:
    static void decrementTimeSlice();
    static void resetTimer();
    static void addToSleepList(_thread*);
    static void updateSleepingThreads();
private:
    static _thread* sleepListHead;
    static uint64 runningThreadTimeLeft;
};


#endif //PROJECT_BASE__TIMER_HPP
