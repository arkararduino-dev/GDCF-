#include "MACPipeline.h"

MACPipeline::MACPipeline() : accumulator(0) {}

int32_t MACPipeline::multiplyAccumulate(int32_t acc, int32_t a, int32_t b) {
    int64_t result = (int64_t)acc + (int64_t)a * (int64_t)b;
    return (int32_t)result;
}

int64_t MACPipeline::dot(const int32_t* x, const int32_t* w, size_t n) {
    int64_t sum = 0;
    if (x == nullptr || w == nullptr) {
        return 0;
    }
    for (size_t i = 0; i < n; i++) {
        sum += (int64_t)x[i] * (int64_t)w[i];
    }
    return sum;
}

int64_t MACPipeline::step(int32_t a, int32_t b) {
    accumulator += (int64_t)a * (int64_t)b;
    return accumulator;
}
