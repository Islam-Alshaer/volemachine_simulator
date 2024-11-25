#include "Machine.h"
#include "fstream"
#include "iomanip"
#include "string"
#include "string.h"
#include "cstring"

//prototypes
void print_from_0_to_F(char hex_numbers[]);

Machine::Machine() : memory(), processor(memory){

}

void Machine::load_file_into_memory(ifstream program_file) {
    const int max_instructions = 256 / 2;
    int number_of_instructions{2};
    string instruction;

    while(program_file >> instruction){
        store_instruction(instruction);
        number_of_instructions++;
        if(number_of_instructions >= max_instructions or program_file.eof())
            break;
    }
}

void Machine::store_instruction(string &instruction){
    static int current_cell = 2;
    for (int i = 0; i < instruction.length(); i += 2) {
        string one_byte(""); //one byte is two hexadicimal digits

        one_byte += instruction[i];
        one_byte += instruction[i + 1];

        memory.setCell(current_cell, one_byte);
        current_cell++;
    }

}

void Machine::complete_execution() {
    while(true){
        try{
            processor.run_next_instruction(memory);
        }
        catch (exception &e){
            const char* haltmessage = "halt execution";
            const char* offboundries = "out of boundries";
            if(strcmp(haltmessage, e.what()) == 0 or strcmp(offboundries, e.what()) == 0)
                break;
        }
    }

}


void Machine::run_single_step() {
    try{
        processor.run_next_instruction(memory);
    }
    catch (const exception& e){
        cout << e.what() << endl;
        throw;
    }
}


void Machine::display_state() {
    print_register();
    print_memory();
}

void Machine::print_register() const{
    Register machine_register;
    machine_register = processor.get_register();
    cout << "register :\n";
    for (int i = 0; i < 16; ++i) {
        cout << "R" << i << ": " << setw(4) << machine_register.getCell(i) << endl;
    }
    cout << endl;
}

void Machine::print_memory() const{
    cout << "memory:\n";
    char hex_numbers[] = {'0', '1' ,'2' ,'3', '4', '5', '6', '7', '8', '9',
                          'A', 'B', 'C', 'D', 'E', 'F'};
    print_from_0_to_F(hex_numbers); //for showing the column number
    int column_pointer{0};
    for (int i = 0; i < 256; ++i) {
        // it's a 16 by 16 matrix
        if(i % 16 == 0) {
            cout << endl;
            cout << setw(2) << hex_numbers[column_pointer] << ' ';
            column_pointer++;
        }
        cout << memory.getCell(i) << ' ';
    }
    cout << endl;
}

void print_from_0_to_F(char hex_numbers[]){
    cout << "  ";
    for (int i = 0; i < 16; ++i) {
        cout << setw(2) << hex_numbers[i] << " ";
    }
}
