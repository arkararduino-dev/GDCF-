#ifndef PIOENGINE_H
#define PIOENGINE_H

#include <Arduino.h>
#include <hardware/pio.h>

// Drives the shift_token PIO program to transport 32-bit token words out on a
// GPIO pin using the RP2040's PIO block.
class PIOEngine {
public:
    PIOEngine();

    // Load and start the token-transport program.
    //   pin    - output GPIO for the serialized token stream
    //   pioBlk - pio0 (default) or pio1
    //   clkdiv - PIO clock divider
    // Returns false if no state machine / program space is available.
    bool initTokenTransport(uint pin, PIO pioBlk = pio0, float clkdiv = 1.0f);

    // Push a token word into the PIO TX FIFO (blocks if the FIFO is full).
    void sendWord(uint32_t word);

    // True if a completed word is waiting in the RX FIFO.
    bool available() const;

    // Pop a completion word from the RX FIFO (blocks until one is available).
    uint32_t receiveWord();

    bool isReady() const { return ready; }

private:
    PIO  pio;
    int  sm;
    uint offset;
    bool ready;
};

#endif
