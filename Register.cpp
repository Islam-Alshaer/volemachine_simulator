#include "Register.h"

Register::Register() {
    for (int i = 0; i < 16; ++i) {
        register_cells.push_back("00");
    }
}


string Register::getCell(int address) const{
    if(address > 15 or address < 0)
        return "00";
    return register_cells[address];
}

void Register::setCell(const int &address, const string &val) {
    if(address > 15 or address < 0)
        return;
    register_cells[address] = val;
}

void Register::clearRegister() {
    for (int i = 0; i <= 15; ++i) {
        register_cells[i] = "00";
    }
}