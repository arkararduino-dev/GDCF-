#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <Arduino.h>

class MemoryPool {
public:
    MemoryPool(size_t size);
    void* allocate(size_t bytes);
    void free(void* ptr);
};

#endif