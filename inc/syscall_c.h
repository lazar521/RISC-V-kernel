#ifndef PROJECT_BASE_SYSCALL_C_H
#define PROJECT_BASE_SYSCALL_C_H

#include"../lib/hw.h"
#include"../h/_thread.h"
#include"../h/_sem.h"
#include"../h/_console.h"
#include"../h/printFucntions.h"

class _thread;

typedef _thread* thread_t;
typedef _sem* sem_t;

void* mem_alloc (int size);
int mem_free (void*);
int thread_create(_thread**,void(*)(void*),void*);
int thread_exit();
void thread_dispatch();
void thread_join(_thread* handle);
int sem_open(_sem**,uint32);
int sem_close(_sem*);
int sem_wait(_sem*);
int sem_signal(_sem*);
int time_sleep(time_t);
void putc(char);
char getc();


enum syscallType
{
    MEM_ALLOC_SYSCALL = 0x1,
    MEM_FREE_SYSCALL= 0x2,
    THREAD_CREATE_SYSCALL = 0x11,
    THREAD_EXIT_SYSCALL = 0x12,
    THREAD_DISPATCH_SYSCALL = 0x13,
    THREAD_JOIN_SYSCALL = 0x14,
    SEM_OPEN_SYSCALL = 0x21,
    SEM_CLOSE_SYSCALL = 0x22,
    SEM_WAIT_SYSCALL = 0x23,
    SEM_SIGNAL_SYSCALL = 0x24,
    GETC_SYSCALL = 0x41,
    PUTC_SYSCALL = 0x42,
    THREAD_SLEEP_SYSCALL = 0x31,
};

#endif //PROJECT_BASE_SYSCALL_C_H
