#include "Router.h"

Router::Router() {
    for (uint8_t i = 0; i < TABLE_SIZE; i++) {
        routingTable[i] = GDCF_ROUTE_NONE;
    }
}

void Router::setMapping(uint8_t src, uint8_t dst) {
    if (src < TABLE_SIZE) {
        routingTable[src] = dst;
    }
}

void Router::clearMapping(uint8_t src) {
    if (src < TABLE_SIZE) {
        routingTable[src] = GDCF_ROUTE_NONE;
    }
}

void Router::route(Token& token) {
    if (token.srcNode < TABLE_SIZE) {
        uint8_t dst = routingTable[token.srcNode];
        if (dst != GDCF_ROUTE_NONE) {
            token.dstNode = dst;
        }
    }
}
