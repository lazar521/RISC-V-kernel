#ifndef KOPIJA_PROJECT_BASE__BUFFER_H
#define KOPIJA_PROJECT_BASE__BUFFER_H

#include"syscall_cpp.hpp"
#include"_sem.h"

class _buffer {
    public:
        explicit _buffer(int);

        void put(char);
        int get();
        bool hasElements();
        bool hasSpace();

    private:
        _sem* spaceAvailable;
        _sem* itemAvailable;
        _sem* mutex;

        int* elements;
        int capacity;
        int head = 0;
        int tail = 0;
        int cnt = 0;
};


#endif //KOPIJA_PROJECT_BASE__BUFFER_H
