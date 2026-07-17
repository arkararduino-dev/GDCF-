#ifndef ROUTER_H
#define ROUTER_H

#include "Token.h"
#include <Arduino.h>

// Value in the routing table meaning "no mapping configured".
#define GDCF_ROUTE_NONE 0xFF

class Router {
public:
    Router();

    // Route a token: if a mapping exists for its source node, overwrite the
    // destination. If no mapping is set the token's dstNode is left untouched.
    void route(Token& token);

    void setMapping(uint8_t src, uint8_t dst);
    void clearMapping(uint8_t src);

private:
    static const uint8_t TABLE_SIZE = 32;
    uint8_t routingTable[TABLE_SIZE];
};

#endif
