# RISC-V-simulation
Simulating RISC-V in C++ for my better understanding of c++ and computer architecture.

## Current structure

- `src/simulator.cpp` starts the simulator and connects the parts together.
- `include/alu/alu.hpp` declares arithmetic operations.
- `src/alu/alu.cpp` implements arithmetic operations.
- `include/cpu/cpu.hpp` declares the CPU state.
- `src/cpu/cpu.cpp` implements CPU behavior such as program counter updates.
- `include/decoder/decoder.hpp` declares machine-code decoding.
- `src/decoder/decoder.cpp` decodes a small RV32I instruction subset.
- `include/instruction/instruction.hpp` declares the temporary instruction model.
- `src/instruction/instruction.cpp` implements instruction helper constructors.
- `include/program/program.hpp` declares a simple instruction container.
- `src/program/program.cpp` implements instruction fetch by address.
- `include/register/registers.hpp` declares the register file.
- `src/register/registers.cpp` implements register read, write, and dump behavior.
- `Makefile` builds and runs the project with simple commands.

## CPU notes

- The CPU owns the register file.
- The CPU also stores the program counter, usually called `pc`.
- In RV32I, normal instructions are 4 bytes, so the default `pc` step is `pc += 4`.
- The CPU asks the ALU to perform arithmetic, then writes the result back to a register.

## Instruction notes

- An instruction describes one operation the CPU should perform.
- `addi` uses a signed immediate, so values like `-5` are allowed.
- The decoder turns real machine-code bits into this instruction structure.

## Decoder notes

- The decoder currently supports `add`, `sub`, and `addi`.
- `add` and `sub` are R-type instructions.
- `addi` is an I-type instruction with a signed 12-bit immediate.
- Unsupported instruction words throw an error for now.

## Program notes

- A program is a list of instructions stored in order.
- The CPU uses `pc` as an address, so instruction `0` is at address `0`, instruction `1` is at address `4`, instruction `2` is at address `8`, and so on.
- `Cpu::run(...)` keeps fetching and executing instructions until there is no instruction at the current `pc`.
- Passing `true` to `Cpu::run(program, true)` enables a trace that prints each fetched instruction.

## ALU notes

- ALU means arithmetic logic unit.
- For now, this project supports only `add`, `sub`, and `addi` style behavior.
- These are not decoded from real machine code yet; they are direct C++ function calls for learning.

## Register file notes

- RV32I has 32 integer registers: `x0` to `x31`.
- `x0` is hardwired to zero, so writes to `x0` are ignored.
- Registers also have ABI names, such as `zero`, `ra`, `sp`, `a0`, and `t0`.

## Build and run

```bash
make
make run
```

To remove generated build files:

```bash
make clean
```
