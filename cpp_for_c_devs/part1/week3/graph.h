#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream> // ostream
#include <fstream> // ifstream
#include <list> // list
#include <vector> // vector
#include <tuple> // tuple

//The Edge struct represents the edge between two vertices.  At initialization
//all vertices have non-existent edges connecting them to all other vertices
//but only when Edge.exists is set to true do these connections exist.
typedef struct _Edge {
	int cost; // cost to travel across this edge
	bool exists; // does the connection exist
}Edge;

//Abstract definition of Minimum Spanning Tree class
class MST{
    std::vector<std::tuple<int, int, int>> nodes;
public:
    void display();
    void addEdge(int src, int dst, int cost);
};

class Graph {
public:
    Graph(int numVertices);
    Graph(std::ifstream& datafile);
    ~Graph();
    // Function to randomly assign edges based on density and distance range
    void randomize(double density, double min, double max);
    // are two vertices adjacent
    bool adjacent(int src, int dst);
    // add an edge from src to dst
    void add(int src, int dst);
    // remove edge from src to dst
    void remove(int src, int dst);
    // Get and Set an edge's value (cost)
    int getEdgeValue(int src, int dst);
    void setEdgeValue(int src, int dst, int val);
    //Add vertices after construction
    void addVertex();
    // Get and Set an vertex's value (cost)
    int getVertexValue(int num);
    void setVertexValue(int num, int val);
    // Get the list of neighbors src has edges to
    std::list<int> getNeighbors(int src);
    int numVertices(){ return nVertices; }
    // Return the cost of the shortest path from
    // src to dst using Dijkstra's algorithm
    std::list<int> dijkstraShortestPath(int src, int dst);
    // Prims algorithm implementation
    MST primsAlgo();
    // Display through ostream
    friend std::ostream& operator<<(std::ostream& os, Graph& g);
    friend std::ostream& operator<<(std::ostream& os, Graph* const g);
    // Get private edgeMatrix
    std::vector<std::vector<Edge> > getEdgeMatrix();
private:
    std::vector<std::vector<Edge> > edgeMatrix;
    int nVertices;
    std::vector<int> *vertices;
};

#endif
