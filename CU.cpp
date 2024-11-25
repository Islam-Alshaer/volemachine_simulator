#include "iostream"
#include "CU.h"
#include "CPU.h"
#include "ALU.h"
#include "Memory.h"
#include "Register.h"
#include <regex>
using namespace std;

//constructor should initialize values for pointers for memory and register
CU::CU(Memory &given_memory, Register &given_register) {
    machine_memory = &given_memory;
    machine_register = &given_register;
}

//operation 1
void CU::Load_register_with_value_in(int register_address, int memory_address) {
    string memory_cell_content = machine_memory->getCell(memory_address);
    machine_register->setCell(register_address, memory_cell_content);
}

//operation 2
void CU::Load_register_with_value(int register_address, string value) {
    machine_register->setCell(register_address, value);
}

//operation 3
void CU::store_content_of_R_in_memory_address_X(int R, int X) {
    string register_cell_content = machine_register->getCell(R);
    machine_memory->setCell(X, register_cell_content);
    //if memory address is 0, then print to the screen
    if(X == 0)
        cout << register_cell_content << endl;
}

//operation 4
void CU::move_from_register_R_to_S(int R, int S) {
    string content_of_register_cell = machine_register->getCell(R);
    machine_register->setCell(S, content_of_register_cell);
}

//operation B
void CU::jump_to_instruction_in_address(int R, int memory_address, int &PC) {
    bool register_cell_equals_register_0 = (machine_register->getCell(R) == machine_register->getCell(0) ); //could be a function also :)
    if(register_cell_equals_register_0) {
        PC = memory_address;
    }
}

//operation C
void CU::halt(int& PC) {
    machine_register->clearRegister();
    machine_memory->clearMemory();
    PC = 2;
}
