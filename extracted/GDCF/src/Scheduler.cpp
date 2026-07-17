#include "Scheduler.h"
#include <pico/multicore.h>

Scheduler::Scheduler() : useCore1(false) {}

void Scheduler::schedule(Token& token) {
    // Topological scheduling simulation
    Serial.println("Scheduling token...");
}

// Core1 entry point - waits for work via the inter-core FIFO instead of
// spinning in a busy loop that would lock the core forever.
static void core1_entry() {
    while (true) {
        uint32_t cmd = multicore_fifo_pop_blocking();
        (void)cmd;  // TODO: dispatch scheduled work on Core1
    }
}

void Scheduler::enableMulticore() {
    if (useCore1) return;  // avoid launching Core1 twice
    useCore1 = true;
    multicore_launch_core1(core1_entry);
}