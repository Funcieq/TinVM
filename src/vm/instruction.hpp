#pragma once

#include "opcode.hpp"
#include "value.hpp"

#include <optional>

namespace tinvm {

struct Instruction {
    Opcode opcode;
    std::optional<Value> a = std::nullopt;
    std::optional<Value> b = std::nullopt;
    std::optional<Value> c = std::nullopt;
};

} // namespace tinvm
