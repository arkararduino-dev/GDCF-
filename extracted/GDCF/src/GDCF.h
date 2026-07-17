#ifndef GDCF_H
#define GDCF_H

#include "Token.h"
#include "Node.h"
#include "Router.h"
#include "Graph.h"
#include <Arduino.h>

class GDCF {
public:
    GDCF();

    bool begin();

    // Register a node in the compute graph. Returns false if the graph is full.
    bool addNode(Node* node);

    // Configure routing: tokens leaving `src` are forwarded to `dst`.
    void setRoute(uint8_t src, uint8_t dst);

    // Inject a token into the graph for processing on the next executeGraph().
    bool sendToken(const Token& token);

    // Run one execution pass over all pending tokens. Returns tokens processed.
    uint32_t executeGraph();

    // Performance counters
    uint32_t tokensProcessed;
    uint32_t cycles;

    Router& getRouter() { return router; }
    Graph&  getGraph()  { return graph; }

private:
    Router router;
    Graph  graph;
};

#endif
