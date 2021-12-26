#include "pipe.h"
#include "CorrectNumber.h"
#include <string>
using namespace std;

ostream& operator<<(ostream& out, const Pipe& p)
{
	out << "\tName: " << p.name
		<< "\tLength: " << p.length
		<< "\tDiameter: " << p.diameter << endl;
	return out;
}

istream& operator>>(istream& in, Pipe& p)
{
    char variant;
    cout << "Please, enter the information about pipe " << endl;
    cout << "Enter the name: ";
    in >> p.name;
    cout << "Enter the length: ";
    p.length = GetCorrectNumber2(0.);
    cout << "Enter the diameter: ";
    p.diameter = GetCorrectNumber2(0.);
    p.in_process = GetCorrectNumber1(0, 1);
    cout << "Type name: ";
    return in;
}
