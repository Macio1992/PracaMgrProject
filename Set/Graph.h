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
    bool checkIfGraphConnected(set<Edge>&, int, int);
    bool checkIfEdgeExistsInGraph(Edge);
    int getEdgeIndex(Edge);
    bool checkIfAllEdgesEvenDegree();
    int getNeighboursCount(int);
    bool checkIfStillConnected(Edge, int, int);
    int getZeroDegreeCount();
    void removeEdgeWithOneNeighbour(int&);
    void removeEdgeWithMoreNeighbour(int&);
    void determineEulerCycle();

private:
	set<Edge> edges;
    set<int> vertices;
    int value;
    
};

struct findByAOrB {
    findByAOrB(int);
    bool operator()(Edge);
    private:
        int value;
};

#endif // !Graph_H