#include "MACPipeline.h"

MACPipeline::MACPipeline() {}

int32_t MACPipeline::multiplyAccumulate(int32_t a, int32_t b, int32_t c) {
    return a + (b * c);  // Simple MAC
}