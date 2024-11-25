#pragma once
#include "Memory.h"
#include "Register.h"
#include "ALU.h"

class CU {
private:
    Memory* machine_memory;
    Register* machine_register;
public:
    CU(Memory &given_memory, Register &given_register);
    void Load_register_with_value_in(int register_address, int memory_address);
    void Load_register_with_value(int register_address, string value);
    void store_content_of_R_in_memory_address_X(int R, int X);
    void move_from_register_R_to_S(int R, int S);
    void jump_to_instruction_in_address(int R, int memory_address, int &PC);
    void halt(int& PC);
    void jump_to_instruction_in_address_D(int R, int memory_address, int &PC);
};