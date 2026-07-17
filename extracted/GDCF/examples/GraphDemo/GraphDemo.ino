// GraphDemo - a two-node dataflow pipeline.
// Node 1 doubles the token value and forwards it to Node 2, which adds 100.
#include <GDCF.h>

// A node that applies a fixed arithmetic operation to each token.
class MathNode : public Node {
public:
    enum Op { DOUBLE, ADD100 };

    MathNode(uint8_t id, const char* name, Op op)
        : Node(id, name), operation(op) {}

    bool process(Token& token, Token& out) override {
        uint32_t result = token.data;
        switch (operation) {
            case DOUBLE:  result = token.data * 2;   break;
            case ADD100:  result = token.data + 100; break;
        }

        Serial.print("Node ");
        Serial.print(name);
        Serial.print(": ");
        Serial.print(token.data);
        Serial.print(" -> ");
        Serial.println(result);

        // Emit the result. dstNode is set by the router mapping.
        out = Token(result, token.type, id, /*dst*/0);
        return true;
    }

private:
    Op operation;
};

GDCF gdcf;
MathNode n1(1, "Doubler", MathNode::DOUBLE);
MathNode n2(2, "Adder",   MathNode::ADD100);

void setup() {
    Serial.begin(115200);
    while (!Serial) { /* wait for USB serial */ }

    gdcf.begin();
    gdcf.addNode(&n1);
    gdcf.addNode(&n2);

    // Route tokens leaving node 1 to node 2. Node 2's output has no mapping,
    // so it leaves the graph (final result).
    gdcf.setRoute(1, 2);

    // Inject an initial token addressed to node 1.
    gdcf.sendToken(Token(42, 0, /*src*/0, /*dst*/1));
}

void loop() {
    uint32_t processed = gdcf.executeGraph();
    if (processed > 0) {
        Serial.print("Tokens processed this pass: ");
        Serial.println(processed);
        Serial.print("Total processed: ");
        Serial.println(gdcf.tokensProcessed);
    }
    delay(1000);
}
