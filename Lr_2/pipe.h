#pragma once
#include <string>
#include <iostream>

class Pipe
{
public:
    int id;
    std::string name;
    double length;
    double diameter;
    bool in_process;
    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
};
