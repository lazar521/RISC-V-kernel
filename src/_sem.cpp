#include "../h/_sem.h"

uint64 const _sem::SEM_SIZE_IN_BLOCKS = (sizeof(_sem) + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;

int _sem::open(_sem** handle, uint32 value) {
    _sem* newSem = (_sem*) MemoryAllocator::allocate(SEM_SIZE_IN_BLOCKS);

    newSem->value = value;
    newSem->blockedThreads = _threadList::create_threadList();

    *handle = newSem;

    return 0;
}

int _sem::close(_sem* sem) {
    unblockThreads(sem);
    _threadList::destroy_threadList(sem->blockedThreads);
    MemoryAllocator::free(sem);
    return 0;
}

void _sem::unblockThreads(_sem* sem) {
    _thread* thread;
    do{
        thread = sem->blockedThreads->get();
        if(thread != nullptr){
            thread->returnValueFromSemaphore = -1;
            Scheduler::put(thread);
        }
    } while(thread != nullptr);
}

int _sem::wait(_sem* sem) {
    _thread::running->returnValueFromSemaphore = 0;
    sem->value--;

    if(sem->value < 0){
        sem->blockedThreads->put(_thread::running);
        _thread::block();
    }
    return _thread::running->returnValueFromSemaphore;
}

int _sem::signal(_sem* sem) {
    sem->value++;

    if(sem->value <= 0){
        Scheduler::put(sem->blockedThreads->get());
    }
    return 0;
}














