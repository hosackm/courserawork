#include "graph.h"
#include <iostream>
#include <vector>
#include <list>

int main(int argc, char *argv[])
{
    const int nvertices = 50;
    const int min_dist = 1;
    const int max_dist = 10;
    std::vector<double> densities;

    const int num_simulations = 16;

    // Simulate using 0.2 and 0.4 as densities
    densities.push_back(0.2);
    densities.push_back(0.4);

    // run simulation for both densities
    for (double dens : densities){
        // accumulate the average path lengths
        double apl_accum = 0;
        for (int n = 0; n < num_simulations; n++){
            // create new graph and randomize the edges
            Graph g = Graph(nvertices);
            g.randomize(dens, 10, 50);
            // accumulate the path lengths
            int pl_accum = 0;
            // get path length for 0 to 1, 0 to 2, ... , 0 to 49
            for (int i = 1; i < nvertices; ++i){
                // get the shortest path using Dijkstras
                std::list<int> path = g.dijkstraShortestPath(0, i);
                // one edge connects 2 nodes
                pl_accum += path.size() - 1;
            }
            // add this path length to the average path length accumulator
            apl_accum += (double)pl_accum / 49.0;
        }
        // Print out averages to console
        std::cout << "Average path length over " << num_simulations << " runs and density (" << dens << ") = "
                  << apl_accum / num_simulations << std::endl;
    }

    return 0;
}
