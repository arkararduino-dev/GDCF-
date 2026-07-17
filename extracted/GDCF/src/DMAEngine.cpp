#include "DMAEngine.h"

DMAEngine::DMAEngine() : dmaChannel(-1), claimed(false) {}

DMAEngine::~DMAEngine() {
    if (claimed && dmaChannel >= 0) {
        dma_channel_unclaim(dmaChannel);
    }
}

bool DMAEngine::begin() {
    if (claimed) {
        return true;
    }
    // Grab any free DMA channel (do not panic if none free).
    dmaChannel = dma_claim_unused_channel(false);
    if (dmaChannel < 0) {
        Serial.println("DMAEngine: no free DMA channel");
        return false;
    }
    claimed = true;
    return true;
}

bool DMAEngine::startTransfer(const uint32_t* src, uint32_t* dst, size_t count,
                             bool blocking) {
    if (!claimed && !begin()) {
        return false;
    }
    if (src == nullptr || dst == nullptr || count == 0) {
        return false;
    }

    dma_channel_config c = dma_channel_get_default_config(dmaChannel);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, true);

    dma_channel_configure(
        dmaChannel,
        &c,
        dst,        // write address
        src,        // read address
        count,      // number of 32-bit words
        true        // start immediately
    );

    if (blocking) {
        dma_channel_wait_for_finish_blocking(dmaChannel);
    }
    return true;
}

bool DMAEngine::isBusy() const {
    if (!claimed || dmaChannel < 0) {
        return false;
    }
    return dma_channel_is_busy(dmaChannel);
}

void DMAEngine::wait() const {
    if (claimed && dmaChannel >= 0) {
        dma_channel_wait_for_finish_blocking(dmaChannel);
    }
}
