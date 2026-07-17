#include "Graph.h"
#include "Router.h"

Graph::Graph() : nodeCount(0), head(0), tail(0), count(0) {}

bool Graph::addNode(Node* node) {
    if (node == nullptr || nodeCount >= GDCF_MAX_NODES) {
        return false;
    }
    nodes[nodeCount++] = node;
    return true;
}

Node* Graph::findNode(uint8_t id) const {
    for (uint8_t i = 0; i < nodeCount; i++) {
        if (nodes[i] && nodes[i]->id == id) {
            return nodes[i];
        }
    }
    return nullptr;
}

bool Graph::enqueue(const Token& token) {
    if (count >= GDCF_TOKEN_QUEUE_SIZE) {
        return false;  // queue full - back-pressure
    }
    queue[tail] = token;
    tail = (tail + 1) % GDCF_TOKEN_QUEUE_SIZE;
    count++;
    return true;
}

bool Graph::dequeue(Token& out) {
    if (count == 0) {
        return false;
    }
    out = queue[head];
    head = (head + 1) % GDCF_TOKEN_QUEUE_SIZE;
    count--;
    return true;
}

uint32_t Graph::execute(Router* router) {
    // Snapshot how many tokens are pending so freshly produced tokens are not
    // processed until the next execute() call. This guarantees termination.
    uint8_t batch = count;
    uint32_t processed = 0;

    Token token;
    for (uint8_t i = 0; i < batch; i++) {
        if (!dequeue(token)) {
            break;
        }

        Node* node = findNode(token.dstNode);
        if (node == nullptr || !node->isReady()) {
            continue;  // no destination or not ready - drop token
        }

        Token out;
        bool hasOutput = node->process(token, out);
        processed++;

        if (hasOutput && out.valid) {
            // The token was emitted from this node; route it onward.
            out.srcNode = node->id;
            if (router) {
                router->route(out);
            }
            enqueue(out);
        }
    }
    return processed;
}
