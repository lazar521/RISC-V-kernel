#include "../h/MemoryAllocator.h"
#include "../h/syscall_c.h"
#include"../h/_thread.h"
#include"../h/printFucntions.h"
#include"../h/_console.h"

void checkExceptions();
void stopProcessor();
void setUserMode();


extern "C" void EcallAndExceptionsTable(uint64 selector,uint64 arg1,uint64 arg2, uint64 arg3, uint64 arg4){
    checkExceptions();

    if(selector == MEM_ALLOC_SYSCALL){
        MemoryAllocator::allocate((unsigned long)arg1);
    }
    else if(selector == MEM_FREE_SYSCALL){
        MemoryAllocator::free((void*) arg1);
    }
    else if(selector == THREAD_CREATE_SYSCALL){
        _thread::createThread((_thread**) arg1, (void(*)(void*)) arg2,(void*) arg3, (void*) arg4);
    }
    else if(selector == THREAD_EXIT_SYSCALL){
        _thread::exit_thread();
    }
    else if(selector == THREAD_DISPATCH_SYSCALL){
        _thread::dispatch();
    }
    else if(selector == THREAD_JOIN_SYSCALL){
        _thread::thread_join((_thread*)arg1);
    }
    else if(selector == SEM_OPEN_SYSCALL){
        _sem::open((_sem**)arg1, (uint32) arg2);
    }
    else if(selector == SEM_CLOSE_SYSCALL){
        _sem::close((_sem*) arg1);
    }
    else if(selector == SEM_WAIT_SYSCALL){
        _sem::wait((_sem*) arg1);
    }
    else if(selector == SEM_SIGNAL_SYSCALL){
        _sem::signal((_sem*) arg1);
    }
    else if(selector == GETC_SYSCALL){
        _console::getc();
    }
    else if(selector == PUTC_SYSCALL){
        _console::putc((char)arg1);
    }
    else if(selector == THREAD_SLEEP_SYSCALL){
        _thread::sleep(_thread::running,(uint64) arg1);
    }
    else{
        print("\nUnknown reason for ecall\n",0);
        stopProcessor();
    }
}


extern "C" void TimerInterrupt(){
    _timer::updateSleepingThreads();

    if(_thread::asyncrhonousMode == true) {
        _timer::decrementTimeSlice();
    }}


extern "C" void HardwareInterrupt(){
    int interruptNumber = plic_claim();
    plic_complete(interruptNumber);

    if(interruptNumber == _console::INTERRUPT_CODE) {
        _console::processInputStream();
        _console::processOutputStream();
    }
}


// helper functions

inline void stopProcessor(){
    while(true);
}

inline void checkExceptions(){
    uint64 scause;
    asm volatile("csrr t0, scause");
    asm volatile("sd t0, %[var]" : [var] "=m" (scause));

    if(scause == 2) {
        print("\n\nIllegal instruction\n\n",0);
        stopProcessor();
    }
    else if(scause == 5) {
        print("\n\nIllegal read address\n\n",0);
        stopProcessor();
    }
    else if(scause == 7) {
        print("\n\nIllegal write address\n", 0);
        stopProcessor();
    }
}
