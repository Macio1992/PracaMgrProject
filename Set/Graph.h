#ifndef Graph_H
#define Graph_H

#include "Edge.h"
#include <set>

using namespace std;

class Graph
{
public:
	Graph();
    ~Graph();
    void fillSet();
    void print();
    bool checkIfGraphConnected(set<Edge>&, int);
    bool checkIfEdgeExistsInGraph(Edge);

private:
	set<Edge> edges;
	set<int> vertexes;
};

#endif // !Graph_H