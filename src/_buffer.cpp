#include "../h/_buffer.h"

_buffer::_buffer(int cap) {
    capacity = cap;
    sem_open(&spaceAvailable,1000);
    sem_open(&itemAvailable,0);
    sem_open(&mutex,1);
    elements = (int*) mem_alloc(sizeof(int) * cap);
}


void _buffer::put(char newElem) {
    _sem::wait(spaceAvailable);
    _sem::wait(mutex);

    elements[tail] = newElem;
    tail = (tail + 1) % capacity;
    cnt++;

    _sem::signal(mutex);
    _sem::signal(itemAvailable);
}

int _buffer::get() {
    int retVal;

    _sem::wait(itemAvailable);
    _sem::wait(mutex);

    retVal = elements[head];
    head = (head + 1) % capacity;
    cnt--;

    _sem::signal(mutex);
    _sem::signal(spaceAvailable);

    return retVal;
}


bool _buffer::hasElements() {
    return (cnt != 0);
}

bool _buffer::hasSpace() {
    return (capacity != cnt);
}


