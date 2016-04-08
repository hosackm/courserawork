#include <iostream>
#include <fstream>
#include <list>
#include "graph.h"

int main(int argc, char* argv[]){
    std::ifstream infile;
    infile.open("data3.txt");
    Graph *g = new Graph(infile);
    infile.close();

    g->primsAlgo();

    delete g;

    return 0;
}
