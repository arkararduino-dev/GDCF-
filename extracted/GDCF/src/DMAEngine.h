#ifndef DMAENGINE_H
#define DMAENGINE_H

#include <Arduino.h>
#include <hardware/dma.h>

class DMAEngine {
public:
    DMAEngine();
    bool startTransfer(uint32_t* src, uint32_t* dst, size_t count);
};

#endif