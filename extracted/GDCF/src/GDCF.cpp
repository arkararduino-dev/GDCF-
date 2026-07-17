#include "GDCF.h"

GDCF::GDCF() : tokensProcessed(0), cycles(0) {}

bool GDCF::begin() {
    // Initialize multicore, DMA, PIO here in full version
    Serial.println("GDCF Initialized on RP2040");
    return true;
}

void GDCF::addNode(Node* node) {
    // Add to graph in full impl
    Serial.print("Added node: "); Serial.println(node->name);
}

void GDCF::executeGraph() {
    // Token execution loop
    tokensProcessed++;
}

void GDCF::sendToken(Token token) {
    router.route(token);
    // Process
}