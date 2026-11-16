#include "vm/vm.hpp"

#include <exception>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    using namespace tinvm;

    try {
        std::vector<Instruction> instructions{
            {Opcode::PUSH, Value{std::int64_t{10}}},
            {Opcode::PUSH, Value{std::int64_t{20}}},
            {Opcode::ADD},
            {Opcode::PRINT},
            {Opcode::HALT},
        };

        std::cerr << "TinVM\nInstructions:\n";
        for (std::size_t i = 0; i < instructions.size(); ++i) {
            const auto& instruction = instructions[i];
            std::cerr << i << ": " << opcode_name(instruction.opcode);
            if (instruction.a) {
                std::visit([](const auto& value) { std::cerr << ' ' << value; }, *instruction.a);
            }
            std::cerr << '\n';
        }

        std::cerr << "Running VM...\n";
        VM vm(std::move(instructions));
        vm.run(std::cerr);
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
}
