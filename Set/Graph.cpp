#include "Graph.h"
#include "Edge.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

void Graph::fillSet(){

    ifstream file("../data/file2.txt");

    if(!file) {
        cout << "Error while opening the file"<<endl;
        exit(0);
    }

    int a,b;

    while(file >> a >> b){
        Edge e(a,b);

        edges.insert(e);

        set<int>::iterator it = vertexes.find(a);

        if(it == vertexes.end())
            vertexes.insert(a);

        it = vertexes.find(b);

        if(it == vertexes.end())
            vertexes.insert(b);

        // sort(vertices.begin(), vertices.end());
    }

    file.close();

    Edge ee(6,7);
    // if(checkIfEdgeExistsInGraph(ee)) cout<<"istnieje";
    // else cout <<"nie istnieje";

}

void Graph::print(){
    cout<<endl<<"Graph: "<<endl<<endl;
    for(set<Edge>::iterator it = edges.begin(); it != edges.end(); it++)
        cout << it->toString();
    cout<<endl;
}

bool Graph::checkIfGraphConnected(set<Edge> &ed, int x){

    bool *visited = new bool[vertexes.size()];
    stack<int>stack;
	int vc = 0;

    for (int i = 0; i < vertexes.size(); i++) visited[i] = false;

    stack.push(0);
    visited[0] = true;
    
    while (!stack.empty()) {
		int v = stack.top();
		stack.pop();
		vc++;
        
        for(auto e : ed){
            if(e.getA() == v && !visited[e.getB()]){
                visited[e.getB()] = true;
                stack.push(e.getB());
            } else if(e.getB() == v && !visited[e.getA()]){
                visited[e.getA()] = true;
                stack.push(e.getA());
            }
        }

	}
	
	delete [] visited;

    return (vc == vertexes.size()-x) ? true : false;

}

bool Graph::checkIfEdgeExistsInGraph(Edge e){
    // return (edges.find(Edge(e.getA(), e.getB())) != edges.end()) ? true : false;
    return (find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end()) ? true : false;
}