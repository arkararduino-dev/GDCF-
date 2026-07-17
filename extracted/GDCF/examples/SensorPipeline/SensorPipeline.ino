// SensorPipeline - a three-stage dataflow pipeline processing analog samples:
//   [ADC read] -> Node 1 (scale) -> Node 2 (threshold/alert)
// Demonstrates chaining nodes via the router.
#include <GDCF.h>

#define SENSOR_PIN A0

// Stage 1: scale a raw ADC reading to millivolts (0-3300 for a 12-bit ADC).
class ScaleNode : public Node {
public:
    ScaleNode(uint8_t id, const char* name) : Node(id, name) {}
    bool process(Token& token, Token& out) override {
        uint32_t mv = (token.data * 3300UL) / 4095UL;
        Serial.print("[Scale] raw=");
        Serial.print(token.data);
        Serial.print(" -> ");
        Serial.print(mv);
        Serial.println(" mV");
        out = Token(mv, token.type, id, 0);
        return true;
    }
};

// Stage 2: raise an alert if the value crosses a threshold.
class ThresholdNode : public Node {
public:
    ThresholdNode(uint8_t id, const char* name, uint32_t th)
        : Node(id, name), threshold(th) {}
    bool process(Token& token, Token& out) override {
        if (token.data > threshold) {
            Serial.print("[Alert] ");
            Serial.print(token.data);
            Serial.print(" mV exceeds ");
            Serial.print(threshold);
            Serial.println(" mV");
        }
        return false;  // terminal node - no output token
    }
private:
    uint32_t threshold;
};

GDCF gdcf;
ScaleNode     scaler(1, "Scale", /*id*/1);
ThresholdNode alarm(2, "Threshold", 2000);  // 2.0 V

void setup() {
    Serial.begin(115200);
    while (!Serial) {}

    gdcf.begin();
    gdcf.addNode(&scaler);
    gdcf.addNode(&alarm);
    gdcf.setRoute(1, 2);  // scaled value flows into the threshold stage
}

void loop() {
    uint32_t raw = analogRead(SENSOR_PIN);
    gdcf.sendToken(Token(raw, 0, 0, 1));
    gdcf.executeGraph();
    delay(500);
}
