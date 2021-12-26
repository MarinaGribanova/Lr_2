// Lr_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Header.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include "pipe.h"
#include "station.h"
#include "CorrectNumber.h"

using namespace std;

template <typename T>
int SearchId(const T& map, int id)
{
        if (map.find(id) != map.end()) return id;
        return -1;
}

void pipe_process(const Pipe& pipe)
{
    if (pipe.in_process)
        cout << "Pipe is in process" << endl;
    else
        cout << "Pipe is not in process" << endl;
}

Pipe input_pipe()
{
    char variant;
    Pipe pipe;
    cout << "Enter information about the pipe, please" << endl;
    cout << "Enter the name: ";
    cin.ignore(10000, '\n');
    getline(cin, pipe.name);
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

Station input_station()
{
    Station station;
    cout << "Enter information about the station, please " << endl;
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

Pipe load_pipe(ifstream& fin)
{
    if (fin.is_open()) {
        Pipe pipe;
        string s;
        fin >> pipe.id;
        fin >> pipe.name;
        fin >> pipe.length;
        fin >> pipe.diameter;
        fin >> pipe.in_process;
        return pipe;
    }
    return {};
}
Station load_station(ifstream& fin)
{
    if (fin.is_open()) {
        Station station;
        fin >> station.id;
        fin >> station.name;
        fin >> station.num;
        fin >> station.num_process;
        fin >> station.eff;
        return station;
    }
    return {};
}

void load_all(unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& stations, ifstream& fin)
{
    string str;
    int pipecount, stationcount;
    fin >> pipecount;
    fin >> stationcount;
    if (pipecount != 0) {
        for (int i = 0; i < pipecount; ++i) {
            Pipe mypipe;
            int id;
            fin >> id;
            getline(fin, str);
            getline(fin, str);
            mypipe.name = str;
            fin >> mypipe.length;
            fin >> mypipe.diameter;
            fin >> mypipe.in_process;
            pipes.insert({ id, mypipe });
        }
    }
    if (stationcount != 0) {
        for (int i = 0; i < stationcount; ++i) {
            Station mystation;
            int id;
            fin >> id;
            getline(fin, str);
            getline(fin, str);
            mystation.name = str;
            //fin >> mystation.name;
            fin >> mystation.num;
            fin >> mystation.num_process;
            fin >> mystation.eff;
            stations.insert({ id, mystation });
        }
    }
}


void print_pipe(const pair <int, Pipe>& pipe)
{
    cout << "\tId: " << pipe.first
        << "\tName: " << pipe.second.name
        << "\tLength: " << pipe.second.length
        << "\tDiameter: " << pipe.second.diameter << endl;
    pipe_process(pipe.second);
    cout << endl;
}

void print_station(const pair <int, Station>& station)
{
    cout << "\tId: " << station.first
        << "\tName: " << station.second.name << endl
        << "\tNumber of factories: " << station.second.num << endl
        << "\tNumber of factories in process: " << station.second.num_process << endl
        << "\tEfficiency: " << station.second.eff << endl;
    cout << endl;
}

void print_pipes(const unordered_map <int, Pipe>& pipes)
{
    for (auto& p : pipes) print_pipe(p);
}

void print_stations(const unordered_map <int, Station>& stations)
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
        << "5. Delete pipe " << endl
        << "6. Delete station " << endl
        << "7. Search and edit by the filter " << endl
        << "8. Show " << endl
        << "9. Save" << endl
        << "10. Load " << endl
        << "0. Exit" << endl;
}

void edit_pipe(Pipe& pipe)
{
    pipe.in_process = !pipe.in_process;
}
int edit_pipes(unordered_map <int, Pipe>& pipes)
{
    int id;
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber2(0);
        if (SearchId(pipes, id) != -1) {
            edit_pipe(pipes[id]);
            cout << "Object was edited" << endl;
            return id;
        }
        else cout << "Object with this id not found" << endl;
    }
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

int edit_stations(unordered_map <int, Station>& stations)
{
    int id;
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber2(0);
        if (SearchId(stations, id) != -1) {
            edit_station(stations[id]);
            cout << "Object was edited" << endl;
            return id;
        }
        else cout << "Object with this id not found" << endl;
    }
}

template <typename T>
void del_object(T& map, int id)
{
    if (map.find(id) != map.end()) {
        map.erase(id);
    }
}

template <typename T>
void del(T& map)
{
    while (true) {
        cout << endl << "Type id: ";
        int id = GetCorrectNumber2(0);
        if (SearchId(map, id) != -1) {
            del_object(map, id);
            cout << "Object was deleted" << endl;
            return;
        }
        else cout << "Object with this id was not found" << endl;
    }
}

void save_pipe(const Pipe& pipe, ofstream& fout)
{

    if (fout.is_open()) {
        fout << pipe.id << endl
            << pipe.name << endl
            << pipe.length << endl
            << pipe.diameter << endl
            << pipe.in_process << endl; }
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

void save_pipes(const unordered_map <int, Pipe>& pipes, ofstream& fout)
{
    for (auto& p : pipes)
        fout << p.first << endl
        << p.second.name << endl
        << p.second.length << endl
        << p.second.diameter << endl
        << p.second.in_process << endl;
}

void save_stations(const unordered_map <int, Station>& stations, ofstream& fout)
{
    for (auto& s : stations)
        fout << s.first << endl
        << s.second.name << endl
        << s.second.num << endl
        << s.second.num_process << endl
        << s.second.eff << endl;;
}

template <typename T, typename T_param>
using Filter = bool (*)(const T& map, T_param param);

template <typename T, typename T_param>
vector<int> search_filter(const unordered_map<int, T>& map, Filter<T, T_param> f, T_param param) {
    vector<int> res;
    for (auto& m : map)
        if (f(m.second, param))
            res.push_back(m.first);
    return res;
}

template <typename T>
bool search_by_name(const T& map, string name)
{
    return map.name == name;
}

bool search_by_repair(const Pipe& pipes, const bool& r)
{
    return pipes.in_process == r;
}

vector<int> search_by_repair(const unordered_map <int, Pipe>& pipes, const bool& r)
{
    int i = 0;
    vector<int> index;
    for (auto& p : pipes) {
        if (p.second.in_process == r)
            index.emplace_back(p.first);
    }
    return index;
}

bool search_by_ratio(const Station& stations, double per)
{
    return (round(((double(stations.num) - double(stations.num_process)) / double(stations.num)) * 100) == per);
}

void pipes_filters(unordered_map<int, Pipe>& pipes) {
    if (pipes.size() == 0) {
        cout << "No pipes " << endl;
        return; }
    while (true) {
        cout << endl << "EDITING PIPES" << endl 
            << "1. Search for pipes by name" << endl
            << "2. Search for pipes on the basis of repair" << endl 
            << "3. Search for pipes by id " << endl 
            << "0. Exit "<< endl;
        switch (GetCorrectNumber1(0, 3)) {
        case 1: {
            cout << "Type name of pipe: ";
            string name = "";
            cin.ignore(10000, '\n');
            getline(cin, name);
            vector<int> index = search_filter(pipes, search_by_name, name);
            if (index.size() != 0) {
                cout << "Found " << index.size() << " pipes" << endl;
                for (auto& id : index) {
                    print_pipe({ id, pipes[id] });
                }
                cout << "1. Edit found pipes" << endl
                    << "0. Exit" << endl;
                switch (GetCorrectNumber1(0, 1)) {
                case 1: {
                    for (auto& id : index) {
                        edit_pipe(pipes[id]);
                        print_pipe({ id, pipes[id] });
                    }
                }
                case 0:
                    return;
                default:
                    cout << "Wrong action" << endl;
                    break;
                }
            }
            else
                cout << "No pipes " << endl;
            break;
        }
        case 2: {
            char variant;
            cout << "Enter 1 if you want to search pipe is under repair, 0 if is not under repair: " << endl;
            do {
                variant = _getch();
                if (variant != '0' && variant != '1') cout << endl << "Enter the correct value" << endl;
            } while (variant != '0' && variant != '1');
            if (variant == '1' || variant == '0') {
                (variant == '1') ? cout << "Pipes is in process: " << endl : cout << "Pipes is not in process:" << endl;
                vector<int> index = search_by_repair(pipes, (variant == '1') ? true : false);
                if (index.size() != 0) {
                    cout << "Found " << index.size() << " pipes" << endl;
                    for (auto& id : index) {
                        print_pipe({ id,pipes[id] });
                    }
                    cout << "1. Edit found pipes" << endl 
                        << "0. Exit" << endl;
                    switch (GetCorrectNumber1(0, 1)) {
                    case 1: {
                        for (auto& id : index) {
                            edit_pipe(pipes[id]);
                            print_pipe({ id, pipes[id] });
                        }
                    }
                    case 0:
                        return;
                    default:
                        cout << "Wrong action" << endl;
                        break;
                    }
                }
                else cout << "No pipes" << endl;
            }
            else
                cout << "Wrong action" << endl;
            break;
        }
        case 3: {
            cout << "Enter id of pipes you want to edit or 0 to complete the entry: " << endl;
            vector<int> edit_id;
            int variant;
            do {
                variant = GetCorrectNumber2(0);
                if (SearchId(pipes, variant) != -1)
                    edit_id.emplace_back(variant);
            } while (variant != 0);
            if (edit_id.size() != 0) {
                cout << "Found " << edit_id.size() << " pipes" << endl;
                for (auto& id : edit_id) {
                    print_pipe({ id,pipes[id] });
                }
                cout << "1. Edit found pipes" << endl
                    << "0. Exit" << endl;
                switch (GetCorrectNumber1(0, 1)) {
                case 1: {
                    for (auto& id : edit_id) {
                        edit_pipe(pipes[id]);
                        print_pipe({ id, pipes[id] });
                    }
                }
                case 0:
                    return;
                default:
                    cout << "Wrong action" << endl;
                    break;
                }
            }
            else cout << "Pipes with this id not found" << endl;
            break;
        }
        case 0:
            return;
        default:
            cout << "Wrong action" << endl;
            break;
        }
    }
}

void stations_filters(unordered_map<int, Station>& stations) {
    if (stations.size() == 0) {
        cout << "No stations" << endl;
        return; }
    while (true) {
        cout << endl << "EDITING STATIONS" << endl 
            << "1. Search for stations by name" << endl
            << "2. Search for stations by ratio" << endl 
            << "0. Exit" << endl;
        switch (GetCorrectNumber1(0, 2)) {
        case 1: {
            cout << "Type name of station: ";
            string name = "";
            cin.ignore(10000, '\n');
            getline(cin, name);
            vector<int> index = search_filter(stations, search_by_name, name);
            if (index.size() != 0) {
                cout << "Found " << index.size() << " stations" << endl;
                for (auto& id : index) {
                    print_station({ id, stations[id] });
                }
                cout << "1. Edit found stations" << endl
                    << "0. Exit" << endl;
                switch (GetCorrectNumber1(0, 1)) {
                case 1: {
                    for (auto& id : index) {
                        edit_station(stations[id]);
                        print_station({ id, stations[id] });
                    }
                }
                case 0:
                    return;
                default:
                    cout << "Wrong action" << endl;
                    break;
                }
            }
            else
                cout << "No stations " << endl;
            break;
        }
        case 2: {
            cout << "Type percentage of factories is not in process: " << endl;
            double percent = GetCorrectNumber2(0);
            if (percent <= 100 && percent >= 0) {
                vector<int> index = search_filter(stations, search_by_ratio, percent);
                if (index.size() != 0) {
                    cout << "Found " << index.size() << " stations" << endl;
                    for (auto& id : index) {
                        print_station({ id, stations[id] });
                    }
                    cout << "1. Edit found stations" << endl
                        << "0. Exit" << endl;
                    switch (GetCorrectNumber1(0, 1)) {
                    case 1: {
                        for (auto& id : index) {
                            edit_station(stations[id]);
                            print_station({ id, stations[id] });
                        }
                    }
                    case 0:
                        return;
                    default:
                        cout << "Wrong action" << endl;
                        break;
                    }
                }
                else
                    cout << "No stations " << endl;
            }
            else
                cout << "Wrong action " << endl;
            break;
        }
        case 0:
            return;
        default:
            cout << "Wrong action" << endl;
            break;
        }
    }
}

void search_and_edit(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
    while (true) {
        cout << endl << "MENU filters" << endl 
            << "1. Pipes " << endl 
            << "2. Stations " << endl
            << "0. Exit " << endl;
        int edit_number = GetCorrectNumber2(0);
        switch (edit_number) {
        case 1: {
            pipes_filters(pipes);
            return;
        }
        case 2: {
            stations_filters(stations);
            return;
        }
        case 0:
            return;
        default: {
            cout << "Wrong actions" << endl;
            break;
        }
        }
    }
}

int main()
{
    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;
    int stationcount = 1;
    int pipecount = 1;
    while (1)
    {
        print_menu();
        switch (GetCorrectNumber1(0, 10))
        {
        case 1:
        {           
        int id = pipes.size() + 1;
        pipes.insert({ id, input_pipe() });
        break;
        }
        case 2:
        {   
        int id = stations.size() + 1;
        stations.insert({ id, input_station() });
            break;
        }
        case 3:
        {   if (pipes.size() == 0)
            cout << "Pipes to edit not found" << endl;
        else {
            int id = edit_pipes(pipes);
            print_pipes({ id, pipes[id] });
        }
        break;
        }

        case 4:
        {   if (stations.size() == 0) {
            cout << "Stations to edit not found" << endl;
        }
        else
        {
            int id = edit_stations(stations);
            print_station({ id, stations[id] });
        }
        break;
        }
        case 5:
        { 
            if (pipes.size() == 0)
                cout << "Pipes to delete not found" << endl;
            else {
                print_pipes(pipes);
                del(pipes);}
            break;
        }
        case 6:
        {   
              if (stations.size() == 0)
            cout << "Stations to delete not found" << endl;
              else {
            print_stations(stations);
            del(stations); }
        break;
        }
        case 7:
        {
            //string name = "";
            //cout << "Type name of station: ";
            //cin.ignore(10000, '\n');
            //getline(cin, name);
            //int i = search_by_name(stations, name);
            //if (i != -1) {
            //    cout << "Station with this name: " << endl;
            //    print_station({ i,stations[i] });  }
            //else
            //    cout << "Station with this name not found" << endl;

            //char variant;
            //cout << "Type 1 if the search pipe is under repair, 0 if not under repair: " << endl;
            ////variant = getchar();
            ////cout << endl;
            //do {
            //    variant = _getch();
            //    if (variant != '0' && variant != '1') cout << "Enter the correct value 1 or 0" << endl;
            //} while (variant != '0' && variant != '1');
            //if (variant == '1' || variant == '0') {
            //    (variant == '1') ? cout << "Pipes is in process: " << endl : cout << "Pipes is not in process:" << endl;
            //    vector<int> index = search_by_repair(pipes, (variant == '1') ? true : false);
            //    if (index.size() != 0) {
            //        for (auto& p : index) {
            //            print_pipe({ p,pipes[p] });
            //        }
            //    }
            //    else cout << "Pipes not found" << endl;
            //}

            ///*cout << "Type id of pipe: ";
            //int name_id = GetCorrectNumber1(0, 1000);
            //int ii = search_by_id(pipes, name_id);
            //if (ii != -1) {
            //    cout << endl;
            //    cout << "Pipes with this id: " << endl;
            //    print_pipe(pipes[ii]);
            //}
            //else
            //    cout << "Pipe with this id not found" << endl;*/

            //cout << "Type percentage ratio of factories is not in process: ";
            //double percent = GetCorrectNumber1(0, 100);
            //vector<int> ind = search_by_ratio(stations, percent);
            //if (ind.size() != 0) {
            //    cout << "Stations with this ratio: " << endl;
            //    for (auto& i : ind) {
            //        print_station({ i,stations[i] });
            //    }
            //}
            //else cout << "Station with this ratio not found" << endl;
            search_and_edit(pipes, stations);
            break;
        }
        case 8:
        {
            cout << "Information about pipes:" << endl;
            if (pipes.size() == 0) {
                cout << "No pipes" << endl; }
            else
                print_pipes(pipes);
            cout << "Information about stations:" << endl;
            if (stations.size() == 0)
                cout << "No stations" << endl;
            else
                print_stations(stations);
            break;
        }
        case 9:
        {
            string name = "";
            cout << "Name of file: ";
            cin.ignore(10000, '\n');
            getline(cin, name);
            name += ".txt";
            ofstream fout;
            fout.open(name, ios::out);
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
        case 10:
        {
            string name = "";
            cout << "Name of file : ";
            cin.ignore(10000, '\n');
            getline(cin, name);
            name += ".txt";
            ifstream fin;
            fin.open(name, ios::in);
            if (fin.fail())
                cout << "File is not exist" << endl;
            else {
                cout << "File is exist" << endl;
                load_all(pipes, stations, fin);
                cout << "Information about pipes:" << endl;
                if (pipes.size() == 0)
                    cout << "No pipes" << endl;
                else
                    print_pipes(pipes);
                cout << "Information about stations:" << endl;
                if (stations.size() == 0)
                    cout << "No stations" << endl;
                else
                    print_stations(stations);
            }
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
