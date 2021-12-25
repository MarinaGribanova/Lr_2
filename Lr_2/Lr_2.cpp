// Lr_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Header.h"
#include <fstream>
#include <vector>

using namespace std;
template <typename T>

T GetCorrectNumber1(T min, T max)
{
    T x;
    while ((cin >> x).fail() || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << min << "-" << max << "):";
    }
    return x;
}

template <typename T>
T GetCorrectNumber2(T min)
{
    T x;
    while (!(cin >> x) && x < min)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type correct number: ";
    }
    cin.ignore(10000, '\n');
    return x;
}

void pipe_process(const Pipe& pipe)
{
    if (pipe.in_process)
        cout << "Pipe is in process" << endl;
    else
        cout << "Pipe is not in process" << endl;
}

Pipe input_pipe(int id)
{
    char variant;
    Pipe pipe;
    cout << "Enter information about the pipe, please" << endl;
    pipe.id = id;
    cout << "Enter the length: ";
    pipe.length = GetCorrectNumber2(0.);
    cout << "Enter the diameter: ";
    pipe.diameter = GetCorrectNumber2(0.);
    cout << "Enter 1 if the pipe is in process or 0 if the pipe is not in process" << endl;
    do {
        variant = _getch();
        if (variant != '0' && variant != '1') cout << "Enter the correct value 1 or 0" << endl;
    } while (variant != '0' && variant != '1');
    pipe.in_process = variant == '1';
    pipe_process(pipe);
    return pipe;
}

Station input_station(int id)
{
    Station station;
    cout << "Enter information about the station, please " << endl;
    station.id = id;
    cout << "Enter the name: ";
    cin.ignore(10000, '\n');
    getline(cin, station.name);
    cout << "Enter the number of factories: ";
    station.num = GetCorrectNumber2(0);
    cout << "Enter the number of factories in process: ";
    station.num_process = GetCorrectNumber1(0, station.num);
    cout << "Enter the efficiency: ";
    station.eff = GetCorrectNumber1(0, 100);
    return station;
}

void load_all(vector <Pipe>& pipes, vector <Station>& stations)
{
    int pipecount, stationcount;
    ifstream fin;
    string str;
    fin.open("data.txt");
    getline(fin, str);
    pipecount = stoi(str);
    getline(fin, str);
    stationcount = stoi(str);

    if (pipecount != 0) {
        pipes.resize(pipecount);
        for (int i = 0; i < pipes.size(); ++i) {
            getline(fin, str); pipes[i].id = stoi(str);
            getline(fin, str); pipes[i].length = stod(str);
            getline(fin, str); pipes[i].diameter = stoi(str);
            getline(fin, str); pipes[i].in_process = stoi(str);
        }
    }
    if (stationcount != 0) {
        stations.resize(stationcount);
        for (int i = 0; i < stations.size(); ++i) {
            getline(fin, str); stations[i].id = stoi(str);
            getline(fin, str); stations[i].name = str;
            getline(fin, str); stations[i].num = stoi(str);
            getline(fin, str); stations[i].num_process = stoi(str);
            getline(fin, str); stations[i].eff = stoi(str);
        }
    }
}


void print_pipe(const Pipe& pipe)
{
    //cout << "Information about pipe: " << endl
    cout << "\tId: " << pipe.id
        << "\tLength: " << pipe.length
        << "\tDiameter: " << pipe.diameter << endl;
    pipe_process(pipe);
    cout << endl;
}

void print_station(const Station& station)
{
    //cout << "Information about station: " << endl
    cout << "\tId: " << station.id
        << "\tName: " << station.name << endl
        << "\tNumber of factories: " << station.num << endl
        << "\tNumber of factories in process: " << station.num_process << endl
        << "\tEfficiency: " << station.eff << endl;
    cout << endl;
}

void print_pipes(const vector<Pipe>& pipes)
{
    for (auto& p : pipes) print_pipe(p);
}

void print_stations(const vector<Station>& stations)
{
    for (auto& s : stations) print_station(s);
}

void print_menu()
{
    cout << "MENU" << endl
        << "1. Add pipe" << endl
        << "2. Add station" << endl
        << "3. Edit pipe" << endl
        << "4. Edit station" << endl
        << "5. Show " << endl
        << "6. Save" << endl
        << "7. Load " << endl
        << "0. Exit" << endl;
}

void edit_pipe(Pipe& pipe)
{
    /*char variant;
        /*cout << "Enter 1 if pipe is in process or 0 if pipe is not in process" << endl;
        do {
            variant = _getch();
            if (variant != '0' && variant != '1') cout << "Enter the correct value 1 or 0" << endl;
        } while (variant != '0' && variant != '1');
        pipe.in_process = variant == '1';*/
    pipe.in_process = !pipe.in_process;
    pipe_process(pipe);
}

void edit_station(Station& station)
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

void save_pipe(const Pipe& pipe, ofstream& fout)
{

    if (fout.is_open()) {
        fout << pipe.id << endl
            << pipe.length << endl
            << pipe.diameter << endl
            << pipe.in_process << endl;
        // if (pipe.in_process == true) fout << "Processed";
       //  else fout << "Not processed";
    }
}

void save_station(const Station& station, ofstream& fout)
{

    if (fout.is_open()) {
        fout << station.id << endl
            << station.name << endl
            << station.num << endl
            << station.num_process << endl
            << station.eff << endl;

    }
}

void save_pipes(const vector<Pipe>& pipes, ofstream& fout)
{
    for (auto& p : pipes) save_pipe(p, fout);
}

void save_stations(const vector<Station>& stations, ofstream& fout)
{
    for (auto& s : stations) save_station(s, fout);
}

Pipe& SelectPipe(vector<Pipe>& p)
{
    cout << "Enter index: " << endl;
    unsigned int index = GetCorrectNumber1<uint64_t>(1, p.size());
    return p[index - 1];
}

Station& SelectStation(vector<Station>& s)
{
    cout << "Enter index: " << endl;
    unsigned int index = GetCorrectNumber1<uint64_t>(1, s.size());
    return s[index - 1];
}

int main()
{
    // Pipe pipe;
     //Station station;
    vector <Pipe> pipes = {};
    vector <Station> stations = {};
    int stationcount = 1;
    int pipecount = 1;
    while (1)
    {
        print_menu();
        switch (GetCorrectNumber1(0, 7))
        {
        case 1:
        {   Pipe pipe;
        pipes.emplace_back(input_pipe(pipecount));
        pipecount++;
        //pipe = input_pipe();
        break;
        }
        case 2:
        {
            Station station;
            stations.emplace_back(input_station(stationcount));
            stationcount++;
            break;
        }

        case 3:
        {   if (pipes.size() == 0) {
            cout << "No pipe to edit" << endl;
        }
        else {
            edit_pipe(SelectPipe(pipes));
        }
        break;
        }

        case 4:
        {   if (stations.size() == 0) {
            cout << "No station to edit" << endl;
        }
        else {
            edit_station(SelectStation(stations));
        }
        break;
        }

        case 5:
        { 
            cout << "Information about pipes:" << endl;
            if (pipes.size() == 0) {
                cout << "No pipes" << endl;
            }
            else
                print_pipes(pipes);
            cout << "Information about stations:" << endl;
            if (stations.size() == 0) {
                cout << "No stations" << endl;
            }
            else
                print_stations(stations);

            break;
        }
        case 6:
        {   ofstream fout;
            fout.open("data.txt", ios::out);
            if (pipes.size() != 0)
                fout << pipes.size() << endl;
            else fout << 0 << endl;
            if (stations.size() != 0)
                fout << stations.size() << endl;
            else fout << 0 << endl;
            if (pipes.size() != 0)
                save_pipes(pipes, fout);
            if (stations.size() != 0)
                save_stations(stations, fout);
            fout.close();
        break;
        }
        case 7:
        {
            /*ifstream fin;
            fin.open("data.txt", ios::in);
            fin >> stationcount;
            fin >> pipecount;
            if (stationcount == 0) {
                cout << "No station" << endl;
            }
            else
            {
                station = load_station(fin);
                print_station(station);
            }
            if (pipecount == 0) {
                cout << "No pipe" << endl;
            }
            else {
                pipe = load_pipe(fin);
                print_pipe(pipe);
            }
            fin.close();*/
            load_all(pipes, stations);
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action" << endl;
        }
        }
    }

    return 0;
}
