#ifndef Graph_H
#define Graph_H

#include "Edge.h"
#include <vector>
#include <stack>

using namespace std;

class Graph
{
public:
	Graph();
	~Graph();
	

private:
	vector<Edge> edges;
	vector<int> vertexes;

};

#endif // !Graph_H