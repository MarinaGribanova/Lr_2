#pragma once
#include <string>
#include <iostream>
#include <conio.h>

struct Pipe
{
    int id;
    double length;
    double diameter;
    bool in_process;
};

struct Station
{
    int id;
    std::string name;
    int num;
    int num_process;
    int eff;
};