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
    int getEdgeIndex(Edge);
    bool checkIfAllEdgesEvenDegree();
    int getNeighboursCount(int v);
    bool checkIfStillConnected(Edge e, int x);
    void printEulerCycle();
    void determineEulerCycle();

private:
	set<Edge> edges;
    set<int> vertices;
    
};

struct findByAOrB {
    findByAOrB(int);
    bool operator()(Edge);
    private:
        int value;
};

#endif // !Graph_H