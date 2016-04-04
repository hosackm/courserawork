// Single file containing graph code and Monte Carlo simulation
// To compile: clang++ -std=c++11 main.cpp
// To run: ./a.exe <number of simulations>
//         ./a.exe 100
/*

I learned many things while writing the simulation for calculating the average
path.

I had never seen Dijkstras shortest path algorithm (DA) before this class
So much of my time was spent on understanding this algorithm and implementing
it.  In researching C++ implementations of DA, I was introduced to multiple
STL container types.  Namely set, pair, and list.   Using these containers
made the process much quicker.  Since I didn't have to test my implemenation of
these data structures I was able to save a lot of time.

After runing the simulation at 100, 1000, and 10000 simulations I see that
the average path length for 0.2 and 0.4 densities seems to converge around 
slightly above 1.5. I find this interesting considering the densities are
so different.  I would think that many more vertices would be needed to create
such a similar level of connectivity.

Some improvements that I was unable to find time for would be:
    * Implement adjacency list graph
    * Use vectors as adjacency matrix instead of naive arrays
    * Hold data in the graph.  Currently it is only useful for performing
      the calculations in the simulation.  It can't be used for anything else.

*/

#include <list>
#include <iostream> // cout
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <climits> // infinity
#include <set> // set
#include <utility> // pair
#include <vector> // vector

int main(int argc, char *argv[]);

//The Edge struct represents the edge between two vertices.  At initialization
//all vertices have non-existent edges connecting them to all other vertices
//but only when Edge.exists is set to true do these connections exist.
typedef struct _Edge {
    int cost; // cost to travel across this edge
    bool exists; // does the connection exist
}Edge;

//Class defining the Graph data structure.  The edges were implemented using
//the adjacency matrix
class Graph {
public:
    Graph(int numVertices);
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
    // Get the list of neighbors src has edges to
    std::list<int> getNeighbors(int src);
    int numVertices(){ return nVertices; }
    // Return the cost of the shortest path from
    // src to dst using Dijkstra's algorithm
    std::list<int> dijkstraShortestPath(int src, int dst);
private:
    Edge *edgeMatrix;
    int nVertices;
};


// **************************************************************************
// *************************Graph Implementation*****************************
// **************************************************************************
Graph::Graph(int numVertices){
    nVertices = numVertices;
    edgeMatrix = new Edge[numVertices*numVertices];
}

Graph::~Graph(){
    delete []edgeMatrix;
}

void Graph::randomize(double dens, double min, double max){
    // seed the random number generator
    srand((unsigned)time(0));

    // iterate over every vertex
    for(int i = 0; i < nVertices; ++i){
        for(int j = 0; j < nVertices; ++j){
            // probability that edge should be added
            double p = (double) rand() / RAND_MAX ;
            if(p < dens){
                // cost of edge between min and max
                double cost = (double)rand() / RAND_MAX *  (max - min) + min;
                // add the edge and set its cost
                this->add(i, j);
                this->setEdgeValue(i, j, (int)cost);
            }
        }
    }
}

bool Graph::adjacent(int src, int dst){
    if (src >= nVertices || dst >= nVertices){
        return false;
    }
    return edgeMatrix[src*nVertices + dst].exists == true;
}

void Graph::add(int src, int dst){
    if (src >= nVertices || dst >= nVertices){
        return;
    }
    /* Edges are undirectional so if Vertex A has
    an edge with Vertex B Vertex B has an edge
    with Vertex A */
    edgeMatrix[src*nVertices + dst].exists = true;
    edgeMatrix[dst*nVertices + src].exists = true;
}

void Graph::remove(int src, int dst){
    if (src >= nVertices || dst >= nVertices){
        return;
    }
    /* Edges are undirectional so if Vertex A has
    an edge with Vertex B Vertex B has an edge
    with Vertex A */
    edgeMatrix[src*nVertices + dst].exists = false;
    edgeMatrix[dst*nVertices + src].exists = false;
}

int Graph::getEdgeValue(int src, int dst){
    if (src >= nVertices || dst >= nVertices){
        return -1;
    }
    return edgeMatrix[src*nVertices + dst].cost;
}

void Graph::setEdgeValue(int src, int dst, int val){
    // restrict negative costs
    val = val < 0 ? 0 : val;
    if (src >= nVertices || dst >= nVertices){
        return;
    }
    /* Set the cost for both edges since they are not directional */
    edgeMatrix[src*nVertices + dst].cost = val;
    edgeMatrix[dst*nVertices + src].cost = val;
}

std::list<int> Graph::getNeighbors(int src){
    std::list<int> nbrs;
    for (int dst = 0; dst < nVertices; ++dst){
        if (this->adjacent(src, dst) && dst != src){
            nbrs.push_back(dst);
        }
    }
    return nbrs;
}

std::list<int> Graph::dijkstraShortestPath(int src, int dst){
    if (src >= nVertices || dst >= nVertices){
        return std::list<int>();
    }
    if (src == dst){
        return std::list<int>();
    }

    std::vector<int> min_distance;
    std::vector<int> previous;

    // seed all values with INT_MAX (virtually infinity)
    min_distance.resize(nVertices, INT_MAX);
    min_distance[src] = 0; // source set to 0 in order to choose it first

    previous.resize(nVertices, -1);

    std::set<std::pair<int, int>> vertex_queue; // weight / vertex
    vertex_queue.insert(std::make_pair(min_distance[src], src));

    while (!vertex_queue.empty()){
        int dist = vertex_queue.begin()->first;
        int u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        for (int n : this->getNeighbors(u)){
            int v = n;
            int weight = this->getEdgeValue(u, v);
            int dist_through_u = dist + weight;

            if (dist_through_u < min_distance[v]){
                vertex_queue.erase(std::make_pair(min_distance[v], v));

                min_distance[v] = dist_through_u;
                previous[v] = u;
                vertex_queue.insert(std::make_pair(min_distance[v], v));
            }
        }
    }

    // Recreate path from previous vector
    std::list<int> path;
    int vertex = dst;
    for (; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}

// ***************************************************************************
// *************************Monte Carlo Simulation****************************
// ***************************************************************************

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cerr << "Please provide number of simulations";
        return -1;
    }

    const int nvertices = 50;
    const int min_dist = 1;
    const int max_dist = 10;
    const int num_simulations = atoi(argv[1]);

    std::vector<double> densities;

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

            // accumulate the path lengths 0-1, 0-2, ... , 0-49
            int pl_accum = 0;
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
        std::cout << "Average path length over " << num_simulations
                  << " runs and density (" << dens << ") = "
                  << apl_accum / num_simulations << std::endl;
    }

    return 0;
}
