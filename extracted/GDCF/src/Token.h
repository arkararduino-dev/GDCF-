#ifndef TOKEN_H
#define TOKEN_H

#include <Arduino.h>
#include <stdint.h>

struct Token {
    uint32_t data;      // Payload
    uint8_t  type;      // Token type
    uint8_t  srcNode;
    uint8_t  dstNode;
    uint8_t  priority;
    bool     valid;

    Token() : data(0), type(0), srcNode(0), dstNode(0), priority(0), valid(false) {}
    Token(uint32_t d, uint8_t t, uint8_t s, uint8_t dest, uint8_t p = 1)
        : data(d), type(t), srcNode(s), dstNode(dest), priority(p), valid(true) {}
};

#endif