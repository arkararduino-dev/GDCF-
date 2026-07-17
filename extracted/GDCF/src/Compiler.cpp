#include "Compiler.h"
#include <string.h>

Compiler::Compiler() : nodes(0), edges(0) {}

bool Compiler::compileGraph(const char* graphDef) {
    nodes = 0;
    edges = 0;
    if (graphDef == nullptr) {
        return false;
    }

    // Count "node:" and "edge:" occurrences in the definition string.
    for (const char* p = graphDef; *p; ++p) {
        if (strncmp(p, "node:", 5) == 0) {
            nodes++;
            p += 4;
        } else if (strncmp(p, "edge:", 5) == 0) {
            edges++;
            p += 4;
        }
    }

    Serial.print("Graph compiled: ");
    Serial.print(nodes);
    Serial.print(" nodes, ");
    Serial.print(edges);
    Serial.println(" edges");
    return true;
}
