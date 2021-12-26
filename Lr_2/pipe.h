#pragma once
#include <string>
#include <iostream>
#include <fstream>

class pipe
{
    static int MaxID;
    int id;
    std::string name;
    double length;
    double diameter;
    bool in_process;
public:
    Pipe();
    double getLen() const { return length; }
    double getDia()const { return diameter; }
    bool getProc() const { return in_process; }
    std::string getName() const { return name; }
    int getId() { return id; }
    void edit();

    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
    friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);
};

