#ifndef __GRAPH_H__
#define __GRAPH_H__

// Using adjacency Matrix
#include <vector>
class AdjacencyMatrix;

class Graph {
public:
    Graph(int numVertices);
    ~Graph();
    // Print to stdout
    void display();
    void displayNeighbors(int vertex);
    // are two vertices adjacent
    bool adjacent(int src, int dst);
    // add an edge from src to dst
    void add(int src, int dst);
    // remove edge from src to dst
    void remove(int src, int dst);
    // Get and Set a node's value
    int getNodeValue(int vertex);
    void setNodeValue(int vertex, int val);
    // Get and Set an edge's value (cost)
    int getEdgeValue(int src, int dst);
    void setEdgeValue(int src, int dst, int val);
    // populate vecNeighbors with the neihboring vertices for a vertex
    void neighbors(int src, std::vector<int> &vecNeighbors);
    int numVertices(){
        return nVertices;
    }
private:
    AdjacencyMatrix *edgeMatrix;
    std::vector<int> vertexValues;
    int nVertices;
};
#endif
