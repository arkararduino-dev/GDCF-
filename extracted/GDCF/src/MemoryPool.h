#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>

// A fixed-size block pool allocator. All memory comes from a single static
// backing buffer so there is no heap fragmentation - well suited to the
// RP2040's limited SRAM. Blocks are all the same size (`blockSize`).
class MemoryPool {
public:
    // backing:    caller-provided buffer
    // bufferSize: total bytes in `backing`
    // blockSize:  size of each allocatable block
    MemoryPool(uint8_t* backing, size_t bufferSize, size_t blockSize);

    // Allocate one block. Returns nullptr if none are free or if `bytes`
    // exceeds the block size.
    void* allocate(size_t bytes = 0);

    // Return a block previously obtained from allocate().
    void free(void* ptr);

    size_t freeBlocks() const { return freeCount; }
    size_t totalBlocks() const { return blockCount; }

private:
    uint8_t* buffer;
    size_t   blockSize;
    size_t   blockCount;
    size_t   freeCount;

    // Intrusive free-list: each free block's first bytes hold a pointer to the
    // next free block.
    struct FreeNode { FreeNode* next; };
    FreeNode* freeList;
};

// Convenience macro to declare a pool with a static backing buffer.
#define GDCF_DECLARE_POOL(name, numBlocks, blkSize)                     \
    static uint8_t name##_backing[(numBlocks) * (blkSize)];             \
    MemoryPool name(name##_backing, sizeof(name##_backing), (blkSize))

#endif
