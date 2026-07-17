#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Token.h"
#include <Arduino.h>

// Maximum number of nodes and the depth of the pending-token queue.
#ifndef GDCF_MAX_NODES
#define GDCF_MAX_NODES 16
#endif
#ifndef GDCF_TOKEN_QUEUE_SIZE
#define GDCF_TOKEN_QUEUE_SIZE 32
#endif

class Router;  // forward declaration

class Graph {
public:
    Graph();

    bool addNode(Node* node);

    // Enqueue a token for processing. Returns false if the queue is full.
    bool enqueue(const Token& token);

    // Process every pending token once. Output tokens produced by nodes are
    // re-enqueued (routed by `router` if provided). Returns the number of
    // tokens processed. Bounded by the current queue contents so it always
    // terminates.
    uint32_t execute(Router* router = nullptr);

    Node* findNode(uint8_t id) const;
    uint8_t getNodeCount() const { return nodeCount; }
    uint8_t pending() const { return count; }

private:
    Node*   nodes[GDCF_MAX_NODES];
    uint8_t nodeCount;

    Token   queue[GDCF_TOKEN_QUEUE_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;

    bool dequeue(Token& out);
};

#endif
