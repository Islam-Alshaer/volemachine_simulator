#include "ALU.h"
#include "CU.h"
#include "Register.h"
#include <map>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;


map<std::string, char> decAndHexMap = {
        {"0000", '0'},
        {"0001", '1'},
        {"0010", '2'},
        {"0011", '3'},
        {"0100", '4'},
        {"0101", '5'},
        {"0110", '6'},
        {"0111", '7'},
        {"1000", '8'},
        {"1001", '9'},
        {"1010", 'A'},
        {"1011", 'B'},
        {"1100", 'C'},
        {"1101", 'D'},
        {"1110", 'E'},
        {"1111", 'F'}
};

map<char, string> hexAndBinMap = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"}
};

map<std::string, int> Bintodec3bits = {
        {"000", 0},
        {"001", 1},
        {"010", 2},
        {"011", 3},
        {"100", 4},
        {"101", 5},
        {"110", 6},
        {"111", 7}
};

map<int, std::string> DecToBinforFloat = {
        {0, "0"},
        {1, "1"},
        {2, "10"},
        {3, "11"},
        {4, "100"},
        {5, "101"},
        {6, "110"},
        {7, "111"}
};

string shift_func(string Str_Bin , int X){
    string Shifted_Str = "";
    int remaining_size = 8-X ;
    Shifted_Str += Str_Bin.substr(remaining_size,X);
    Shifted_Str += Str_Bin.substr(0,remaining_size);


    return Shifted_Str;
}

string Or_func(string strS,string strT){
    string Or_str = "";
    for (int i = 0; i < 8; ++i) {
        if (strS[i] == '1' or strT[i]== '1'){
            Or_str += '1';
        }else{
            Or_str += '0';
        }
    }
    return Or_str;
}

void ALU::bitwiseAND(int R, int S, int T) {

    string r, s = machine_register->getCell(S), t = machine_register->getCell(T);
    s = hexToBin(s), t = hexToBin(t);

    for(int i = 0; i < 8; i++) {
        if(s[i] == t[i]) {
            if(s[i] == '1') {
                r += s[i];
                continue;
            }
        }
        r += "0";
    }
    r = binToHex(r);
    machine_register->setCell(R, r);

}

void ALU::bitwiseXOR(int R, int S, int T) {

    string r;
    string s = machine_register->getCell(S);
    string t = machine_register->getCell(T);
    s = hexToBin(s);
    t = hexToBin(t);

    for(int i = 0; i < 8; i++) {
        if(s[i] == t[i])
            r += "0";
        else
            r += "1";
    }

    r = binToHex(r);
    machine_register->setCell(R, r);
}

string ALU::hexToBin(string hex) {
    string binary;
    for(char i : hex) {
        binary += hexAndBinMap[i];
    }
    return binary;
}

string ALU::binToHex(string bin) {
    string bin1 = bin.substr(0, 4);
    string bin2 = bin.substr(4);
    for(auto i : hexAndBinMap) {
        if(i.second == bin1)
            bin1 = i.first;
        if(i.second == bin2)
            bin2 = i.first;
    }
    return bin1 + bin2;
}

int ALU::hexToDec(string hex) {
    int dec = stoi(hex, 0, 16);
    return dec;
}

string ALU::decToHex(int dec) {
    if (dec == 0)
        return "0";
    string hex;
    while (dec > 0) {
        int remainder = dec % 16;
        if (remainder < 10) {
            char c = remainder + '0';
            hex += c;
        } else {
            char c = remainder - 10 + 'A';
            hex += c;
        }
        dec /= 16;
    }
    reverse(hex.begin(), hex.end());
    return hex;
}






string convert_farction_bin(double fraction){
    string Fraction_bin = "";
    int Del_int = 0;
    for (int i = 0; i < 4; ++i) {
        fraction= fraction*2;
        Del_int = fraction;
        if (Del_int == 1){
            Fraction_bin += '1';
        }else{
            Fraction_bin += '0';
        }
        fraction = fraction - Del_int;
    }
    return Fraction_bin;
};




double calculate_floating_point (string StrNum){
    char Sign_S = StrNum[0];
    string Exponent_S = StrNum.substr(1,3);
    string Mantissa_S = StrNum.substr(4,4);
    double Mantissa = 0;
    for (int i = 0; i < 4 ; ++i) {
        if (Mantissa_S[i]=='1'){
            Mantissa += pow(2,-1*(i+1));
        }
    }
    int Exponent = Bintodec3bits[Exponent_S];
    double Fin_Num = (Mantissa * pow(2,Exponent-4));
    if (Sign_S == '1'){
        return -1*Fin_Num;
    }else{
        return Fin_Num;
    }
}





string fiill(string str){
    string fillstr = "";
    if (str.size()<8){
        for (int i = 0; i < (8-str.size()); ++i) {
            fillstr += '0';
        }
    }
    fillstr += str;
    return fillstr;
}


string binarary = "";
string Binarary (int n){
    if (n > 1){
        Binarary(n/2);
    }
    binarary += to_string(n%2);
    return binarary;
}


string Hexanum = "";
string Hexawawy (string str){
    Hexanum = str.substr(0,4);
    string Hexanumfin = "";
    Hexanumfin += decAndHexMap[Hexanum];
    Hexanum = str.substr(4,4);
    Hexanumfin += decAndHexMap[Hexanum];
    return Hexanumfin;
}


string invert_ans (string str){
    string ans = "";
    for (int i = 7; i >= 0 ; --i) {
        ans += str[i];
    }
    return ans;
}

ALU::ALU(Memory &machine_memory, Register &machine_register) :
        machine_memory(&machine_memory), machine_register(&machine_register){

}




void ALU::add_twos_complement(int R, int S, int T) {
    int content_of_S = stoi(machine_register->getCell(S),  nullptr, 16);
    int content_of_T = stoi(machine_register->getCell(T),  nullptr, 16);
    int Adding_res = content_of_S + content_of_T ;
    string BinNum = Binarary(Adding_res);
    binarary = "";
    BinNum = fiill(BinNum);
    string BinNumSemi = "";
    string BinNumFin = "";
    for (int i = 0; i < 8 ; ++i) {
        if (BinNum[i]=='1'){
            BinNumSemi += '0';
        }else{
            BinNumSemi += '1';
        }
    }
    for (int i = 7; i >= 0 ; --i) {
        if (BinNumSemi[i]=='0'){
            BinNumFin += '1';
            break;
        }else{
            BinNumFin += '0';
        }
    }
    while (BinNumFin.size() != 8){
        BinNumFin += BinNumSemi[7-BinNumFin.size()];
    }
    BinNumFin = invert_ans(BinNumFin);
    int BinFinHun = stoi(BinNumFin, nullptr,2);
    string final_Hex = Hexawawy(BinNumFin);
    Hexanum = "";
    machine_register->setCell(R,final_Hex);
}










void ALU::add_float_representation(int R, int S, int T) {
    int content_of_S = stoi(machine_register->getCell(S),  nullptr, 16);
    int content_of_T = stoi(machine_register->getCell(T),  nullptr, 16);

    string content_of_S_bin = Binarary(content_of_S);
    binarary = "";
    content_of_S_bin = fiill(content_of_S_bin);
    string content_of_T_bin = Binarary(content_of_T);
    binarary = "";
    content_of_T_bin = fiill(content_of_T_bin);
    double Num_of_S = calculate_floating_point(content_of_S_bin);
    double Num_of_T = calculate_floating_point(content_of_T_bin);
    double Adding_res_Num = Num_of_S + Num_of_T;

    string res_sign;
    if (Adding_res_Num<0){
        res_sign = "1";
    }else{
        res_sign = "0";
    }

    Adding_res_Num = abs(Adding_res_Num);
    int Adding_res_int = (int)Adding_res_Num;
    string Left_Point_Side_bin = DecToBinforFloat[Adding_res_int];
    double Right_Point_side_dec = Adding_res_Num - Adding_res_int;
    string Right_Point_side_bin = convert_farction_bin(Right_Point_side_dec);
    string Mantissa = Left_Point_Side_bin + Right_Point_side_bin;
    if(Mantissa.size() > 4){
        Mantissa  = Mantissa.substr(1, 4);
    }
    int Exponent;
    if (Left_Point_Side_bin[0] != '0'){
        Exponent = Left_Point_Side_bin.size();
    }else{
        Exponent = 0;
    }
    Exponent += 4;
    string Exponent_bin = DecToBinforFloat[Exponent];
    string Fin_Adding_Ans = res_sign + Exponent_bin + Mantissa ;
    string firsthalf = "";
    string sechalf = "";
    firsthalf = decAndHexMap[Fin_Adding_Ans.substr(0,4)];
    sechalf = decAndHexMap[Fin_Adding_Ans.substr(4,4)];
    string Hex_Fin_Adding_Ans = firsthalf + sechalf;
    machine_register->setCell(R,Hex_Fin_Adding_Ans);

}



void ALU::BitWise_OR(int R, int S, int T) {
    int decimalcontent_of_S = stoi(machine_register->getCell(S), nullptr, 16);
    int decimalcontent_of_T = stoi(machine_register->getCell(T), nullptr, 16);

    string bin_S = Binarary(decimalcontent_of_S);
    binarary="";
    bin_S = fiill(bin_S);
    string bin_T = Binarary(decimalcontent_of_T);
    binarary="";
    bin_T = fiill(bin_T);
    string FinStr_OR = Or_func(bin_S,bin_T);
    FinStr_OR = Hexawawy(FinStr_OR);
    Hexanum = "";
    machine_register->setCell(R,FinStr_OR);
}



void CU::jump_to_instruction_in_address_D(int R, int memory_address, int &PC) {
    bool register_cell_equals_register_0 = (machine_register->getCell(R) > machine_register->getCell(00) ); //could be a function also :)
    if(register_cell_equals_register_0) {
        PC = memory_address;
    }
}


void ALU::shift_the_content(int R, int X){
    int content_of_R = stoi(machine_register->getCell(R),  nullptr, 16);
    string content_of_R_str = Binarary(content_of_R);
    binarary = "";
    content_of_R_str +=  fiill(content_of_R_str);
    string shifted;
    shifted = shift_func(content_of_R_str,X);
    shifted = Hexawawy(shifted);
    Hexanum = "";
    machine_register->setCell(R,shifted);
}