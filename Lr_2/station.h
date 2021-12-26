#pragma once
#include <string>
#include <iostream>
#include <fstream>

class station
{
    int id;
    static int MaxID;
    std::string name;
    int num;
    int num_process;
    int eff;
public:
    std::string getName() const { return name; }
    int getNum() const { return num; }
    int getNumP() const { return num_process; }
    int getId() { return id; }
    Station();
    void edit();

    friend std::ostream& operator << (std::ostream& out, const Station& s);
    friend std::ofstream& operator << (std::ofstream& fout, const Station& s);
    friend std::istream& operator >> (std::istream& in, Station& s);
    friend std::ifstream& operator >> (std::ifstream& fin, Station& s);
};

