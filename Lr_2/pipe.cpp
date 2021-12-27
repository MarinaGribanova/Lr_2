#include "pipe.h"
#include "CorrectNumber.h"
#include <string>
#include <iostream>
#include <conio.h>
using namespace std;
int Pipe::MaxID = 0;

void pipe_processs(const Pipe& pipe)
{
    if (pipe.getProc())
        cout << "Pipe is in process" << endl;
    else
        cout << "Pipe is not in process" << endl;
}

Pipe::Pipe()
{
    id = ++MaxID;
    name = "";
    length = 0;
    diameter = 0;
    in_process = 0;
}

void Pipe::edit()
{
    in_process = !in_process;
}

ostream& operator << (ostream& out, const Pipe& p)
{
    out << "\tId: " << p.id
        << "\tName: " << p.name
        << "\tLength: " << p.length
        << "\tDiameter: " << p.diameter << endl;
    pipe_processs(p);
    return out;
}

std::ofstream& operator<<(std::ofstream& fout, const Pipe& p)
{
    if (fout.is_open()) {
        fout << p.id << endl
            << p.name << endl
            << p.length << endl
            << p.diameter << endl
            << p.in_process << endl;
    }
    return fout;
}

istream& operator >> (istream& in, Pipe& p)
{
    char variant;
    cout << "Please, enter the information about pipe " << endl;
    cout << "Enter the name: ";
    cin.ignore(10000, '\n');
    getline(in, p.name);
    cout << "Enter the length: ";
    p.length = GetCorrectNumber2(0.);
    cout << "Enter the diameter: ";
    p.diameter = GetCorrectNumber2(0.);
    cout << "Enter 1 if pipe in process or 0 if pipe is not in process" << endl;
    do {
        variant = _getch();
        if (variant != '0' && variant != '1') cout << "Enter the correct value" << endl;
    } while (variant != '0' && variant != '1');
    p.in_process = variant == '1';
    pipe_processs(p);
    return in;
}

std::ifstream& operator>>(std::ifstream& fin, Pipe& p)
{
    string str;
    if (fin.is_open()) {
        string s;
        fin >> p.id;
        getline(fin, str);
        getline(fin, str);
        p.name = str;
        fin >> p.length;
        fin >> p.diameter;
        fin >> p.in_process;
    }
    return fin;
}
