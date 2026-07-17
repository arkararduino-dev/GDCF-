#include "Router.h"

Router::Router() {
    for (int i = 0; i < 32; i++) routingTable[i] = 0;
}

void Router::setMapping(uint8_t src, uint8_t dst) {
    if (src < 32) routingTable[src] = dst;
}

void Router::route(Token& token) {
    if (token.srcNode < 32) {
        token.dstNode = routingTable[token.srcNode];
    }
}