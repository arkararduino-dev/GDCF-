#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <Arduino.h>

class Node {
public:
    virtual ~Node() {}
    virtual void process(Token& token) = 0;
    virtual bool isReady() const { return true; }
    
    uint8_t id;
    const char* name;
    
protected:
    Node(uint8_t _id, const char* _name) : id(_id), name(_name) {}
};

#endif