#include "station.h"
#include "CorrectNumber.h"
#include <string>
using namespace std;

ostream& operator << (ostream& out, const Station& s)
{
    out << "\tName: " << s.name << endl
        << "\tNumber of factories: " << s.num << endl
        << "\tNumber of factories in process: " << s.num_process << endl
        << "\tEfficiency: " << s.eff << endl;
    return out;
}

istream& operator>>(istream& in, Station& s)
{
    cout << "Please, enter the information about station " << endl;
    cout << "Enter the name: ";
    in >> s.name;
    cout << "Enter the number of factories: ";
    s.num = GetCorrectNumber2(0);
    cout << "Enter the number of factories in process: ";
    s.num_process = GetCorrectNumber1(0, s.num);
    cout << "Enter the efficiency: ";
    s.eff = GetCorrectNumber1(0, 100);
    return in;
}
