#pragma once
#include "CPU.h"
#include "iostream"
using namespace std;


class Machine {

private:
    CPU processor;
    Memory memory;
    void print_register() const;
    void print_memory() const;
    void store_instruction(string &instruction);
public:
    Machine();
    void load_file_into_memory(ifstream program_file);
    void display_state();
    void run_single_step();
    void complete_execution();
};