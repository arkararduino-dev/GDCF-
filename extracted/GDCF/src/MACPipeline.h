#ifndef MACPIPELINE_H
#define MACPIPELINE_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>

// Multiply-accumulate helpers. On RP2040 these compile to the efficient
// single-cycle multiply on the Cortex-M0+.
class MACPipeline {
public:
    MACPipeline();

    // Returns acc + (a * b) using 64-bit accumulation to avoid overflow.
    int32_t multiplyAccumulate(int32_t acc, int32_t a, int32_t b);

    // Dot product of two int32 vectors of length `n`. Accumulates in int64.
    int64_t dot(const int32_t* x, const int32_t* w, size_t n);

    // Reset the internal running accumulator used by step().
    void reset() { accumulator = 0; }

    // Streaming MAC: accumulator += a * b, returns the running total.
    int64_t step(int32_t a, int32_t b);

    int64_t value() const { return accumulator; }

private:
    int64_t accumulator;
};

#endif
