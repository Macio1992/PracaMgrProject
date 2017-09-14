#include <iostream>
#include <string>
#include "Graph.h"


using namespace std;

int main (){

    Graph g;
    g.fillVector();
    g.print();
    g.determineEulerCycle();

    return 0;
}