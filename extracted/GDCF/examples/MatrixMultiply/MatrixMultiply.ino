// MatrixMultiply - demonstrates the MACPipeline dot-product for a small
// matrix-vector multiply (y = A * x), and optionally streams a row through DMA.
#include <GDCF.h>
#include "MACPipeline.h"

#define ROWS 3
#define COLS 3

// 3x3 matrix A and input vector x.
int32_t A[ROWS][COLS] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
int32_t x[COLS] = {1, 0, 2};
int32_t y[ROWS];

MACPipeline mac;

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("MatrixMultiply Example");

    // y[i] = dot(A[i], x)
    for (int i = 0; i < ROWS; i++) {
        y[i] = (int32_t)mac.dot(A[i], x, COLS);
    }

    Serial.println("Result y = A * x:");
    for (int i = 0; i < ROWS; i++) {
        Serial.print("  y[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(y[i]);
    }
    // Expected: y = [7, 16, 25]
}

void loop() {}
