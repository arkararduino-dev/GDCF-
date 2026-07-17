#include "Utilities.h"

void GDCFUtils::printTokenInfo(const Token& t) {
    Serial.print("Token data: "); Serial.println(t.data);
}

uint32_t GDCFUtils::getPerformanceCounter() {
    return millis();
}