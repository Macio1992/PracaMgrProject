#include <iostream>
#include <vector>
#include <set>

#include "Edge.h"
// #include "Edge.cpp"

#include "Operations.cpp"

int main () {

    // vector<Edge> edges;
    // vector<int> vertices;

    // fill(edges, vertices);
    // determineEulerCycle(edges, vertices);

    set<Edge> edgesS;
    set<int> verticesS;

    fill(edgesS, verticesS);
    determineEulerCycle(edgesS, verticesS);

    return 0;
}