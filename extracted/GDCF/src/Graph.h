#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <Arduino.h>

class Graph {
public:
    Graph();
    void addNode(Node* node);
    void execute();
    
private:
    Node* nodes[16];
    uint8_t nodeCount;
};

#endif