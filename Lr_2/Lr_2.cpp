// Lr_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Header.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include "pipe.h"
#include "station.h"

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
int SearchId(const T& map, int id)
{
    if (map.find(id) != map.end()) return id;
    return -1;
}
template <typename T>
T GetCorrectNumber2(T min)
{
    T x;
    while ((cin >> x).fail() || x < min)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (0...): ";
    }
    return x;
}


void pipe_process(const Pipe& pipe)
{
    if (pipe.getProc())
        cout << "Pipe is in process" << endl;
    else
        cout << "Pipe is not in process" << endl;
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
            fin >> mypipe;
            pipes.insert({ mypipe.getId(), mypipe });
        }
    }
    if (stationcount != 0) {
        for (int i = 0; i < stationcount; ++i) {
            Station mystation;
            fin >> mystation;
            stations.insert({ mystation.getId(), mystation });
        }
    }
}


//void print_pipe(const pair <int, Pipe>& pipe)
//{
//    cout << "\tId: " << pipe.first
//        << "\tName: " << pipe.second.name
//        << "\tLength: " << pipe.second.length
//        << "\tDiameter: " << pipe.second.diameter << endl;
//    pipe_process(pipe.second);
//    cout << endl;
//}
//
//void print_station(const pair <int, Station>& station)
//{
//    cout << "\tId: " << station.first
//        << "\tName: " << station.second.name << endl
//        << "\tNumber of factories: " << station.second.num << endl
//        << "\tNumber of factories in process: " << station.second.num_process << endl
//        << "\tEfficiency: " << station.second.eff << endl;
//    cout << endl;
//}

void print_pipes(const unordered_map <int, Pipe>& pipes)
{
    for (auto& [id,p] : pipes) cout << p;
}

void print_stations(const unordered_map <int, Station>& stations)
{
    for (const auto& [id, s] : stations)
        cout << s;
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

int edit_pipes(unordered_map <int, Pipe>& pipes)
{
    int id;
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber2(0);
        if (SearchId(pipes, id) != -1) {
            pipes[id].edit();
            cout << "Object was edited" << endl;
            return id;
        }
        else cout << "Object with this id not found" << endl;
    }
}

int edit_stations(unordered_map <int, Station>& stations)
{
    int id;
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber2(0);
        if (SearchId(stations, id) != -1) {
            stations[id].edit();
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


void save_pipes(const unordered_map <int, Pipe>& pipes, ofstream& fout)
{
    for (auto& p : pipes)
        fout << p.second;
}

void save_stations(const unordered_map <int, Station>& stations, ofstream& fout)
{
    for (auto& s : stations)
        fout << s.second;
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
    return map.getName() == name;
}

bool search_by_repair(const Pipe& pipes, const bool& r)
{
    return pipes.getProc() == r;
}

vector<int> search_by_repair(const unordered_map <int, Pipe>& pipes, const bool& r)
{
    int i = 0;
    vector<int> index;
    for (auto& p : pipes) {
        if (p.second.getProc() == r)
            index.emplace_back(p.first);
    }
    return index;
}

bool search_by_ratio(const Station& stations, double per)
{
    return (round(((double(stations.getNum()) - double(stations.getNumP())) / double(stations.getNum())) * 100) == per);
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
                    cout << pipes[id];
                }
                cout << "1. Edit found pipes" << endl
                    << "0. Exit" << endl;
                switch (GetCorrectNumber1(0, 1)) {
                case 1: {
                    for (auto& id : index) {
                        pipes[id].edit();
                        cout << pipes[id];
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
                        cout << pipes[id];
                    }
                    cout << "1. Edit found pipes" << endl 
                        << "0. Exit" << endl;
                    switch (GetCorrectNumber1(0, 1)) {
                    case 1: {
                        for (auto& id : index) {
                            pipes[id].edit();
                            cout << pipes[id];
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
                    cout << pipes[id] << endl;
                }
                cout << "1. Edit found pipes" << endl
                    << "0. Exit" << endl;
                switch (GetCorrectNumber1(0, 1)) {
                case 1: {
                    for (auto& id : edit_id) {
                        pipes[id].edit();
                        cout << pipes[id] << endl;
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
            << "3. Search for stations by id" << endl
            << "0. Exit" << endl;
        switch (GetCorrectNumber1(0, 3)) {
        case 1: {
            cout << "Type name of station: ";
            string name = "";
            cin.ignore(10000, '\n');
            getline(cin, name);
            vector<int> index = search_filter(stations, search_by_name, name);
            if (index.size() != 0) {
                cout << "Found " << index.size() << " stations" << endl;
                for (auto& id : index) {
                    cout << stations[id];
                }
                cout << "1. Edit found stations" << endl
                    << "0. Exit" << endl;
                switch (GetCorrectNumber1(0, 1)) {
                case 1: {
                    for (auto& id : index) {
                        stations[id].edit();
                        cout << stations[id] << endl;
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
                        cout << stations[id];
                    }
                    cout << "1. Edit found stations" << endl
                        << "0. Exit" << endl;
                    switch (GetCorrectNumber1(0, 1)) {
                    case 1: {
                        for (auto& id : index) {
                            stations[id].edit();
                            cout << stations[id];
                        }
                    }
        case 3: {
            cout << "Enter id of stations you want to edit or 0 to complete the entry: " << endl;
            int variant;
            vector<int> edit_id;
            do {
                variant = GetCorrectNumber2(0);
                if (SearchId(stations, variant) != -1)
                    edit_id.emplace_back(variant);
            } while (variant != 0);
            if (edit_id.size() != 0) {
                cout << "Found " << edit_id.size() << " stations" << endl;
                for (auto& id : edit_id) {
                    cout << stations[id] << endl;
                    stations[id].edit();
                    cout << "1. Edit found pipes" << endl
                        << "0. Exit" << endl;
                    switch (GetCorrectNumber1(0, 1)) {
                    case 1: {
                        for (auto& id : edit_id) {
                            stations[id].edit();
                            cout << stations[id] << endl;
                        }
                    }
                    case 0:
                        return;
                    default:
                        cout << "Wrong action" << endl;
                        break;
                    }
                }
            }
            else cout << "No stations with this id" << endl;
            break;
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
    while (1)
    {
        print_menu();
        switch (GetCorrectNumber1(0, 10))
        {
        case 1:
        {           
            Pipe pipe;
            cin >> pipe;
            pipes.insert({ pipe.getId(),pipe });
        break;
        }
        case 2:
        {   
            Station station;
            cin >> station;
            stations.insert({ station.getId(),station });
            break;
        }
        case 3:
        {   if (pipes.size() == 0)
            cout << "Pipes to edit not found" << endl;
        else {
            int id = edit_pipes(pipes);
            cout << pipes[id];
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
            cout << stations[id];
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
