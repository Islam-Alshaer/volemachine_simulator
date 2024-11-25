#include "Test.h"

using namespace std;


int main(){

    Test test("testing_log_file.txt");
    //memory tests

    //testing set_cell and get_cell all at once
    test.test_memory_set_cell(0, "AA");
    test.test_memory_set_cell(15, "FF");
    test.test_memory_set_cell(550, "00");

    //testing clear memory
    test.test_clear_memory(5, "FF");
    test.test_clear_memory(0, "45");

    //register tests

    //testing set cell
    test.test_register_set_cell(0, "AA");
    test.test_register_set_cell(12, "FF");
    test.test_register_set_cell(235, "00");

    //testing clear memory
    test.test_clear_register(3, "C4");
    test.test_clear_register(0, "BB");

    //testing CU

    //test first load function
    test.test_cu_load1(4, "AA", 155, "15");
    test.test_cu_load1(0, "A2", 0, "24");
    test.test_cu_load1(15, "A2", 255, "00");

    //test the other load function
    test.test_cu_load2(0, "24", "44");
    test.test_cu_load2(15, "FF", "00");
    test.test_cu_load2(4, "48", "FF");

    //test store
    test.test_store(3, "32", 33, "65");
    test.test_store(0, "00", 0, "FF"); //should print 00
    test.test_store(15, "FF", 255, "A3");

    //test move
    test.test_move(2, 3);
    test.test_move(0, 15);


    //testing ALU
    test.test_bitwise_OR(0, 1,"A1", "AA", "AB"); //normal
    test.test_bitwise_OR(7, 8,"12", "12", "12"); //number with itself
    test.test_bitwise_OR(7, 8,"0", "FF", "FF"); //0 with something
    test.test_bitwise_OR(7, 8,"23", "FF", "FF"); //FF with something
    test.test_bitwise_OR(7, 8,"34", "67", "77"); //normal test

    test.test_shift("D5", 2, "75");
    test.test_shift("A3 ", 3, "74");
    test.test_shift("B6", 1, "5B");
    test.test_shift("FF", 7, "FF");
    test.test_shift("A5", 0, "A5");


    test.test_twos_complement("20", "10", "D0");
    test.test_twos_complement("33", "0B", "C2");
    test.test_twos_complement("00", "00", "00");

    test.test_bitwise_XOR("3A", "5C", "66");
    test.test_bitwise_XOR("7D", "4B", "36");
    test.test_bitwise_XOR("A2", "1F", "BD");
    test.test_bitwise_XOR("C9", "3E", "F7");
    test.test_bitwise_XOR("5F", "B4", "EB");
    test.test_bitwise_XOR("8E", "D1", "5F");


    test.test_bitwise_AND("7D", "4B", "49");
    test.test_bitwise_AND("A2", "1F", "02");
    test.test_bitwise_AND("C9", "3E", "08");
    test.test_bitwise_AND("5F", "B4", "14");
    test.test_bitwise_AND("8E", "D1", "80");


    test.test_float("20", "50", "40");
    test.test_float("3F", "3F", "4F");

    //test is instruction valid
    test.test_is_valid_instruction("N345", false);
    test.test_is_valid_instruction("A345", true);
    test.test_is_valid_instruction("B345", true);
    test.test_is_valid_instruction("C345", true);
    test.test_is_valid_instruction("D345", true);
    test.test_is_valid_instruction("7345", true);
    test.test_is_valid_instruction("8345", true);
    test.test_is_valid_instruction("9345", true);
    test.test_is_valid_instruction("10345", false);




}