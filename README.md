# TinVM

A small stack-based virtual machine written in C++17. Requires a C++17 compiler
and GNU Make; no external libraries are needed.

```sh
make          # build ./TinVM
make run      # run the example: 10 + 20, printing 30
make clean    # remove C++ build artifacts
```

The VM lives in `src/vm/`; `src/main.cpp` constructs and runs the example program.
Values are signed 64-bit integers, doubles, owned strings, or booleans.
Instructions have an opcode and three optional operands (`a`, `b`, `c`).

Supported instructions: `NOP`, `HALT`, `PUSH`, `POP`, `ADD`, `SUB`, `MUL`, `DIV`,
and `PRINT`. `PUSH` reads operand `a`; arithmetic consumes two integers and pushes
the result, with the older stack value on the left. Division truncates toward
zero. `PRINT` consumes the top value. Reaching the end of the program also stops
execution. The example sends its diagnostics and VM output to standard error.

`VM::run(std::ostream&)` sends output to the supplied stream and throws `VMError`
for missing operands, stack underflow, type mismatches, division by zero, or
integer overflow. Arithmetic errors preserve both operands and leave the program
counter at the failing instruction. VM storage is managed automatically.
