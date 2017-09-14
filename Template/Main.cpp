#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
#include "Edge.h"
#include <vector>

using namespace std;

int main() {

    Graph<vector<Edge>, vector<int>> g;
    g.fill();
    g.print();
    g.determineEulerCycle();

    return 0;
}