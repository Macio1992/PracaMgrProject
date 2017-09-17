#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <forward_list>

#include "Edge.h"
// #include "Edge.cpp"

#include "Operations.cpp"

int main () {

    // vector<Edge> edges;
    // vector<int> vertices;

    // fill(edges, vertices);
    // determineEulerCycle(edges, vertices);

    // set<Edge> edgesS;
    // set<int> verticesS;

    // fill(edgesS, verticesS);
    // determineEulerCycle(edgesS, verticesS);

    vector<Edge> edges;
    vector<int> vertices;

    // int f = 0;
    fill(edges, vertices);
    determineEulerCycle(edges, vertices);

    set<Edge> edgesS;
    set<int> verticesS;

    determineEulerCycle(edgesS, vertices);

    list<Edge> edgesL;
    list<int> verticesL;

    determineEulerCycle(edgesL, verticesL);

    forward_list<Edge> edgesA;
    forward_list<int> verticesA;

    sortVertices<forward_list<int>, typename forward_list<int>::iterator>(verticesA);

    return 0;
}