// CNN - a minimal convolution example on GDCF showing a 1D convolution
// (single conv layer with ReLU) implemented as a dataflow node using the
// MACPipeline for the multiply-accumulate kernel.
#include <GDCF.h>
#include "MACPipeline.h"

#define KERNEL_SIZE 3
#define INPUT_SIZE  8

// A 1D convolution node: slides a kernel over the buffered input token stream.
class Conv1DNode : public Node {
public:
    Conv1DNode(uint8_t id, const char* name, const int32_t* k)
        : Node(id, name), kernel(k), filled(0) {
        for (int i = 0; i < KERNEL_SIZE; i++) window[i] = 0;
    }

    bool process(Token& token, Token& out) override {
        // Shift new sample into the sliding window.
        for (int i = 0; i < KERNEL_SIZE - 1; i++) {
            window[i] = window[i + 1];
        }
        window[KERNEL_SIZE - 1] = (int32_t)token.data;
        if (filled < KERNEL_SIZE) filled++;

        if (filled < KERNEL_SIZE) {
            return false;  // not enough samples yet
        }

        // Convolve + ReLU activation.
        MACPipeline mac;
        int32_t acc = (int32_t)mac.dot(window, kernel, KERNEL_SIZE);
        int32_t activated = acc > 0 ? acc : 0;  // ReLU

        Serial.print("[Conv1D] out=");
        Serial.println(activated);

        out = Token((uint32_t)activated, token.type, id, 0);
        return true;
    }

private:
    const int32_t* kernel;
    int32_t window[KERNEL_SIZE];
    int filled;
};

GDCF gdcf;
const int32_t kernel[KERNEL_SIZE] = {1, 0, -1};  // simple edge detector
Conv1DNode conv(1, "Conv1D", kernel);

// Example input feature map.
int32_t input[INPUT_SIZE] = {0, 1, 2, 3, 2, 1, 0, -1};

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    gdcf.begin();
    gdcf.addNode(&conv);

    Serial.println("CNN 1D convolution demo");
    for (int i = 0; i < INPUT_SIZE; i++) {
        gdcf.sendToken(Token((uint32_t)input[i], 0, 0, 1));
        gdcf.executeGraph();
    }
}

void loop() {}
