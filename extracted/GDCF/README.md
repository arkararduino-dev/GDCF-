# GDCF - Graph-Driven Compute Fabric

**Advanced Token-Based Dataflow Execution Engine for Raspberry Pi RP2040**

This library implements a graph-native compute architecture where computation is driven by data tokens rather than traditional program counter execution.

## Features
- Token-based dataflow with Ready/Valid handshake
- Multicore parallel execution (Core 0/1)
- PIO for high-speed token transport
- DMA streaming support
- Dynamic graph scheduling
- MAC pipeline acceleration
- Graph compiler and runtime loading
- Performance counters and debugging

## Hardware Requirements
- Raspberry Pi Pico / Pico W
- Arduino-Pico core by Earle Philhower

## Installation
1. Download or clone this repository.
2. In Arduino IDE: Sketch > Include Library > Add .ZIP Library

## Quick Start
See `examples/GraphDemo/GraphDemo.ino`

## Documentation
See `docs/` folder.

## License
MIT (see LICENSE)