#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
#include "Edge.h"
#include <vector>
#include <list>

using namespace std;

int main() {

    Graph<list<Edge>, vector<int>> g;
    g.fill();
    g.print();
    g.determineEulerCycle();

    return 0;
}