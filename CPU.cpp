#include "CPU.h"
#include "regex"
//prototypes
int get_memory_address(string IR);


CPU::CPU(Memory &machine_memory):
    cu(machine_memory, machine_register), alu(machine_memory, machine_register), pc(2){
}

void CPU::run_next_instruction(Memory memory) {
    if(not fetch(memory)){ //sorry for this bad code practice, this actually means fetch and check if it's done correctly
        if(pc > 255)
            throw runtime_error("out of boundries");
        else
            throw runtime_error("instruction is not valid, could not fetch");
    }
    else{ //that means we have already fetched
        try{
            decode_and_excute();
        }
        catch (exception& e){
            throw runtime_error(e.what());
        }
    }
}

bool CPU::fetch(Memory &memory) {

    for(int i = 0; i < 2; i++) {
        IR += memory.getCell(pc);
        pc++; //run next step
    }

    if(not is_instruction_valid(IR) or pc > 255){
        IR.clear();
        return false;
    }

    return true;
}

bool CPU::is_instruction_valid(string instruction) {
    regex pattern("^[1-9ABCD]{1}[0-9A-F]{3}$");
    if(regex_match(instruction, pattern))
        return true;
    return false;
}


void CPU::decode_and_excute() { // I am truly ashamed to make one function this long : <

    char operation_code = IR[0];
    string hex_R;
    hex_R += IR[1];
    int R = stoi(hex_R, 0, 16);


    if(operation_code == '1'){ //load with value in
        int memory_address = get_memory_address(IR);
        cu.Load_register_with_value_in(R, memory_address);
    }
    else if(operation_code == '2'){ //load with value
        string value = IR.substr(2);
        cu.Load_register_with_value(R, value);
    }
    else if(operation_code == '3'){ // store
        string string_memory_address = IR.substr(2);
        int x = stoi(string_memory_address, 0, 16);
        cu.store_content_of_R_in_memory_address_X(R, x);
    }
    else if (operation_code == '4'){ //move
        string third;
        third += IR[2];
        R = stoi(third, 0, 16); // very counterintuitive, but it's proffessor's fault :)
        string fourth;
        fourth += IR[3];
        int S = stoi(fourth, 0, 16);
        cu.move_from_register_R_to_S(R, S);
    }
    else if (operation_code == '5'){ //two's complement
        string string_s;
        string_s += IR[2];
        string string_t;
        string_t += IR[3];
        int S = stoi(string_s, 0, 16);
        int T = stoi(string_t, 0, 16);
        alu.add_twos_complement(R, S, T);
    }
    else if (operation_code == '6'){ //float
        string string_s;
        string_s += IR[2];
        string string_t;
        string_t += IR[3];
        int S = stoi(string_s, 0, 16);
        int T = stoi(string_t, 0, 16);
        alu.add_float_representation(R, S, T);
    }
    else if(operation_code == '7'){ // bitwise OR
        string string_s;
        string_s += IR[2];
        string string_t;
        string_t += IR[3];
        int S = stoi(string_s, 0, 16);
        int T = stoi(string_t, 0, 16);
        alu.BitWise_OR(R, S, T);
    }
    else if (operation_code == '8'){ //bitwise AND
        string string_s;
        string_s += IR[2];
        string string_t;
        string_t += IR[3];
        int S = stoi(string_s, 0, 16);
        int T = stoi(string_t, 0, 16);
        alu.bitwiseAND(R, S, T);
    }
    else if (operation_code == '9'){ //bitwise XOR
        string string_s;
        string_s += IR[2];
        string string_t;
        string_t += IR[3];
        int S = stoi(string_s, 0, 16);
        int T = stoi(string_t, 0, 16);
        alu.bitwiseXOR(R, S, T);
    }
    else if (operation_code == 'A'){ //Rotate
        string string_rotation_key;
        string_rotation_key += IR[3];
        int rotation_key = stoi(string_rotation_key, 0, 16);
        alu.shift_the_content(R, rotation_key);
    }
    else if (operation_code == 'B'){ //jump
        string string_memory_address = IR.substr(2);
        int x = stoi(string_memory_address, 0, 16);
        cu.jump_to_instruction_in_address(R, x, pc);
    }
    else if (operation_code == 'D'){ //bonus jump
        string string_memory_address = IR.substr(2);
        int x = stoi(string_memory_address, 0, 16);
        cu.jump_to_instruction_in_address_D(R, x, pc);
    }
    else if (operation_code == 'C'){ //halt
        cu.halt(pc);
        throw runtime_error("halt execution");
    }

    IR.clear();
}

int get_memory_address(string IR){
    string hexa_memory_address = IR.substr(2);
    int memory_address = stoi(hexa_memory_address, 0, 16);
    return memory_address;
}


Register CPU::get_register() const{
    return this->machine_register;
}