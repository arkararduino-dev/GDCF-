#include "MemoryPool.h"

MemoryPool::MemoryPool(uint8_t* backing, size_t bufferSize, size_t blkSize)
    : buffer(backing), blockSize(blkSize), blockCount(0),
      freeCount(0), freeList(nullptr) {

    // A block must be large enough to hold a free-list pointer.
    if (blockSize < sizeof(FreeNode)) {
        blockSize = sizeof(FreeNode);
    }

    if (buffer == nullptr || blockSize == 0) {
        return;
    }

    blockCount = bufferSize / blockSize;

    // Build the free list, linking every block to the next.
    for (size_t i = 0; i < blockCount; i++) {
        FreeNode* node = reinterpret_cast<FreeNode*>(buffer + i * blockSize);
        node->next = freeList;
        freeList = node;
    }
    freeCount = blockCount;
}

void* MemoryPool::allocate(size_t bytes) {
    if (bytes > blockSize || freeList == nullptr) {
        return nullptr;
    }
    FreeNode* node = freeList;
    freeList = node->next;
    freeCount--;
    return static_cast<void*>(node);
}

void MemoryPool::free(void* ptr) {
    if (ptr == nullptr) {
        return;
    }
    // Reject pointers that are not inside this pool.
    uint8_t* p = static_cast<uint8_t*>(ptr);
    if (p < buffer || p >= buffer + blockCount * blockSize) {
        return;
    }
    FreeNode* node = static_cast<FreeNode*>(ptr);
    node->next = freeList;
    freeList = node;
    freeCount++;
}
