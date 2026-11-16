#include "vm.hpp"

#include <limits>
#include <ostream>
#include <type_traits>
#include <utility>

namespace tinvm {
namespace {

const char* error_name(Error error) {
    switch (error) {
    case Error::MissingOperand: return "MissingOperand";
    case Error::StackUnderflow: return "StackUnderflow";
    case Error::TypeMismatch: return "TypeMismatch";
    case Error::DivisionByZero: return "DivisionByZero";
    case Error::IntegerOverflow: return "IntegerOverflow";
    }
    return "UnknownError";
}

std::int64_t calculate(Opcode opcode, std::int64_t a, std::int64_t b) {
    constexpr auto min = std::numeric_limits<std::int64_t>::min();
    constexpr auto max = std::numeric_limits<std::int64_t>::max();
    switch (opcode) {
    case Opcode::ADD:
        if ((b > 0 && a > max - b) || (b < 0 && a < min - b)) {
            throw VMError(Error::IntegerOverflow);
        }
        return a + b;
    case Opcode::SUB:
        if ((b > 0 && a < min + b) || (b < 0 && a > max + b)) {
            throw VMError(Error::IntegerOverflow);
        }
        return a - b;
    case Opcode::MUL:
        if ((a > 0 && ((b > 0 && a > max / b) || (b < 0 && b < min / a))) ||
            (a < 0 && ((b > 0 && a < min / b) || (b < 0 && a < max / b)))) {
            throw VMError(Error::IntegerOverflow);
        }
        return a * b;
    case Opcode::DIV:
        if (b == 0) throw VMError(Error::DivisionByZero);
        if (a == min && b == -1) throw VMError(Error::IntegerOverflow);
        return a / b;
    default:
        throw std::logic_error("Expected an arithmetic opcode");
    }
}

} // namespace

VMError::VMError(Error code) : std::runtime_error(error_name(code)), code_(code) {}

VM::VM(std::vector<Instruction> instructions) : instructions_(std::move(instructions)) {}

void VM::run(std::ostream& output) {
    while (pc_ < instructions_.size()) {
        const auto& instruction = instructions_[pc_];
        switch (instruction.opcode) {
        case Opcode::NOP:
            break;
        case Opcode::HALT:
            return;
        case Opcode::PUSH:
            if (!instruction.a) throw VMError(Error::MissingOperand);
            stack_.push_back(*instruction.a);
            break;
        case Opcode::POP:
            if (stack_.empty()) throw VMError(Error::StackUnderflow);
            stack_.pop_back();
            break;
        case Opcode::ADD:
        case Opcode::SUB:
        case Opcode::MUL:
        case Opcode::DIV: {
            if (stack_.size() < 2) throw VMError(Error::StackUnderflow);
            const auto size = stack_.size();
            const auto* a = std::get_if<std::int64_t>(&stack_[size - 2]);
            const auto* b = std::get_if<std::int64_t>(&stack_[size - 1]);
            if (!a || !b) throw VMError(Error::TypeMismatch);
            const auto result = calculate(instruction.opcode, *a, *b);
            stack_[size - 2] = result;
            stack_.pop_back();
            break;
        }
        case Opcode::PRINT:
            if (stack_.empty()) throw VMError(Error::StackUnderflow);
            std::visit([&output](const auto& value) {
                if constexpr (std::is_same_v<std::decay_t<decltype(value)>, bool>) {
                    output << (value ? "true" : "false");
                } else {
                    output << value;
                }
            }, stack_.back());
            stack_.pop_back();
            output << '\n';
            break;
        }
        ++pc_;
    }
}

} // namespace tinvm
