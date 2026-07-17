#ifndef ROUTER_H
#define ROUTER_H

#include "Token.h"
#include <Arduino.h>

class Router {
public:
    Router();
    void route(Token& token);
    void setMapping(uint8_t src, uint8_t dst);
    
private:
    uint8_t routingTable[32]; // Simple mapping
};

#endif