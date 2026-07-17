#ifndef GDCF_H
#define GDCF_H

#include "Token.h"
#include "Node.h"
#include "Router.h"
#include "Graph.h"
#include <Arduino.h>
#include <pico/multicore.h>
#include <hardware/dma.h>
#include <hardware/pio.h>

class GDCF {
public:
    GDCF();
    bool begin();
    void addNode(Node* node);
    void executeGraph();
    void sendToken(Token token);
    
    // Performance counters
    uint32_t tokensProcessed;
    uint32_t cycles;

private:
    Router router;
    // Simplified graph for demo
};

#endif