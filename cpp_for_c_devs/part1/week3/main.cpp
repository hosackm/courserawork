#include <iostream>
#include <fstream>
#include <list>
#include "graph.h"

int main(int argc, char* argv[]){
    std::ifstream infile;
    infile.open("data.txt");
    //Graph *g = graphFromFile(infile);
    Graph *g = new Graph(infile);
    infile.close();

    std::cout << "Vertex 2 is neighbors with: ";
    for(auto n : g->getNeighbors(2)){
        std::cout << n << " ";
    }
    std::cout << std::endl;

    delete g;

    return 0;
}
