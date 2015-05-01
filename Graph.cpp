#include "Graph.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
/*
Function Prototype:
void addEdge(string, string, int)

Function Description:
This method adds an 'edge' in the graph connecting two cities. It first finds the cities (or returns if one or both are not found)
and then adds each 'city' vertex to the other's adjacent vertices vector with the edge weight given as an input.

Example:
Graph g;
g.addEdge("city1", "city2", 50);

Precondition: Cities are stored in the private 'vertices' vector with connecting cities and distances stored in their adjacency vectors.

Postcondition: Input cities have their adjacency vectors updated to include each other with the distance set by the 'weight' input.
*/
void Graph::addEdge(string v1, string v2, int weight){
    for(int i = 0; i < vertices.size(); i++){
        //find first city
        if(vertices[i]->name == v1){
            for(int j = 0; j < vertices.size(); j++){
                //find second city, ensure it isn't the same as the first
                if(vertices[j]->name == v2 && i != j){
                    for(int k = 0; k < vertices[i]->adj.size(); k++){
                            vertex *x = vertices[i]->adj[k].v;
                        if(x->name == vertices[j]->name){
                            return;
                        }
                    }
                    //add adjacent vertec signifying edge
                    adjVertex av;
                    av.v = vertices[j];
                    av.weight = weight;
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    av2.weight = weight;
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}

/*
Function Prototype:
void Graph::addVertex(string)

Function Description:
This method adds a 'city' to the graph as a vertex in the vertices vector, returning if it is already in the graph.

Example:
Graph g;
g.addVertex("city1");

Precondition: Graph could have any number of vertices in it or it could be empty.

Postcondition: New city is added as a vertex to the end of the vertices vector. Graph is otherwise unchanged.
*/
void Graph::addVertex(string n){
    bool found = false;
    //check if it already exists
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == n){
            found = true;
            cout<<vertices[i]->name<<"Already in network"<<endl;
        }
    }
    if(found == false){
        vertex *v = new vertex;
        v->name = n;
        v->ID = -1;
        v->infestation = 0;
        v->index = vertices.size();
        vertices.push_back(v);
    }
}
/*
Function Prototype:
void Graph::displayEdges()

Function Description:
This method loops through the vertices vector and the adjacency vector of each vertex, printing each vertex' name and which other vertices it
connects to.

Example:
Graph g;
g.displayEdges();

Precondition: The graph can be empty or full, vertices are stored in the vertices vector.

Postcondition: The graph is unchanged by this method.
*/
void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->ID<<":";
        cout<<vertices[i]->name<<"-->";
        cout<<vertices[i]->adj[0].v->name;
        for(int j = 1; j < vertices[i]->adj.size(); j++){
            cout<<"***"<<vertices[i]->adj[j].v->name;
        }
        cout<<endl;
    }

}

/*
Function Prototype:
void Graph::assignDistrict(string, int)

Function Description:
This method finds the vertex corresponding to the input city name, then does a breadth-first traversal of the graph starting
from that vertex, assigning the input district ID to each vertex visited in the traversal

Example:
Graph g;
g.assignDistrict("city1", 1);

Precondition: The Graph should not be empty, with cities stored in the vertices vector.

Postcondition: Some, but not necessarily all, of the vertices will have updated 'ID' values indicating they are part of
this newly created district
*/
void Graph::assignDistrict(std::string startingCity, int district){
    vertex *s;
    for(int i = 0; i<vertices.size(); i++){
            //set visited on all to false
        if (vertices[i]->name != startingCity){
            vertices[i]->visited = false;
        }
        else{
            //starting vertex
            vertices[i]->ID = district;
            s = vertices[i];
        }
    }
   s->visited = true;
   vertex Q[30];
   int head = 0;
   int tail = 0;
    Q[tail] = *s;
    tail++;
    //Breadth-first traversal by queuing a vertex then all of its adjacents. Set all of their 'ID' to the input
   while (head != tail){
       vertex u;
       u = Q[head];
       head++;
       for(int i = 0; i<u.adj.size();i++){
           vertex *v = u.adj[i].v;
           if(v->visited == false){
                 v->visited = true;
                 v->ID = district;
                 Q[tail] = *v;
                 tail++;
           }
       }
   }
}
//Auxilary 'getter' function to find the first vertex in the vertices vector that does not yet have a district (signified by ID = -1)
//and return its index
int Graph::findDistrectless(){
for(int i = 0; i < vertices.size(); i++){
    if(vertices[i]->ID == -1){
        return i;
    }
}
//if all vertices have a district assigned
return -1;
}

//Auxilary function to loop through the vertices vector and erase all districts by setting each vertex' ID to -1
void Graph::resetdistricts(){
    for(int i = 0; i < vertices.size(); i++){
        vertices[i]->ID = -1;
    }
}

//Auxilary function that loops through the vertices vector and displays the name of each vertex and its district ID
void Graph::displayDistricts(){
    for(int i = 0; i < vertices.size(); i++){
        std::cout<<vertices[i]->name<<" - "<<vertices[i]->ID<<std::endl;
    }
}

/*
Function prototype:
void Graph::shortestpath(string, string)

Function description:
This method does a breadth-first traversal of the graph beginning at the vertex corresponding to the input starting city name.
For each city it visits, it records where it came from. After the traversal, starting at the vertex corresponding to the input
destination name, it follows the path it took in reverse, counting how many steps it took. It then prints the number of steps and
the path followed from origin to destination.

Example:
Graph g;
g.shortestpath("city1", "city2");

Precondition: Cities are stored in the vertices vector, with edges stored in their adjacency vectors. District IDs should be
set, meaning they should not be -1.

Postcondition: All cities will have their 'visited' attribute set to true. The graph is otherwise unchanged by this function.
*/
void Graph::shortestpath(string c1, string c2){
    int cities[15];
    vertex v1;
    vertex v2;
    for(int i = 0; i<vertices.size(); i++){
        if (vertices[i]->name != c1){
            vertices[i]->visited = false;
            if (vertices[i]->name == c2){
                //destination
                v2 = *vertices[i];
            }
        }
        else {
            //beginning
            v1 = *vertices[i];
            vertices[i]->visited = true;
        }
        cities[i] = -1;
    }
    if(v1.name == "" || v2.name == ""){
        cout<<"One or more cities doesn't exist"<<endl;
        return;
    }
    if(v1.ID != v2.ID){
        cout<<"Cities not connected"<<endl;
        return;
    }
    vertex Q[15];
    int head = 0;
    int tail = 0;
    Q[tail] = v1;
    tail++;
    //Breadth-first traversal by queuing a vertex then all of its adjacents
    while(head != tail){
        vertex u;
        u = Q[head];
        head++;
        for(int i = 0; i<u.adj.size();i++){
           vertex *v = u.adj[i].v;
           if(v->visited == false){
                 v->visited = true;
                 //store where it came from in index-array style
                 //hindsight could have just used 'previous' attribute, but it works
                 cities[v->index] = u.index;
                 Q[tail] = *v;
                 tail++;
           }
       }
    }
    //set up a queue for printing the path taken
    int prev = 0;
    int S[15];
    int top = 0;
    int dist = 0;
    prev = v2.index;
    S[top] = prev;
    top++;
    prev = cities[prev];
    while(prev != -1){
        //follow path, add up steps
        S[top] = prev;
        top++;
        prev = cities[prev];
        dist++;
    }
    cout<<dist;
    top--;
    while(top != -1){
        //dequeue the path and print
        cout<<","<<vertices[S[top]]->name;
        top--;
    }
    cout<<endl;
}

/*
Function prototype:
void Graph::shortestdistance(string, string)

Function description:
This method used Dijkstra's shortest distance algorithm to find the shortest distance between two vertices given their edge weights.
It begins at the vertex corresponding to the input origin city name, then uses a breadth-first search of the graph to determine the
shortest distance to each vertex based on edge weights until the destination vertex is visited. It then prints out the distance and
the path taken.

Example:
Graph g;
g.shortestdistance("city1", "city2");

Precondition: Cities are stored in the vertices vector, with edges and edge weights stored in their individual adjacency vectors.

Postcondition: Most or all cities will have their 'visited' attribute changed to true. The graph is otherwise unchanged.

*/
void Graph::shortestdistance(string starting, string destination){
    vertex *start;
    vertex *dest;
    for(int i = 0; i<vertices.size(); i++){
        if (vertices[i]->name != starting){
            //set all visited to false and all distances to a huge number
            vertices[i]->visited = false;
            vertices[i]->distance = 1000000;
            if (vertices[i]->name == destination){
                dest = vertices[i];
            }
        }
        else {
            vertices[i]->visited = true;
            vertices[i]->distance = 0;
            start = vertices[i];
        }
    }
    if (start->name == "" || dest->name == ""){
        cout<<"One or more cities not found"<<endl;
        return;
    }
    if (start->ID != dest->ID){
        cout<<"Cities not connected"<<endl;
        return;
    }
    //create a vector to keep track of solved vertices
    vector<vertex*> solved;
    solved.push_back(start);
    while(dest->visited == false){
        //create a vector to keep track of choices in where to go along the path
        vector<vertex*> choices;
        for(int i = 0; i < solved.size(); i++){
                vertex *u = solved[i];
            for(int j = 0; j < solved[i]->adj.size(); j++){
                vertex *v = u->adj[j].v;
                if(v->visited == false){
                    //set distance to the vertex as distance up to the previous step plus edge weight in that step
                    int dist = u->distance + u->adj[j].weight;
                    if(dist < v->distance){
                        //if this distance is shorter than the previously logged distance to the same vertex, change it.
                        v->distance = dist;
                        v->previous = u;
                    }
                    choices.push_back(v);
                }
            }
        }
        int mindistance = 1000000;
        int choice = -1;
        //make choice from vector with shortest distance
        for(int i = 0; i < choices.size(); i++){
            if(choices[i]->distance < mindistance){
                choice = i;
                mindistance = choices[i]->distance;
            }
        }
        //add to solved and mark visited
        solved.push_back(choices[choice]);
        choices[choice]->visited = true;
    }
    //set up stack for printing the path
    start->previous = NULL;
    vertex *temp = dest;
    vertex *printstack[20];
    int top = 0;
    while(temp != NULL){
        printstack[top] = temp;
        top++;
        temp = temp->previous;
    }
    top--;
    cout<<"Shortest Path"<<endl;
    while(top != 0){
        temp = printstack[top];
        cout<<temp->name<<" - ";
        top--;
    }
    temp = printstack[top];
    cout<<temp->name<<endl;
    cout<<"Minimum Distance: "<<dest->distance<<" miles"<<endl;
}

/*
Function prototype:
void Graph::updateinfestation(string, int)

Function description:
This method loops through the vertices vector, finds the one corresponding to the input city name, then updates its 'infestation'
attribute to the input value

Example:
Graph g;
g.updateinfestation("city1", 50)

Precondition: Cities are stored in the vertices vector.

Postcondition: All conditions remain the same except for the one vertex that had its 'infestation' attribute changed.
*/
void Graph::updateinfestation(std::string name, int level){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == name){
            vertices[i]->infestation = level;
            return;
        }
    }
}

//Auxilary function that prints all cities in the vertices vector and their infestation attribute
void Graph::checkinfestation(){
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<" - "<<vertices[i]->infestation<<"% infested"<<endl;
    }
}

/*
Function prototype:
void Graph::districtinfestation()

Function description:
This method loops through the vertices vector and adds up the infestation attributes for each vertex by district ID and
keeps a total overall. It then prints the average infestation level of cities in each district and the overall average.

Example:
Graph g;
g.districtinfestation();

Precondition: Cities are stored in the vertices vector, with district IDs set. (Function will not work if district IDs are not set [= -1])

Postcondition:
*/
void Graph::districtinfestation(){
    //keeps track of infestation totals
    int data[6];
    //keeps track of number of cities in each district
    int sizes[6];
    for(int i = 0; i < 6; i++){
        data[i] = 0;
        sizes[i] = 0;
    }
    int districts = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->ID > districts){
            //keeps highest district ID (signifying total # of districts)
            districts = vertices[i]->ID;
        }
        data[vertices[i]->ID] += vertices[i]->infestation;
        sizes[vertices[i]->ID]++;
    }
    double avg = 0;
    int total = 0;
    //calculate average values and print
    for(int i = 1; i < districts + 1; i++){
        avg = data[i]/sizes[i];
        total += data[i];
        cout<<"Average infestation level of district "<<i<<": "<<avg<<endl;
    }
    avg = total/vertices.size();
    cout<<"Overall average infestation level: "<<avg<<endl;

}

/*
Function Prototype:
void Graph::survival(string, string)

Function Description:
This method is very similar to the shortestdistance function. It uses Dijkstra's shortest distance algorithm to find the shortest distance
between two cities specified by the inputs. However this time it also adds up the infestation levels of cities visited along the way. It then
calculates a survival chance based on the distance traveled and the infestation level of the cities visited along the way, including the origin
and destination cities.

Example:
Graph g;
g.survival("city1","city2");

Precondition: Cities are stored in the vertices vector. Districts must be assigned. Infestation levels should be between 0 and 100.

Postcondition: Graph is unchanged.
*/
void Graph::survival(std::string starting, std::string destination){
    //see shortestdistance function for more detailed comments
    vertex *start;
    vertex *dest;
    for(int i = 0; i < vertices.size(); i++){
        if (vertices[i]->name != starting){
            vertices[i]->visited = false;
            vertices[i]->distance = 1000000;
            if (vertices[i]->name == destination){
                dest = vertices[i];
            }
        }
        else {
            vertices[i]->visited = true;
            vertices[i]->distance = 0;
            start = vertices[i];
        }
    }

    if (start->name == "" || dest->name == ""){
        cout<<"One or more cities not found"<<endl;
        return;
    }
    if (start->ID != dest->ID){
        cout<<"Cities not connected"<<endl;
        return;
    }

    vector<vertex*> solved;
    solved.push_back(start);
    while(dest->visited == false){
        vector<vertex*> choices;
        for(int i = 0; i < solved.size(); i++){
                vertex *u = solved[i];
            for(int j = 0; j < solved[i]->adj.size(); j++){
                vertex *v = u->adj[j].v;
                if(v->visited == false){
                    int dist = u->distance + u->adj[j].weight;
                    if(dist < v->distance){
                        v->distance = dist;
                        v->previous = u;
                    }
                    choices.push_back(v);
                }
            }
        }
        int mindistance = 1000000;
        int choice = -1;
        for(int i = 0; i < choices.size(); i++){
            if(choices[i]->distance < mindistance){
                choice = i;
                mindistance = choices[i]->distance;
            }
        }
        solved.push_back(choices[choice]);
        choices[choice]->visited = true;
    }
    start->previous = NULL;
    vertex *temp = dest;
    vertex *printstack[20];
    int top = 0;
    int infestation = 0;
    while(temp != NULL){
        printstack[top] = temp;
        top++;
        //add infestation level of each city
        infestation += temp->infestation;
        temp = temp->previous;
    }
    top--;
    cout<<"\nPath"<<endl;
    while(top != 0){
        temp = printstack[top];
        cout<<temp->name<<" - ";
        top--;
    }
    temp = printstack[top];
    cout<<temp->name<<endl;
    //% chance of survival, starts at 100
    double survival = 100;
    //subtract amount based on distance traveled
    survival = survival - (dest->distance * .02);
    //subtract amount based on infestation level of cities visited
    survival = survival - (infestation * 0.35);
    survival = round(survival);
    if(survival < 0){
        survival = 0;
    }
    cout<<"Chance of survival: "<<survival<<"%\n"<<endl;
}

/*
Function Prototype:
void Graph::deletecity(string)

Function Description:
This method takes an input name of a city to delete from the graph. It first loops through the vertices vector, and subsequently through
the adjacency vector for each vertex, and if it finds that city, deletes it from the adj vector for that vertex. It then goes through the
vertices vector, finds the vertex with the name to be deleted, and deletes that vertex. Finally it resets the 'index' attribute of all
vertices.

Example:
Graph g;
g.deletecity("city1");

Precondition: The cities are stored in the vertices vector, with their connections stored in their individual 'adj' adjacency vectors, with
their position in the vertices vector stored in their 'index' attribute.

Postcondition: The city to be deleted is no longer in the vertices vector, and it is also removed from the adjacency vectors of each vertex
that was connected to it. Index attribute of most or all vertices changes to reflect their new position in the vector.
*/
void Graph::deletecity(string cityname){
    //loop through each vertex' adj vector and delete if found
    for(int i = 0; i < vertices.size(); i++){
        for(int j = 0; j < vertices[i]->adj.size(); j++){
            if(vertices[i]->adj[j].v->name == cityname){
                vertices[i]->adj.erase(vertices[i]->adj.begin() + j);
                break;
            }
        }
    }
    //find and delete city from vertices
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == cityname){
            vertices.erase(vertices.begin() + i);
            break;
        }
    }
    //reset 'index' attribute for all vertices
    for(int k = 0; k < vertices.size(); k++){
        vertices[k]->index = k;
    }
}

/*
Function prototype:
void Graph::alphabetize()

Function Description:
This method uses an insertion sort algorithm to sort the vertices vector by vertex 'name' attribute in alphabetical order.

Example:
Graph g;
g.alphabetize();

Precondition: Cities are stored in the vertices vector in any order.

Postcondition: Cities are stored in the vertices vector in alphabetical order.
*/
void Graph::alphabetize(){
    vertex *index;
    for(int i = 0; i < vertices.size(); i++){
        index = vertices[i];
        int j = i;
        //move until in the right spot
        while(j > 0 && strcmp(vertices[j-1]->name.c_str(), index->name.c_str()) > 0){
            vertices[j] = vertices[j - 1];
            j--;
        }
        vertices[j] = index;
    }
}

//getter for the size of the vertices vector
int Graph::getsize(){
    return vertices.size();
}

/*
Function prototype:
void Graph::districtsort(int, int)

Function description:
This method uses a recursive quicksort algorithm to sort the vertices vector by the vertices' 'ID' atrribute.

Example:
Graph g;
g.districtsort(0,g.getsize() - 1);

Precondition: Cities are stored in the vertices vector in any order. District IDs must be set (not = -1). First input should
be 0 for the beginning of the vector, and the second input should use the g.getsize() function and subtract 1 for the end of the vector.

Postcondition: Cities are stored in the vertices vector in  increasing numerical order based upon their 'ID' attribute. Cities with
the same 'ID' are not necessarily listed in alphabetical order.
*/
void Graph::districtsort(int left, int right){
    int i = left;
    int j = right;
    vertex *temp;
    //set pivot to vertex halfway between the left and right index
    int pivot = vertices[(left + right) / 2]->ID;
    while(i <= j){
        //find vertex on left side that it out of place
        while(vertices[i]->ID < pivot){
            i++;
        }
        //find vertex on right side that it out of place
        while(vertices[j]->ID > pivot){
            j--;
        }
        //if it isnt sorted yet
        if(i <= j){
            //swap the two
            temp = vertices[i];
            vertices[i] = vertices[j];
            vertices[j] = temp;
            i++;
            j--;
        }
    }
    //recursively call on the left subvector if not sorted yet
    if(left < j){
        districtsort(left, j);
    }
    //recursively call on the right subvector if not sorted yet
    if(right > i){
        districtsort(i, right);
    }
}



