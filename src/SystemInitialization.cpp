#include"../h/MemoryAllocator.h"
#include"../h/_thread.h"
#include"../h/_timer.hpp"
#include"../h/_console.h"

extern "C" void interruptTable();

void initIVTP(){
    uint64 supervisorAddr = (uint64) &interruptTable | 0x1;
    __asm__ volatile ("csrw stvec, %[address]" : : [address] "r" (supervisorAddr ));
}

void displayBootMessage(){
    bool validInput = false;
    char input;

    while(validInput == false){
        print("\nDo you want to enable asynchronous time-sharing? [Y/n]: ",0);
        input = getc();

        if (input == 'y' || input == 'Y' || input == '\r') {
            print("\n=== Asynchronous mode is ENABLED ===\n\n", 0);
            _thread::setAsyncrhonousMode(true);
            validInput = true;
        }
        else if(input == 'n' || input == 'N'){
            print("\n=== Asynchronous mode is DISABLED ===\n\n",0);
            _thread::setAsyncrhonousMode(false);
            validInput = true;
        }
        else{
            print("Wrong input, try again\n",0);
        }
    }

    if(input != '\r') getc();   //clearing the buffer from ENTER
}

void initSystem(){
    initIVTP();
    MemoryAllocator::initMemory();
    Scheduler::initScheduler();
    _thread::initMainThread();
    _timer::resetTimer();
    _console::initConsole();
    displayBootMessage();
}
