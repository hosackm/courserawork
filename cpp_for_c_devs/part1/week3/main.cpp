#include <fstream>
#include "graph.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		std::cerr << "Please provide a data set filename.\n";
		return -1;
	}

    std::ifstream infile;
	infile.open(argv[1]);
    Graph *g = new Graph(infile);
    infile.close();

    MST m;
    m = g->primsAlgo();
    m.display();

    delete g;

    return 0;
}
