#include "graph.h"
#include <iostream>

typedef struct _Edge {
    int cost;
    bool exists;
}Edge;

class AdjacencyMatrix{
public:
    AdjacencyMatrix(int numVertices){
        //Alloc mem
        matrix = new Edge[numVertices*numVertices];

        //Set all vertices adjacent to themselves
        for(int i = 0; i < numVertices; ++i){
            matrix[numVertices*i + i].exists = true;
        }

        //Store numVertices
        nVertices = numVertices;
    }

    ~AdjacencyMatrix(){
        delete [] matrix;
    }

    void display(){
        // Display each row line by line
        for(int i = 0; i < nVertices; ++i){
            for(int j = 0; j < nVertices; ++j){
                std::cout << matrix[i*nVertices+j].exists << " ";                
            }
            std::cout << std::endl;
        }
    }

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
        /* Edges are not directional so if Vertex A has
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
    // Edge getEdge(int x, int y){
    //     return matrix[x*nVertices+y];
    // }
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
    edgeMatrix->setEdgeCost(src, dst, val);
}

void Graph::neighbors(int src, std::vector<int> &vecNeighbors){
    for(int dst = 0; dst < nVertices; dst++){
        if(dst == src){
            continue;
        }
        if(this->adjacent(src, dst)){
            vecNeighbors.push_back(dst);
        }
    }
}

void Graph::displayNeighbors(int vertex){
    std::vector<int> ns;
    this->neighbors(vertex, ns);
    std::cout << "Neighbors for " << vertex << ":";
    for(int i = 0; i < ns.size(); ++i){
        if(i > 0){
            std::cout << "->";
        }
        std::cout << ns.at(i);
    }
    std::cout << std::endl;
}
