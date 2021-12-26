#include "station.h"
#include "CorrectNumber.h"
#include <string>
#include <iostream>
#include <conio.h>
using namespace std;

int Station::MaxID = 0;

Station::Station()
{
    id = ++MaxID;
}

ostream& operator << (ostream& out, const Station& s)
{
    out << "\tId: " << s.id << endl
        << "\tName: " << s.name << endl
        << "\tNumber of factories: " << s.num << endl
        << "\tNumber of factories in process: " << s.num_process << endl
        << "\tEfficiency: " << s.eff << endl;
    return out;
}

ofstream& operator<<(ofstream& fout, const Station& s)
{
    if (fout.is_open()) {
        fout << s.id << endl
            << s.name << endl
            << s.num << endl
            << s.num_process << endl
            << s.eff << endl;
    }
    return fout;
}

istream& operator>>(istream& in, Station& s)
{
    cout << "Please, enter the information about station " << endl;
    cout << "Enter the name: ";
    cin.ignore(10000, '\n');
    getline(in, s.name);
    cout << "Enter the number of factories: ";
    s.num = GetCorrectNumber2(0);
    cout << "Enter the number of factories in process: ";
    s.num_process = GetCorrectNumber1(0, s.num);
    cout << "Enter the efficiency: ";
    s.eff = GetCorrectNumber1(0, 100);
    return in;
}

ifstream& operator>>(ifstream& fin, Station& s)
{
    string str;
    if (fin.is_open()) {
        fin >> s.id;
        getline(fin, str);
        getline(fin, str);
        s.name = str;
        fin >> s.num;
        fin >> s.num_process;
        fin >> s.eff;
    }
    return fin;
}

void station::edit()
{
    int n;
    char variant;
    cout << "Enter 1 if factories were added to work or 0 if factories were excluded from work" << endl;
    do {
        variant = _getch();
        if (variant != '0' && variant != '1') cout << "Enter the correct value" << endl;
    } while (variant != '0' && variant != '1');
    if (variant == '1') {
        cout << "Enter how many factories were added to work " << endl;
        n = GetCorrectNumber1(0, (station.num - station.num_process));
        station.num_process = station.num_process + n;
    }
    else {
        cout << "Enter how many factories were excluded from work " << endl;
        n = GetCorrectNumber1(0, (station.num_process));
        station.num_process = station.num_process - n;
    }
}
