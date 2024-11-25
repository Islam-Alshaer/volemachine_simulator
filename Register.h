#pragma once
#include <string>
#include "vector"

using namespace std;

class Register {
private:
    vector<string> register_cells;
public:
    Register();
    string getCell(int address) const;
    void setCell(const int &address, const string &val);
    void clearRegister();
};