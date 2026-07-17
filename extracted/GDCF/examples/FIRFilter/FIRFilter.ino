// FIRFilter - a moving-average / FIR filter node built on GDCF.
// Each incoming token sample is filtered against a set of coefficients using
// the MACPipeline, and the filtered result is emitted as a new token.
#include <GDCF.h>
#include "MACPipeline.h"

#define TAPS 4

class FIRNode : public Node {
public:
    FIRNode(uint8_t id, const char* name, const int32_t* coeffs)
        : Node(id, name), coef(coeffs), pos(0) {
        for (int i = 0; i < TAPS; i++) history[i] = 0;
    }

    bool process(Token& token, Token& out) override {
        // Push newest sample into the circular history buffer.
        history[pos] = (int32_t)token.data;
        pos = (pos + 1) % TAPS;

        // Compute the FIR output: sum(coef[i] * history[...]).
        MACPipeline mac;
        mac.reset();
        for (int i = 0; i < TAPS; i++) {
            int idx = (pos + i) % TAPS;  // oldest -> newest
            mac.step(coef[i], history[idx]);
        }
        int32_t y = (int32_t)mac.value();

        Serial.print("FIR in=");
        Serial.print((int32_t)token.data);
        Serial.print(" out=");
        Serial.println(y);

        out = Token((uint32_t)y, token.type, id, 0);
        return true;
    }

private:
    const int32_t* coef;
    int32_t history[TAPS];
    int pos;
};

GDCF gdcf;
const int32_t coeffs[TAPS] = {1, 1, 1, 1};  // simple moving average (x4 gain)
FIRNode fir(1, "FIR", coeffs);

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    gdcf.begin();
    gdcf.addNode(&fir);
}

void loop() {
    // Simulate a sampled signal (a slow ramp).
    static uint32_t sample = 0;
    gdcf.sendToken(Token(sample, 0, 0, 1));
    gdcf.executeGraph();
    sample = (sample + 10) % 200;
    delay(200);
}
