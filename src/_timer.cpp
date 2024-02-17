#include "../h/_timer.hpp"

_thread* _timer::sleepListHead = nullptr;
uint64  _timer::runningThreadTimeLeft = DEFAULT_TIME_SLICE;


void _timer::resetTimer() {
    _timer::runningThreadTimeLeft = DEFAULT_TIME_SLICE;
}

void _timer::decrementTimeSlice() {
    _timer::runningThreadTimeLeft--;

    if(_timer::runningThreadTimeLeft == 0){
        _thread::dispatch();         // longjump calls resetTimer, so every context change resets the timer
    }
}

void _timer::addToSleepList(_thread* thread) {
    thread->nextThread = sleepListHead;
    sleepListHead = thread;
}


void _timer::updateSleepingThreads() {
    _thread* prev = nullptr;
    _thread* curr = sleepListHead;
    _thread* wokeThread;

    while(curr != nullptr){
        curr->sleepTime--;

        if(curr->sleepTime == 0){
            wokeThread = curr;
            curr = curr->nextThread;

            if(prev != nullptr) prev->nextThread = curr;
            else sleepListHead = curr;

            wokeThread->nextThread = nullptr;
            Scheduler::put(wokeThread);
        }
        else{
            prev = curr;
            curr = curr->nextThread;
        }
    }
}
