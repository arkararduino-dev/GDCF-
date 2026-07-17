#ifndef COMPILER_H
#define COMPILER_H

#include <Arduino.h>

class Compiler {
public:
    Compiler();
    bool compileGraph(const char* graphDef);
};

#endif