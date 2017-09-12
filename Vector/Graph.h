#ifndef Graph_H
#define Graph_H

#include "Edge.h"
#include <vector>

using namespace std;

class Graph
{
    public:
        Graph();
        ~Graph();
        void fillVector();
        void print();
        bool checkIfGraphConnected(vector<Edge>&, int);
        bool checkIfEdgeExistsInGraph(Edge);
        int getEdgeIndex(Edge);
        bool checkIfAllEdgesEvenDegree();
        int getNeighboursCount(int);
        bool checkIfStillConnected(Edge, int);
        void determineEulerCycle();

    private:
        vector<Edge> edges;
        vector<int> vertices;

};

#endif