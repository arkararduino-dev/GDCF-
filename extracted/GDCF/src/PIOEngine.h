#ifndef PIOENGINE_H
#define PIOENGINE_H

#include <Arduino.h>
#include <hardware/pio.h>

class PIOEngine {
public:
    PIOEngine();
    void initTokenTransport();
};

#endif