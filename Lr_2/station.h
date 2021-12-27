#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Station
{
    int id;
    std::string name;
    int num;
    int num_process;
    int eff;
    static int MaxID;

public:

    std::string getName() const { return name; }
    int getNum() const { return num; }
    static int getMaxID() { return MaxID; }
    static void setMaxID(const int id) { MaxID = id; }
    int getNumP() const { return num_process; }
    int getId() { return id; }
    Station();
    void edit();
    friend std::ostream& operator << (std::ostream& out, const Station& s);
    friend std::ofstream& operator << (std::ofstream& fout, const Station& s);
    friend std::istream& operator >> (std::istream& in, Station& s);
    friend std::ifstream& operator >> (std::ifstream& fin, Station& s);
};

