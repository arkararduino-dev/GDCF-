#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <Arduino.h>

// A Node is a compute element in the dataflow graph. Tokens arrive on its
// input, process() transforms them, and the node may emit a result token by
// returning true and filling `out`.
class Node {
public:
    virtual ~Node() {}

    // Process an incoming token. If the node produces an output token, fill
    // `out` and return true. Return false to consume the token silently.
    virtual bool process(Token& token, Token& out) = 0;

    // Whether the node can accept a token right now (Ready/Valid handshake).
    virtual bool isReady() const { return true; }

    uint8_t id;
    const char* name;

protected:
    Node(uint8_t _id, const char* _name) : id(_id), name(_name) {}
};

#endif
