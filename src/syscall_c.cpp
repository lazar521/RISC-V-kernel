#include"../h/syscall_c.h"


uint64 syscall(uint64 selector,uint64 arg1, uint64 arg2, uint64 arg3,uint64 arg4){
    uint64 retVal;
    asm volatile("ecall");
    asm volatile ("mv %[var], a0" : [var] "=r" (retVal)); //putting a0 (value returned from ecall) into retVal
    return retVal;
}




void* mem_alloc(int size) {
    unsigned long blkCnt = (size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
    return (void*) syscall(MEM_ALLOC_SYSCALL,blkCnt,0,0,0);
}

int mem_free(void* addr){
    syscall(MEM_FREE_SYSCALL,(uint64) addr,0,0,0);
    return 0;
}

int thread_create(_thread** handle,void (*start_routine)(void*), void* arg){
    void* thread_stack = mem_alloc(DEFAULT_STACK_SIZE*2);
    if(thread_stack == nullptr) return -1;
    syscall(THREAD_CREATE_SYSCALL,(uint64) handle,(uint64) start_routine,(uint64) arg,(uint64) thread_stack);
    return 0;
}

int thread_exit(){
    return (int) syscall(THREAD_EXIT_SYSCALL,0,0,0,0);
}

void thread_dispatch() {
    syscall(THREAD_DISPATCH_SYSCALL,0,0,0,0);
}

void thread_join(_thread *handle) {
    syscall(THREAD_JOIN_SYSCALL,(uint64)handle ,0,0,0);
}

int sem_open(_sem** handle, uint32 value){
    return (int) syscall(SEM_OPEN_SYSCALL,(uint64) handle, (uint64) value,0,0);
}

int sem_close(_sem* handle){
    return (int) syscall(SEM_CLOSE_SYSCALL,(uint64) handle, 0, 0, 0);
}

int sem_wait(_sem* handle){
    return (int) syscall(SEM_WAIT_SYSCALL,(uint64) handle, 0, 0, 0);
}

int sem_signal(_sem* handle){
    return (int) syscall(SEM_SIGNAL_SYSCALL,(uint64) handle,0 ,0 ,0);
}

void putc(char character) {
    syscall(PUTC_SYSCALL, (uint64) character, 0, 0, 0);
}

char getc(){
    return (char) syscall(GETC_SYSCALL, 0, 0, 0, 0);
}


int time_sleep(time_t time) {
    if(time > 0) {
        syscall(THREAD_SLEEP_SYSCALL,(uint64) time, 0, 0, 0);
    }
    return 0;
}

