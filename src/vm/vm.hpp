#pragma once

#include "instruction.hpp"

#include <cstddef>
#include <iosfwd>
#include <stdexcept>
#include <vector>

namespace tinvm {

enum class Error {
    MissingOperand,
    StackUnderflow,
    TypeMismatch,
    DivisionByZero,
    IntegerOverflow,
};

class VMError : public std::runtime_error {
public:
    explicit VMError(Error code);
    Error code() const noexcept { return code_; }

private:
    Error code_;
};

class VM {
public:
    explicit VM(std::vector<Instruction> instructions);
    void run(std::ostream& output);

    const std::vector<Value>& stack() const noexcept { return stack_; }
    std::size_t pc() const noexcept { return pc_; }

private:
    std::vector<Instruction> instructions_;
    std::vector<Value> stack_;
    std::size_t pc_ = 0;
};

} // namespace tinvm
