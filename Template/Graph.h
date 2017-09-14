#ifndef Graph_H
#define Graph_H

#include <iostream>
#include "Edge.h"

using namespace std;

template<typename T, typename U>
class Graph{

    public:
        Graph();
        ~Graph();
        void fill();
        void print();
        bool checkIfGraphConnected(T&, int);
        bool checkIfEdgeExistsInGraph(Edge);
        int getEdgeIndex(Edge);
        bool checkIfAllEdgesEvenDegree();
        int getNeighboursCount(int);
        bool checkIfStillConnected(Edge, int);
        int getZeroDegreeCount(int);
        void removeEdgeWithOneNeighbour(int&);
        void removeEdgeWithMoreNeighbour(int&);
        void determineEulerCycle();

    private:
        T edges;
        U vertices;

};

#endif