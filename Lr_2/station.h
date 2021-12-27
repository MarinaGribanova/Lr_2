#pragma once
#pragma once
#include <string>
#include <iostream>

class Station
{
public:
    int id;
    std::string name;
    int num;
    int num_process;
    int eff;
    friend std::ostream& operator << (std::ostream& out, const Station& s);
    friend std::istream& operator >> (std::istream& in, Station& s);
};

