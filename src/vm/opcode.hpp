#pragma once

#include <cstdint>
#include <string_view>

namespace tinvm {

enum class Opcode : std::uint8_t { NOP, HALT, PUSH, POP, ADD, SUB, MUL, DIV, PRINT };

constexpr std::string_view opcode_name(Opcode opcode) {
    switch (opcode) {
    case Opcode::NOP: return "NOP";
    case Opcode::HALT: return "HALT";
    case Opcode::PUSH: return "PUSH";
    case Opcode::POP: return "POP";
    case Opcode::ADD: return "ADD";
    case Opcode::SUB: return "SUB";
    case Opcode::MUL: return "MUL";
    case Opcode::DIV: return "DIV";
    case Opcode::PRINT: return "PRINT";
    }
    return "Unknown";
}

} // namespace tinvm
