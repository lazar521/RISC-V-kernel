#include"../h/printFucntions.h"
#include"../h/syscall_c.h"
#include"../h/MemoryAllocator.h"
#include"../h/_thread.h"
#include"../h/_timer.hpp"
#include "../h/syscall_cpp.hpp"
#include"../h/_console.h"


void initSystem();


int userProgram(){
    // add implementation
}


int main() {
    initSystem();

    Thread* userMainThread = new Thread(userProgram, nullptr);

    userMainThread->start();
    userMainThread->join();

    return 0;
}






