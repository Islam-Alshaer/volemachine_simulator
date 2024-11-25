#include "Test.h"
#include "iostream"

using namespace std;

Test::Test(const std::string &log_file_name) {
    logfile.open(log_file_name, ios::in | ios::out);
}

void Test::log_test(bool pass, const string &testname) {
    logfile << testname;
    if(pass)
        logfile << ": pass";
    else
        logfile << ": fail";
    logfile << endl;
}

void Test::test_memory_set_cell(int address, string content) {

    Memory memory;
    memory.setCell(address, content);
    string cell = memory.getCell(address);
    string testname = "test_memory_address_: " + to_string(address) + " content :" + content;
    if(cell == content)
        log_test(true, testname);
    else
        log_test(false, testname);

}


void Test::test_clear_memory(int address, string value) {
    Memory memory;
    memory.setCell(address, value);
    memory.clearMemory();
    string testname = "test_clear_memory_";

    //check all elements
    bool all_are_cleared = true;
    for (int i = 0; i <= 255; ++i) {
        if(memory.getCell(i) != "00")
            all_are_cleared = false;
    }
    if(all_are_cleared)
        log_test(true, testname);
    else
        log_test(false, testname);
}


void Test::test_register_set_cell(int address, std::string content) {

    Register aRegister;
    aRegister.setCell(address, content);
    string cell = aRegister.getCell(address);
    string testname = "test_register_address_: " + to_string(address) + " content :" + content;
    if(cell == content)
        log_test(true, testname);
    else
        log_test(false, testname);
}

void Test::test_clear_register(int address, std::string value) {

    Register aRegister;
    aRegister.setCell(address, value);
    aRegister.clearRegister();
    string testname = "test_clear_register_";

    //check all elements
    bool all_are_cleared = true;
    for (int i = 0; i <= 15; ++i) {
        if(aRegister.getCell(i) != "00")
            all_are_cleared = false;
    }

    if(all_are_cleared)
        log_test(true, testname);
    else
        log_test(false, testname);
}



void Test::test_cu_load1(int registeraddress, string register_value, int memoryaddress, string memory_value) {

    Register my_register;
    Memory my_memory;
    CU controlunit(my_memory, my_register);
    my_register.setCell(registeraddress, register_value);
    my_memory.setCell(memoryaddress, memory_value);
    controlunit.Load_register_with_value_in(registeraddress, memoryaddress);

    //checking
    string testname = "test_cu_load_1_" + to_string(registeraddress) + " " + register_value + " " + to_string(memoryaddress) + " " + memory_value;
    if(my_register.getCell(registeraddress) == my_memory.getCell(memoryaddress))
        log_test(true, testname);
    else
        log_test(false, testname);

}


void Test::test_cu_load2(int registeraddress, string valuebefore, string valueafter) {
    //constructing needed objects
    Register my_register;
    Memory my_memory;
    CU controlunit(my_memory, my_register);

    //doing the test
    my_register.setCell(registeraddress, valuebefore);
    controlunit.Load_register_with_value(registeraddress, valueafter);

    //checking and logging
    string testname = "test_cu_load_with_value " + to_string(registeraddress) + " " + valuebefore + " " + valueafter;
    if(my_register.getCell(registeraddress) == valueafter)
        log_test(true, testname);
    else
        log_test(false, testname);

}

void Test::test_store(int registeraddress, std::string register_value, int memoryaddress, std::string memory_value) {
    //constructing needed objects
    Register my_register;
    Memory my_memory;
    CU controlunit(my_memory, my_register);

    //doing the test
    my_register.setCell(registeraddress, register_value);
    my_memory.setCell(memoryaddress, memory_value);
    controlunit.store_content_of_R_in_memory_address_X(registeraddress, memoryaddress);

    //checking and logging test
    string testname = "test_store_" + to_string(registeraddress) + ' ' + register_value + ' ' + to_string(memoryaddress) + ' ' + memory_value;
    if(my_memory.getCell(memoryaddress) == my_register.getCell(registeraddress))
        log_test(true, testname);
    else
        log_test(false, testname);
}

void Test::test_move(int R, int S) {
    //constructing needed objects
    Register my_register;
    Memory my_memory;
    CU controlunit(my_memory, my_register);

    //doing test
    my_register.setCell(R, "33");
    my_register.setCell(S, "23");
    controlunit.move_from_register_R_to_S(R, S);

    //checking and logging test
    string test_name = "test_move";
    if(my_register.getCell(S) == "33")
        log_test(true, test_name);
    else
        log_test(true, test_name);

}


void Test::test_bitwise_OR(int S, int T, string S_content, string T_content, string expected) {
    //constructing needed objects
    Register my_register;
    Memory my_memory;
    ALU alu(my_memory, my_register);

    //doing test
    my_register.setCell(S,  S_content);
    my_register.setCell(T, T_content);
    int R = 8;
    alu.BitWise_OR(8, S, T);

    //checking
    string testname = "test_ALU_S:" + to_string(S) + ' ' + S_content + " T: " + to_string(T) + ' ' + T_content;
    if(my_register.getCell(R) == expected)
        log_test(true, testname);
    else
        log_test(false, testname);
}


void Test::test_shift(string R_content, int shift_key, string expected) {
    //constructing needed objects
    Register my_register;
    Memory my_memory;
    ALU alu(my_memory, my_register);

    //doing test
    int R = 3;
    my_register.setCell(3, R_content);
    alu.shift_the_content(3, shift_key);

    //check
    string testname = "test shift R: " + R_content + " shift key: " + to_string(shift_key) + " expected: " + expected + "and the actual is : " + my_register.getCell(3);
    if(my_register.getCell(3) == expected)
        log_test(true, testname);
    else
        log_test(false, testname);

}

void Test::test_twos_complement(string S_content, string T_content, string expected) {
    //constructing needed objects
    Register my_register;
    Memory my_memory;
    ALU alu(my_memory, my_register);

    //doing the test
    my_register.setCell(6, S_content);
    my_register.setCell(7, T_content);
    alu.add_twos_complement(8, 6, 7);

    //checking
    string testname = "test two complement S content: " + S_content + " T content: " + T_content + " expected: " + expected;
    if(my_register.getCell(8) == expected)
        log_test(true, testname);
    else
        log_test(false, testname);

}

void Test::test_bitwise_XOR(string S_content, string T_content, string expected) {

    //constructing needed objects
    Register my_register;
    Memory my_memory;
    ALU alu(my_memory, my_register);

    //doing the test
    my_register.setCell(6, S_content);
    my_register.setCell(7, T_content);
    alu.bitwiseXOR(8, 6, 7);

    //checking
    string testname = "test bitwiseXOR S content: " + S_content + " T content: " + T_content + " expected: " + expected+ " actual: " + my_register.getCell(8);
    if(my_register.getCell(8) == expected)
        log_test(true, testname);
    else
        log_test(false, testname);

}

void Test::test_bitwise_AND(string S_content, string T_content, string expected) {

    //constructing needed objects
    Register my_register;
    Memory my_memory;
    ALU alu(my_memory, my_register);

    //doing the test
    my_register.setCell(6, S_content);
    my_register.setCell(7, T_content);
    alu.bitwiseAND(8, 6, 7);

    //checking
    string testname = "test_bitwiseAND S content: " + S_content + " T content: " + T_content + " expected: " + expected;
    if(my_register.getCell(8) == expected)
        log_test(true, testname);
    else
        log_test(false, testname);

}

void Test::test_float(std::string S_content, std::string T_content, std::string expected) {

    //constructing needed objects
    Register my_register;
    Memory my_memory;
    ALU alu(my_memory, my_register);

    //doing the test
    my_register.setCell(6, S_content);
    my_register.setCell(7, T_content);
    alu.add_float_representation(8, 6, 7);

    //checking
    string testname = "test_float: S content: " + S_content + " T content: " + T_content + " expected: " + expected + " and actual is : " + my_register.getCell(8);
    if(my_register.getCell(8) == expected)
        log_test(true, testname);
    else
        log_test(false, testname);


}

void Test::test_is_valid_instruction(string instruction, bool expected) {
    Memory memory;
    CPU cpu(memory);

    string testname = "test is instruction valid, instruction : " + instruction + "  ,expected: " + to_string((int)expected);
    if(cpu.is_instruction_valid(instruction) == expected)
        log_test(true, testname);
    else
        log_test(false, testname);

}


/*
 * test_memory_address_: 0 content :AA: pass
test_memory_address_: 15 content :FF: pass
test_memory_address_: 550 content :00: pass
test_clear_memory_: pass
test_clear_memory_: pass
test_register_address_: 0 content :AA: pass
test_register_address_: 12 content :FF: pass
test_register_address_: 235 content :00: pass
test_clear_register_: pass
test_clear_register_: pass
test_cu_load_1_4 AA 155 15: pass
test_cu_load_1_0 A2 0 24: pass
test_cu_load_1_15 A2 255 00: pass
test_cu_load_with_value 0 24 44: pass
test_cu_load_with_value 15 FF 00: pass
test_cu_load_with_value 4 48 FF: pass
test_store_3 32 33 65: pass
test_store_0 00 0 FF: pass
test_store_15 FF 255 A3: pass
test_move: pass
test_move: pass
test_ALU_S:0 A1 T: 1 AA: pass
test_ALU_S:7 12 T: 8 12: pass
test_ALU_S:7 0 T: 8 FF: pass
test_ALU_S:7 23 T: 8 FF: pass
test_ALU_S:7 34 T: 8 67: pass
test shift R: D5 shift key: 2 expected: 75and the actual is : 75: pass
test shift R: A3  shift key: 3 expected: 74and the actual is : 74: pass
test shift R: B6 shift key: 1 expected: 5Band the actual is : 5B: pass
test shift R: FF shift key: 7 expected: FFand the actual is : FF: pass
test shift R: A5 shift key: 0 expected: A5and the actual is : A5: pass
test two complement S content: 20 T content: 10 expected: D0: pass
test two complement S content: 33 T content: 0B expected: C2: pass
test two complement S content: 00 T content: 00 expected: 00: pass
test bitwiseXOR S content: 3A T content: 5C expected: 66: pass
test bitwiseXOR S content: 7D T content: 4B expected: 36: pass
test bitwiseXOR S content: A2 T content: 1F expected: BD: pass
test bitwiseXOR S content: C9 T content: 3E expected: F7: pass
test bitwiseXOR S content: 5F T content: B4 expected: EB: pass
test bitwiseXOR S content: 8E T content: D1 expected: 5F: pass
test_bitwiseAND S content: 7D T content: 4B expected: 49: pass
test_bitwiseAND S content: A2 T content: 1F expected: 02: pass
test_bitwiseAND S content: C9 T content: 3E expected: 08: pass
test_bitwiseAND S content: 5F T content: B4 expected: 14: pass
test_bitwiseAND S content: 8E T content: D1 expected: 80: pass
test_float: S content: 20 T content: 50 expected: 40 and actual is : 40: pass
test_float: S content: 3F T content: 3F expected: 4F and actual is : 4F: pass
test is instruction valid, instruction : N345  ,expected: 0: pass
test is instruction valid, instruction : A345  ,expected: 1: pass
test is instruction valid, instruction : B345  ,expected: 1: pass
test is instruction valid, instruction : C345  ,expected: 1: pass
test is instruction valid, instruction : D345  ,expected: 1: pass
test is instruction valid, instruction : 7345  ,expected: 1: pass
test is instruction valid, instruction : 8345  ,expected: 1: pass
test is instruction valid, instruction : 9345  ,expected: 1: pass
test is instruction valid, instruction : 10345  ,expected: 0: pass
*/