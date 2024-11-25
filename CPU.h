#pragma once
#include <string>
#include <vector>
#include "Memory.h"
#include "Register.h"
#include "ALU.h"
#include "CU.h"
using namespace std;

class CPU {
private:
    int pc;
    string IR;
    Register machine_register;
    ALU alu;
    CU cu;

    bool fetch(Memory& memory);
    bool is_instruction_valid(string instruction);
    void decode_and_excute();
    friend class Test;

public:
    CPU(Memory &machine_memory);
    void run_next_instruction(Memory memory) ;
    Register get_register() const;
};
