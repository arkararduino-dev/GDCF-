#include "Graph.h"

Graph::Graph() : nodeCount(0) {}

void Graph::addNode(Node* node) {
    if (nodeCount < 16) {
        nodes[nodeCount++] = node;
    }
}

void Graph::execute() {
    for (uint8_t i = 0; i < nodeCount; i++) {
        // Simplified execution
    }
}