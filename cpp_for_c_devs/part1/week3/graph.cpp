#include "graph.h"
#include <iostream> // cout
#include <sstream> // stringstream
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <climits> // infinity
#include <set> // set
#include <utility> // pair
#include <vector> // vector
#include <string> // string
#include <algorithm> // count


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

	vertices = new std::vector<Vertex>(numVertices);
}

Graph::Graph(std::ifstream& datafile){
	if(!datafile.is_open())
		return;

	// Read a line from the file
    std::string line;
    std::getline(datafile, line);

    // Convert number of vertices to int and store in this graph
	nVertices = std::stoi(line);

	// Create vector of vectors
	edgeMatrix = std::vector<std::vector<Edge> >(nVertices);
	for(int i = 0; i < nVertices; ++i){
		std::vector<Edge> col = std::vector<Edge>(nVertices);
		// Vertices should have edges with themselves
		col.at(i).exists = true;
		edgeMatrix.at(i) = col;
	}

	// Create vertices
	vertices = new std::vector<Vertex>(nVertices);

	// Add the edges from the file
	while(std::getline(datafile, line)){
    	std::string value;
    	std::vector<int> values;
    	std::stringstream valuesStream(line);

    	while(valuesStream >> value){
    		values.push_back(std::stoi(value));
    	}

    	int src = values.at(0);
    	int dst = values.at(1);
    	int cost = values.at(2);

        this->add(src, dst);
        this->setEdgeValue(src, dst, cost);
    }
}


std::vector<std::vector<Edge> > Graph::getEdgeMatrix(){
	return edgeMatrix;
}


std::ostream& operator<<(std::ostream& os, Graph& g){
	for(auto edgeVec : g.getEdgeMatrix()){
		for(auto vertex : edgeVec){
			if(vertex.exists){
				os << "1 ";
			} else {
				os << "0 ";
			}
		}
		os << "\n";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, Graph* const g){
	os << *g;
	return os;
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

void Graph::addVertex(){
	std::vector<Edge> vert = std::vector<Edge>(nVertices+1);
	edgeMatrix.push_back(vert);
	for(int i = 0; i < nVertices; ++i){
		Edge e;
		edgeMatrix.at(i).push_back(e);
	}
	vertices->push_back(0);
	nVertices++;
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
	std::vector<Vertex> previous;

	// seed all values with INT_MAX (virtually infinity)
	min_distance.resize(nVertices, INT_MAX);
	min_distance[src] = 0; // source set to 0 in order to choose it first

	previous.resize(nVertices, -1);

	std::set<std::pair<int, Vertex>> vertex_queue; // weight / vertex
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
	std::list<Vertex> path;
	int vertex = dst;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}

void MST::display(){
	int sum = 0;
	for(auto node : nodes){
		// unpack the tuple
		int src = std::get<0>(node);
		int dst = std::get<1>(node);
		int cost = std::get<2>(node);

		// display each edge to the user
		std::cout << src << " -> " << dst
		          << "  (Cost: " << cost << ")\n";

		sum += cost;
	}
	// display the total cost of the MST to the user
	std::cout << "Total cost: " << sum << std::endl;
}

void MST::addEdge(int src, int dst, int cost){
	// pack the tuple and push back onto the MST
	nodes.push_back(std::make_tuple(src, dst, cost));
}


MST Graph::primsAlgo(){
	MST mst;// Minimum spanning tree to store edges
    std::vector<bool> visited = std::vector<bool>(nVertices, false);

    //Start at 0th vertex and loop until we've visited all nodes
    visited.at(0) = true;
    while(std::count(visited.begin(),
    	             visited.end(),
    	             true) < nVertices){
        int x = 0, y = 0;
        int min = INT_MAX; // seed min so that edge costs will be smaller

        for(int i = 0; i < nVertices; ++i){
            if(visited.at(i) == false) continue;
            for(int j = 0; j < nVertices; ++j){
            	if(visited.at(j) == false && edgeMatrix.at(i).at(j).exists){	
	                int cost = this->getEdgeValue(i, j);
	                if(min > cost){
	                    min = cost;
	                    x = i;
	                    y = j;
	                }
            	}
            }
        }

        // Set visited and add to MST (+1 so stdout printout counts from 1)
        visited.at(y) = true;
        mst.addEdge(x+1, y+1, min);
    }
    std::cout << std::endl;

    return mst;
}

int MST::size(){
	return nodes.size();
}

std::vector<std::tuple<int, int, int>> MST::getNodes(){
	return nodes;
}

