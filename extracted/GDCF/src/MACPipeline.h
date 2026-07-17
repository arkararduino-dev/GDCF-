#ifndef MACPIPELINE_H
#define MACPIPELINE_H

#include <Arduino.h>

class MACPipeline {
public:
    MACPipeline();
    int32_t multiplyAccumulate(int32_t a, int32_t b, int32_t c);
};

#endif