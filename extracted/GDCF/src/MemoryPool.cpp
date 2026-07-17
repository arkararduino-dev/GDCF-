#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t size) {}

void* MemoryPool::allocate(size_t bytes) { return malloc(bytes); }
void MemoryPool::free(void* ptr) { ::free(ptr); }