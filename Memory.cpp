#include "Memory.h"

bool is_valid_address(int address){
    if(address > 255 or address < 0)
        return false;
    return true;
}

Memory::Memory(){
    for (int i = 0; i < 256; ++i) {
        memory_cells.push_back("00");
    }
}

void Memory::clearMemory() {
    for (int i = 0; i <= 255; ++i) {
        this->setCell(i, "00");
    }
}

string Memory::getCell(const int &address) const {
    if(not is_valid_address(address))
        return "00";
    string cell_content = memory_cells[address];
    return cell_content;
}

void Memory::setCell(const int &address, string val) {
    if(not is_valid_address(address))
        return;
    memory_cells[address] = val;
}


