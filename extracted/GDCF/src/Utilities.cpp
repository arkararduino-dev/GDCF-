#include "Utilities.h"

void GDCFUtils::printTokenInfo(const Token& t) {
    Serial.print("Token[data=");
    Serial.print(t.data);
    Serial.print(", type=");
    Serial.print(t.type);
    Serial.print(", src=");
    Serial.print(t.srcNode);
    Serial.print(", dst=");
    Serial.print(t.dstNode);
    Serial.print(", prio=");
    Serial.print(t.priority);
    Serial.print(", valid=");
    Serial.print(t.valid ? "true" : "false");
    Serial.println("]");
}

uint32_t GDCFUtils::getPerformanceCounter() {
    return micros();
}
