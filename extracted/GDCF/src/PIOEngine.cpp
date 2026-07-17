#include "PIOEngine.h"
#include "shift_token.pio.h"  // generated from shift_token.pio by pioasm

PIOEngine::PIOEngine() : pio(pio0), sm(-1), offset(0), ready(false) {}

bool PIOEngine::initTokenTransport(uint pin, PIO pioBlk, float clkdiv) {
    pio = pioBlk;

    // Make sure the program fits in this PIO's instruction memory.
    if (!pio_can_add_program(pio, &shift_token_program)) {
        Serial.println("PIOEngine: no space for program");
        return false;
    }
    offset = pio_add_program(pio, &shift_token_program);

    // Claim a free state machine.
    sm = pio_claim_unused_sm(pio, false);
    if (sm < 0) {
        Serial.println("PIOEngine: no free state machine");
        return false;
    }

    shift_token_program_init(pio, (uint)sm, offset, pin, clkdiv);
    ready = true;
    Serial.println("PIO Token Transport Initialized");
    return true;
}

void PIOEngine::sendWord(uint32_t word) {
    if (ready) {
        pio_sm_put_blocking(pio, (uint)sm, word);
    }
}

bool PIOEngine::available() const {
    if (!ready) {
        return false;
    }
    return !pio_sm_is_rx_fifo_empty(pio, (uint)sm);
}

uint32_t PIOEngine::receiveWord() {
    if (!ready) {
        return 0;
    }
    return pio_sm_get_blocking(pio, (uint)sm);
}
