#include "graph.h"
#include <iostream> // cout
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <climits> // infinity
#include <set> // set
#include <utility> // pair
#include <vector> // vector
#include <string> // string

Graph::Graph(int numVertices){
    nVertices = numVertices;
    // Create vector of vectors
	edgeMatrix = std::vector<std::vector<Edge> >(nVertices);
	for(int i = 0; i < nVertices; ++i){
		std::vector<Edge> col = std::vector<Edge>(nVertices);
		// Vertices should have edges with themselves
		col.at(i).exists = true;
		edgeMatrix.at(i) = col;
	}

	vertices = new std::vector<int>(numVertices);
}

Graph::Graph(std::ifstream &datafile){
	if (datafile.is_open()){
		std::string line;
		std::getline(datafile, line);

		int numNodes = atoi(line.c_str());
		std::cout << "Num Nodes: " << numNodes << std::endl;

		while (std::getline(datafile, line)){
			std::cout << line << std::endl;
		}
		datafile.close();
	}
}

Graph::~Graph(){
	delete vertices;
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

	return edgeMatrix.at(src).at(dst).exists == true;
}

void Graph::add(int src, int dst){
	if (src >= nVertices || dst >= nVertices){
		return;
	}
	/* Edges are undirectional so if Vertex A has
	an edge with Vertex B Vertex B has an edge
	with Vertex A */
	edgeMatrix.at(src).at(dst).exists = true;
	edgeMatrix.at(dst).at(src).exists = true;
}

void Graph::remove(int src, int dst){
	if (src >= nVertices || dst >= nVertices){
		return;
	}
	/* Edges are undirectional so if Vertex A has
	an edge with Vertex B Vertex B has an edge
	with Vertex A */
	edgeMatrix.at(src).at(dst).exists = false;
	edgeMatrix.at(dst).at(src).exists = false;
}

int Graph::getEdgeValue(int src, int dst){
	if (src >= nVertices || dst >= nVertices){
		return -1;
	}
	return edgeMatrix.at(src).at(dst).cost;
}

void Graph::setEdgeValue(int src, int dst, int val){
    // restrict negative costs
    val = val < 0 ? 0 : val;
	if (src >= nVertices || dst >= nVertices){
		return;
	}
	/* Set the cost for both edges since they are not directional */
	edgeMatrix.at(src).at(dst).cost = val;
	edgeMatrix.at(dst).at(src).cost = val;
}

int Graph::getVertexValue(int num){
	if (num >= nVertices){
		return -1;
	}
	return vertices->at(num);
}

void Graph::setVertexValue(int num, int val){
	if (num >= nVertices){
		return;
	}
	val = val < 0 ? 0 : val;
	vertices->at(num) = val;
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
