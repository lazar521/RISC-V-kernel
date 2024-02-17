#include "../h/_threadList.h"

uint64 const  _threadList::THREAD_LIST_SIZE_IN_BLOCKS = (sizeof(_threadList) + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;

void _threadList::put(_thread * thread) {

    if(thread == nullptr){
        print("\nNullptr was passed to _threadList::put function\n",0);
        return;
    }

    thread->nextThread = nullptr;

    if(tail != nullptr){
        tail->nextThread = thread;
        tail = tail->nextThread;
    }
    else{
        head = thread;
        tail = thread;
    }
}

_thread *_threadList::get() {
    _thread* retVal = nullptr;

    if(head != nullptr){
        retVal = head;

        if(head->nextThread == nullptr){
            tail = nullptr;
            head = nullptr;
        }
        else{
            head = head->nextThread;
        }

        retVal->nextThread = nullptr;
    }

    return retVal;
}

_threadList *_threadList::create_threadList() {
    _threadList* newList = (_threadList*) MemoryAllocator::allocate(THREAD_LIST_SIZE_IN_BLOCKS);
    newList->head = nullptr;
    newList->tail = nullptr;
    return newList;
}

void _threadList::destroy_threadList(_threadList* list) {
    MemoryAllocator::free(list);
}
