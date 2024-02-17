#include "../h/MemoryAllocator.h"

unsigned long const MemoryAllocator::BLK_WITH_HEADER_SZ = MEM_BLOCK_SIZE + sizeof(memHeader);

MemoryAllocator::memHeader* MemoryAllocator::freeHead = nullptr;
bool MemoryAllocator::initialized = false;

void MemoryAllocator::initMemory() {
    freeHead = (memHeader*) HEAP_START_ADDR;
    freeHead->next = nullptr;
    freeHead-> size = ( (unsigned long) HEAP_END_ADDR - (unsigned long) HEAP_START_ADDR) - sizeof(memHeader);
    initialized = true;
}


void* MemoryAllocator::allocate(unsigned long blkCnt) {
    if(!initialized) initMemory();

    memHeader* prev = nullptr;
    memHeader* curr = freeHead;
    memHeader* newHeader;
    unsigned long memoryRest;

    while(curr != nullptr && curr->size < blkCnt * MEM_BLOCK_SIZE){
        prev = curr;                        //curr will be the segment that will be used
        curr = curr->next;                  //prev will be the segment before that
    }

    if(curr == nullptr){
        return nullptr;
    }

    memoryRest = (unsigned long)(curr->size) - (unsigned long)(blkCnt * MEM_BLOCK_SIZE);    //calculate the size of a potential new segment

    if( memoryRest >= BLK_WITH_HEADER_SZ ){     // make a new segment if there is enough space left
        newHeader= (memHeader*) ((char*)curr + blkCnt * MEM_BLOCK_SIZE + sizeof(memHeader)); //insert the new segment into the list
        newHeader->next = curr->next;
        newHeader->size = memoryRest - sizeof(memHeader);

        curr->next = newHeader;
    }

    if(prev == nullptr) freeHead = curr->next;     //reorder the list
    else prev->next = curr->next;

    curr->size = blkCnt * MEM_BLOCK_SIZE;          //adjust size of the allocated block
    curr->next = nullptr;                       //curr->next is now invalid since curr is now an allocated segment
                                                //keep the 'size' field, for when memory needs to be freed
    return (char*)curr + sizeof(memHeader);     //return memory start address but keep the header
}



void MemoryAllocator::free(void *memAddr) {
    memHeader* prev = nullptr;
    memHeader* curr = freeHead;
    memHeader* newSeg = (memHeader*) ( (char*)memAddr -  sizeof(memHeader) );  //calculate header position

    while(curr != nullptr && curr < newSeg){
        prev = curr;
        curr = curr->next;
    }

    if(prev != nullptr){
        if( mergeFreeSegments(&prev,&newSeg) == true ) newSeg = prev;   //reconnect the list based on outcome
        else prev->next = newSeg;
    }
    else freeHead = newSeg;


    if(curr != nullptr) {
        if( mergeFreeSegments(&newSeg,&curr) == true ) newSeg->next = curr->next; //same as above
        else newSeg->next = curr;
    }
    else newSeg->next = nullptr;

}


bool MemoryAllocator::mergeFreeSegments(MemoryAllocator::memHeader** prev, MemoryAllocator::memHeader** next) {
    unsigned int fullPrevSize = (*prev)->size + sizeof(memHeader);
    unsigned int fullNextSize = (*next)->size + sizeof(memHeader);

    if((char*)(*prev) + fullPrevSize == (char*) (*next) ){
        (*prev)->size = fullPrevSize + fullNextSize - sizeof(memHeader);  //calculate new size
        return true;
    }

    return false;
}
