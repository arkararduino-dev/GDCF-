#ifndef DMAENGINE_H
#define DMAENGINE_H

#include <Arduino.h>
#include <hardware/dma.h>

// Thin wrapper around a single RP2040 DMA channel for memory-to-memory
// 32-bit word transfers (e.g. streaming token payloads or tensor data).
class DMAEngine {
public:
    DMAEngine();
    ~DMAEngine();

    // Claim a DMA channel. Call once before startTransfer(). Returns false if
    // no channel is available.
    bool begin();

    // Start a memory-to-memory transfer of `count` 32-bit words.
    // If `blocking` is true, waits for completion before returning.
    bool startTransfer(const uint32_t* src, uint32_t* dst, size_t count,
                       bool blocking = true);

    // Non-blocking status query.
    bool isBusy() const;
    void wait() const;

    int channel() const { return dmaChannel; }

private:
    int  dmaChannel;
    bool claimed;
};

#endif
