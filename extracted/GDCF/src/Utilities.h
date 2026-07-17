#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>
#include "Token.h"

namespace GDCFUtils {
    void printTokenInfo(const Token& t);
    uint32_t getPerformanceCounter();
}

#endif