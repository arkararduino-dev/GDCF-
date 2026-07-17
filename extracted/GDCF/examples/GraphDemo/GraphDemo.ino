#include <GDCF.h>

class SimpleNode : public Node {
public:
    SimpleNode(uint8_t id, const char* name) : Node(id, name) {}
    void process(Token& token) override {
        Serial.print("Node "); Serial.print(name);
        Serial.print(" processed token data: "); Serial.println(token.data);
        token.data *= 2;  // Simple operation
    }
};

GDCF gdcf;

void setup() {
    Serial.begin(115200);
    gdcf.begin();
    
    SimpleNode* n1 = new SimpleNode(1, "Node1");
    SimpleNode* n2 = new SimpleNode(2, "Node2");
    
    gdcf.addNode(n1);
    gdcf.addNode(n2);
    
    Token t(42, 0, 1, 2);
    gdcf.sendToken(t);
}

void loop() {
    gdcf.executeGraph();
    delay(1000);
}