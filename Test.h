#ifndef TEST_H
#define TEST_H
#include "Machine.h"
#include "ALU.h"
#include "CPU.h"
#include "CU.h"
#include "Memory.h"
#include "Register.h"
#include "fstream"


class Test {
private:
    fstream logfile;
public:
    void setLogfile(const fstream &logfile);

private:
    void log_test(bool pass, const string &testname);
public:
    Test(const string &log_file_name);

    //memory stuff
    void test_memory_set_cell(int address, string content);
    void test_clear_memory(int address, string value);

    //register stuff
    void test_register_set_cell(int address, string content);
    void test_clear_register(int address, string value);

    //control unit stuff
    void test_cu_load1(int registeraddress, string register_value, int memoryaddress, string memory_value);
    void test_cu_load2(int registeraddress, string valuebefore, string valueafter);
    void test_store(int registeraddress, string register_value, int memoryaddress, string memory_value);
    void test_move(int R,  int S);

    //ALU
    void test_bitwise_OR(int S, int T, string S_content, string T_content, string expected);
    void test_shift(string R_content, int shift_key, string expected);
    void test_twos_complement(string S_content, string T_content, string expected);
    void test_bitwise_XOR(string S_content, string T_content, string expected);
    void test_bitwise_AND(string S_content, string T_content, string expected);
    void test_float(string S_content, string T_content, string expected);

    //CPU
    void test_is_valid_instruction(string instruction, bool expected);

};


#endif //TEST_H