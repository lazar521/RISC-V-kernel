#ifndef PROJECT_BASE_MEMORYALLOCATOR_H
#define PROJECT_BASE_MEMORYALLOCATOR_H

#include"../lib/hw.h"

extern const void* HEAP_START_ADDR, *HEAP_END_ADDR;

class MemoryAllocator{
public:
    struct memHeader{
        memHeader* next = nullptr;
        unsigned long size;
    };

    static void initMemory();
    static void* allocate(unsigned long blkCnt);
    static void free(void* memAddr);
    static memHeader* freeHead;


private:
    static const unsigned long BLK_WITH_HEADER_SZ;
    static bool initialized;

    static bool mergeFreeSegments(memHeader** prev,memHeader** next);
};

#endif //PROJECT_BASE_MEMORYALLOCATOR_H
