#include "Machine.h"
#include "Memory.h"
#include "fstream"
#include "cstring"

using namespace std;

void display_choices(){ //a screaming violation of the open closed principle
    cout << "choose one of the following choices : " << endl;
    cout << "1.load a new program from a file" << endl;
    cout << "2.run a single step" << endl;
    cout << "3.display status of memory and registers" << endl;
    cout << "4.complete execution" << endl;
    cout << "5.turn off the machine" << endl;
}

char minue() {

    display_choices();
    string choice;
    cin >> choice;
    bool is_valid_choice = ( (choice.length() == 1) and (choice[0] <= '5') and (choice[0] >= '1') );
    while (not is_valid_choice){
        display_choices();
        cin >> choice;
        is_valid_choice = ( (choice.length() == 1) and (choice[0] <= '5') and (choice[0] >= '1') );
    }
    return choice[0];
}

ifstream load_file(const string &filename){

    ifstream inputfile(filename);
    if(!inputfile.is_open()){
        throw runtime_error("Failed to open file: " + filename);;
    }
    return inputfile;
}

ifstream choice1(){
    string filename;
    cout << "enter file name : ";
    cin >> filename;
    ifstream inputfilestream;
    try {
        inputfilestream = load_file(filename);
    }
    catch (exception& e){
        cout << e.what() << endl;
        choice1();
    }
    return inputfilestream;
}


int main(void){
    cout << "welcome to our vole machine simulator" << endl;
    Machine volemachine;
    bool is_a_file_loaded = false;
    while(true){
        char choice = minue();
        if(choice == '1'){
            volemachine.load_file_into_memory(choice1());
            is_a_file_loaded = true;
        }
        else if (choice == '2'){
            try {
                if (is_a_file_loaded)
                    volemachine.run_single_step();
                else
                    cout << "you should load a file first bro" << endl;
            }
            catch (exception& e){
                cout << e.what();
                const char* errormessage = "halt execution"; //possible error
                if(strcmp(e.what(), errormessage) == 0) { //the operation is halt
                    is_a_file_loaded = false;
                }
            }
        }
        else if (choice == '3'){
            volemachine.display_state();
        }
        else if (choice == '4'){
            if(not is_a_file_loaded){
                cout <<"you should load a file first bro" << endl;
            }
            else{
                volemachine.complete_execution();
            }
        }
        else if (choice == '5'){
            return 0;
        }

    }

}


/*
 *test case for the whole program:
2300 //R3 = 0
9533 //R5 = R3 XOR R3 = 00 (the register i'll use for printing from now on)
3500 //print the result of R5
2206 //R2 = 6
2710 //R7 = 10
9572 //R5 = R2 XOR R7 = 6 XOR 10 = 16 (hexa values)
3500 //print the result of R5
7527 //R5 = R2 OR R7 = 6 OR 10 = 16
3500 //print the result of R5
8527 //R5 = R2 AND R7 = 6 AND 10 = 00
3500 //print the result of R5
2055 //R0 = 55
2955 //R9 = 55
B926 //jump to halt if R0 == R9 which is true
2544 //R5 = 44 (should be discarded)
3500 //print R5 (should be discarded)
2566 //R5 = 66 (should be discarded)
3500 //print R5 (should be discarded)
C000 //halt
 *
 * */
