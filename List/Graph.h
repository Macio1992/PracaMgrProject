#ifndef Graph_H
#define Graph_H

#include "Edge.h"
#include <list>

using namespace std;

class Graph
{
    public:
	    Graph();
        ~Graph();
        void fill();
        void print();
        bool checkIfGraphConnected(list<Edge>&, int);
        bool checkIfEdgeExistsInGraph(Edge);
        int getEdgeIndex(Edge);
        bool checkIfAllEdgesEvenDegree();
        int getNeighboursCount(int);
        bool checkIfStillConnected(Edge, int);
        void determineEulerCycle();
        int getZeroDegreeCount(int);
    
    private:
        list<Edge> edges;
        list<int> vertices;

};

#endif // !Graph_H