#include <iostream>
#include <vector>
#include "Graph.h"
#include <fstream>
#include <cstring>

using namespace std;

string printmenu(){
    cout<<"======Main Menu====="<<endl;
    cout<<"1. List cities and connections"<<endl;
    cout<<"2. Find districts"<<endl;
    cout<<"3. Find shortest path"<<endl;
    cout<<"4. Find shortest distance"<<endl;
    cout<<"5. Add a city"<<endl;
    cout<<"6. Delete a city"<<endl;
    cout<<"7. Update a city's infestation level"<<endl;
    cout<<"8. Check overall infestation status"<<endl;
    cout<<"9. Check infestation status by city"<<endl;
    cout<<"10. Calculate chance of survival"<<endl;
    cout<<"11. Organize cities alphabetically"<<endl;
    cout<<"12. Organize cities by district"<<endl;
    cout<<"13. Quit"<<endl;
    string input;
    string choice;
    getline(cin,choice);
    return choice;
}

int main(int argc, char *argv[])
{
    //initialize each city
    Graph g;
    char* file = argv[1];
    ifstream infile;
    infile.open(file);
    string discard;
    vector<string> cities;
    getline(infile, discard, ',');
    for(int i = 0; i < 14; i++){
        string name;
        getline(infile, name, ',');
        g.addVertex(name);
        cities.push_back(name);
    }
    string last;
    getline(infile, last, '\n');
    g.addVertex(last);
    cities.push_back(last);

    //add edges between cities
    for(int i = 0; i < 15; i++){
        getline(infile, discard, ',');
        for(int j = 0; j < 14; j++){
            string edge;
            getline(infile, edge,',');
            int edgelength = stoi(edge);
            if(edgelength != -1){
                g.addEdge(cities[i],cities[j],edgelength);
            }
        }
        string edge;
        getline(infile, edge,'\n');
        int edgelength = stoi(edge);
        if(edgelength != -1){
            g.addEdge(cities[i],cities[14],edgelength);
        }
    }

    string choice = "";
    while(choice != "13"){
        choice = printmenu();
        if(choice == "1"){
            g.displayEdges();
        }
        else if(choice == "2"){
            int next = 0;
            int district = 1;
            while(next != -1){
                g.assignDistrict(cities[next], district);
                next = g.findDistrectless();
                district++;
            }
            g.displayDistricts();
        }
        else if(choice == "3"){
            string first;
            cout<<"Enter a starting city:"<<endl;
            getline(cin, first);
            string second;
            cout<<"Enter an ending city:"<<endl;
            cin>>second;
            if(g.findDistrectless() != -1){
                cout<<"Please identify the districts before checking distances"<<endl;
            }
            else{
                g.shortestpath(first, second);
            }
        }
        else if(choice == "4"){
            string first;
            string second;
            cout<<"Enter a starting city:"<<endl;
            getline (cin, first);
            cout<<"Enter an ending city:"<<endl;
            getline (cin, second);
            if(g.findDistrectless() != -1){
                cout<<"Please identify the districts before checking distances"<<endl;
            }
            else{
                g.shortestdistance(first, second);
            }
        }
        else if(choice == "5"){
            string cityname;
            cout<<"Enter city name:"<<endl;
            getline (cin, cityname);
            bool found = false;
            for(int i = 0; i < cities.size(); i++){
                if(cities[i] == cityname){
                    cout<<"City already exists"<<endl;
                    found = true;
                    break;
                }
            }
            if(found == false){
                g.addVertex(cityname);
                cities.push_back(cityname);
                for(int i = 0; i < cities.size() - 1; i++){
                    cout<<"Enter distance in miles to "<<cities[i]<<". (Enter -1 if they do not safely connect)"<<endl;
                    string weightin;
                    cin>>weightin;
                    int weight = stoi(weightin);
                    if(weight != -1){
                        g.addEdge(cityname,cities[i],weight);
                    }
                }
                int next = 0;
                int district = 1;
                g.resetdistricts();
                while(next != -1){
                    g.assignDistrict(cities[next], district);
                    next = g.findDistrectless();
                    district++;
                }
                g.displayDistricts();
            }
        }
        else if(choice == "6"){
            string cityname;
            cout<<"Enter city name:"<<endl;
            getline (cin, cityname);
            bool found = false;
            int deletehere = -1;
            for(int i = 0; i < cities.size(); i++){
                if(cities[i] == cityname){
                    found = true;
                    deletehere = i;
                    break;
                }
            }
            if(found == false){
                cout<<"City does not exist in current network"<<endl;
            }
            else{
                g.deletecity(cityname);
                cities.erase(cities.begin() + deletehere);
                g.resetdistricts();
                int next = 0;
                int district = 1;
            }
        }
        else if(choice == "7"){
            string cityname;
            bool found = false;
            cout<<"Enter city to update infestation level for:"<<endl;
            getline (cin, cityname);
            for(int i = 0; i < cities.size(); i++){
                if(cities[i] == cityname){
                    found = true;
                    break;
                }
            }
            if(found == true){
                cout<<"Enter infestation level (0-100)"<<endl;
                string infestation;
                int level;
                getline (cin, infestation);
                level = stoi(infestation);
                while(level < 0 || level > 100){
                    cout<<"Invalid entry. Please enter an infestation level between 0 and 100"<<endl;
                    getline (cin, infestation);
                    level = stoi(infestation);
                }
                g.updateinfestation(cityname, level);
            }
            else{
                cout<<"City not found"<<endl;
            }
        }
        else if(choice == "8"){
            if(g.findDistrectless() != -1){
                cout<<"Please identify the districts first"<<endl;
            }
            else{
                g.districtinfestation();
            }
        }
        else if(choice == "9"){
            g.checkinfestation();
        }
        else if(choice == "10"){
            string first;
            string second;
            cout<<"Enter a starting city:"<<endl;
            getline (cin, first);
            cout<<"Enter an ending city:"<<endl;
            getline (cin, second);
            if(g.findDistrectless() != -1){
                cout<<"Please identify the districts before calculating survival"<<endl;
            }
            else{
                g.survival(first, second);
            }
        }
        else if (choice == "11"){
            g.alphabetize();
            string index;
            for(int i = 0; i < cities.size(); i++){
                index = cities[i];
                int j = i;
                while(j > 0 && strcmp(cities[j-1].c_str(), index.c_str()) > 0){
                cities[j] = cities[j - 1];
                j--;
                }
                cities[j] = index;
            }
        }
        else if (choice == "12"){
            if(g.findDistrectless() != -1){
                cout<<"Please identify the districts first"<<endl;
            }
            else{
                g.districtsort(0, g.getsize() - 1);
            }
        }
        else if(choice == "13"){
            cout<<"Goodbye!"<<endl;
        }
        else{
            cout<<"invalid choice"<<endl;
        }
    }
    return 0;
}
