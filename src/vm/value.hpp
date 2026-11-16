#pragma once

#include <cstdint>
#include <string>
#include <variant>

namespace tinvm {

using Value = std::variant<std::int64_t, double, std::string, bool>;

} // namespace tinvm
