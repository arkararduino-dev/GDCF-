#include "GDCF.h"

GDCF::GDCF() : tokensProcessed(0), cycles(0) {}

bool GDCF::begin() {
    Serial.println("GDCF Initialized on RP2040");
    return true;
}

bool GDCF::addNode(Node* node) {
    bool ok = graph.addNode(node);
    if (ok && node) {
        Serial.print("Added node: ");
        Serial.println(node->name);
    }
    return ok;
}

void GDCF::setRoute(uint8_t src, uint8_t dst) {
    router.setMapping(src, dst);
}

bool GDCF::sendToken(const Token& token) {
    return graph.enqueue(token);
}

uint32_t GDCF::executeGraph() {
    uint32_t processed = graph.execute(&router);
    tokensProcessed += processed;
    cycles++;
    return processed;
}
