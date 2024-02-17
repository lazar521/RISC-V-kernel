#ifndef PROJECT_BASE__THREADLIST_H
#define PROJECT_BASE__THREADLIST_H

#include"_thread.h"
#include"printFucntions.h"

class _thread;

class _threadList {
public:
    static const uint64 THREAD_LIST_SIZE_IN_BLOCKS;


    _thread* get();
    void put(_thread*);
    static _threadList* create_threadList();
    static void destroy_threadList(_threadList*);
private:
    _thread* head = nullptr;
    _thread* tail = nullptr;

};


#endif //PROJECT_BASE__THREADLIST_H
