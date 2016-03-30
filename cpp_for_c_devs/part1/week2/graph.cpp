#include "graph.h"
#include <iostream>

//The Edge struct represents the edge between two vertices.  At initialization
//all vertices have non-existent edges connecting them to all other vertices
//but only when Edge.exists is set to true do these connections exist.
typedef struct _Edge {
    int cost; // cost to travel across this edge
    bool exists; // does the connection exist
}Edge;

class AdjacencyMatrix{
public:
    AdjacencyMatrix(int numVertices){
        //Alloc mem
        matrix = new Edge[numVertices*numVertices];

        //Set all vertices adjacent to themselves.  Edges to other vertices
        //do not exist yet.
        for(int i = 0; i < numVertices; ++i){
            matrix[numVertices*i + i].exists = true;
        }

        //Store numVertices
        nVertices = numVertices;
    }

    ~AdjacencyMatrix(){
        delete [] matrix;
    }

    //Display each row line by line
    void display(){
        for(int i = 0; i < nVertices; ++i){
            for(int j = 0; j < nVertices; ++j){
                std::cout << matrix[i*nVertices+j].exists << " ";                
            }
            std::cout << std::endl;
        }
    }

    //Check if two vertices are adjacent (an edge exists between them)
    bool isAdjacent(int x, int y){
        if(x >= nVertices || y >= nVertices){
            return false;
        }
        return matrix[x*nVertices+y].exists == true;
    }

    void setEdgeExists(int x, int y, bool val){
        if(x >= nVertices || y >= nVertices){
            return;
        }
        /* Edges are undirectional so if Vertex A has
           an edge with Vertex B Vertex B has an edge
           with Vertex A */
        matrix[x*nVertices+y].exists = val;
        matrix[y*nVertices+x].exists = val;
    }

    void setEdgeCost(int x, int y, int val){
        if(x >= nVertices || y >= nVertices){
            return;
        }
        /* Set the cost for both edges since they are not directional */
        matrix[x*nVertices+y].cost = val;
        matrix[y*nVertices+x].cost = val;
    }

    int getEdgeCost(int x, int y){
        return matrix[x*nVertices+y].cost;
    }
    bool isEdge(int x, int y){
        return matrix[x*nVertices+y].exists;
    }
private:
    Edge *matrix;
    int nVertices;
};

Graph::Graph(int numVertices){
    edgeMatrix = new AdjacencyMatrix(numVertices);
    vertexValues = std::vector<int>(numVertices);
    nVertices = numVertices;
}

Graph::~Graph(){
    delete edgeMatrix;
}

void Graph::display(){
    edgeMatrix->display();
}

bool Graph::adjacent(int src, int dst){
    return edgeMatrix->isAdjacent(src, dst);
}

void Graph::add(int src, int dst){
    edgeMatrix->setEdgeExists(src, dst, true);
}

void Graph::remove(int src, int dst){
    edgeMatrix->setEdgeExists(src, dst, false);
}

int Graph::getNodeValue(int vertex){
    return vertexValues.at(vertex);
}

void Graph::setNodeValue(int vertex, int val){
    vertexValues.at(vertex) = val;
}

int Graph::getEdgeValue(int src, int dst){
    return edgeMatrix->getEdgeCost(src, dst);
}

void Graph::setEdgeValue(int src, int dst, int val){
    // restrict negative costs
    val = val < 0 ? 0 : val;
    edgeMatrix->setEdgeCost(src, dst, val);
}

void Graph::neighbors(int src, std::vector<int> &vecNeighbors){
    for(int dst = 0; dst < nVertices; dst++){
        //Don't report edges looping back to the same vertex
        if(dst == src){
            continue;
        }
        if(this->adjacent(src, dst)){
            vecNeighbors.push_back(dst);
        }
    }
}

//Print neighbors to stdout to verify the graph is working
void Graph::displayNeighbors(int vertex){
    //Get neighbors
    std::vector<int> ns;
    this->neighbors(vertex, ns);

    //Print to stdout
    std::cout << "Neighbors for " << vertex << ":";
    for(int i = 0; i < ns.size(); ++i){
        if(i > 0){
            std::cout << "->";
        }
        std::cout << ns.at(i);
    }
    std::cout << std::endl;
}
