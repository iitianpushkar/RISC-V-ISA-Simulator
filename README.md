# RISC-V-simulation
Simulating RISC-V in C++ for my better understanding of c++ and computer architecture.

## Current structure

- `src/simulator.cpp` starts the simulator and connects the parts together.
- `include/register/registers.hpp` declares the register file.
- `src/register/registers.cpp` implements register read, write, and dump behavior.
- `Makefile` builds and runs the project with simple commands.

## Build and run

```bash
make
make run
```

To remove generated build files:

```bash
make clean
```
