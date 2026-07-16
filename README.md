
# GDCF - Graph-Driven Compute Fabric

**RP2040 အတွက် Token-based Dataflow Execution Engine**

GDCF သည် ရိုးရာ CPU program counter အစား **data tokens** ကို အသုံးပြု၍ computation ကို မောင်းနှင်တဲ့ ခေတ်မီဆန်းသစ်တဲ့ ဗိသုကာ ဖြစ်ပါတယ်။

## ✨ Features
- Token-based dataflow with Ready/Valid handshake
- Dual-core parallel execution (Core 0 + Core 1)
- PIO နဲ့ မြန်ဆန်တဲ့ token transport
- DMA streaming support
- Dynamic graph scheduling & routing
- MAC pipeline acceleration
- Graph compiler & runtime loading
- Low memory footprint (SRAM optimized)

## 🛠 Hardware Requirements
- Raspberry Pi Pico / Pico W
- Arduino-Pico core (Earle Philhower)

## 📥 Installation
1. Repository ကို download လုပ်ပါ (Code → Download ZIP)
2. Arduino IDE ဖွင့်ပါ → **Sketch → Include Library → Add .ZIP Library**
3. `File → Examples → GDCF` ကနေ ဥပမာတွေ စမ်းကြည့်ပါ

## 🚀 Quick Start
```cpp
#include <GDCF.h>

GDCF gdcf;

void setup() {
  Serial.begin(115200);
  gdcf.begin();
}

void loop() {
  // သင့် graph ကို ဒီမှာ လုပ်ဆောင်ပါ
  gdcf.executeGraph();
}
