#ifndef COMPILER_H
#define COMPILER_H

#include <Arduino.h>
#include <stdint.h>

// A very small textual graph-definition parser. It accepts a description of
// the form:
//   "node:1 node:2 edge:1->2"
// and reports how many nodes and edges were found. This is a lightweight
// runtime loader placeholder that can be extended to build a Graph directly.
class Compiler {
public:
    Compiler();

    // Parse `graphDef`. Returns true on success (non-null input).
    bool compileGraph(const char* graphDef);

    uint16_t nodeCount() const { return nodes; }
    uint16_t edgeCount() const { return edges; }

private:
    uint16_t nodes;
    uint16_t edges;
};

#endif
