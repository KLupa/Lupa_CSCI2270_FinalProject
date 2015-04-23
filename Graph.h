#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    std::vector<adjVertex> adj;
    bool visited;
    int ID;
    int index;
    int distance;
    vertex* previous;
    int infestation;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void assignDistrict(std::string startingCity, int district);
        int findDistrectless();
        void displayDistricts();
        void shortestpath(std::string c1, std::string c2);
        void shortestdistance(std::string c1, std::string c2);
        void resetdistricts();
        void updateinfestation(std::string name, int level);
        void checkinfestation();
        void deletecity(std::string cityname);
        void districtinfestation();
        void survival(std::string start, std::string dest);
        void alphabetize();
        void districtsort(int left, int right);
        int getsize();
    protected:
    private:
        std::vector<vertex> vertices;

};

#endif // GRAPH_H
