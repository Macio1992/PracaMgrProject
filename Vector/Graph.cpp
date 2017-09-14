#include "Graph.h"
#include "Edge.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

void Graph::fillVector(){

    ifstream file("../data/file3.txt");

    if(!file) {
        cout << "Error while opening the file"<<endl;
        exit(0);
    }

    int a,b;

    while(file >> a >> b){
        Edge e(a,b);

        edges.push_back(e);

        vector<int>::iterator it = find(vertices.begin(), vertices.end(), a);

        if(it == vertices.end())
            vertices.push_back(a);

        it = find(vertices.begin(), vertices.end(), b);

        if(it == vertices.end())
            vertices.push_back(b);

        sort(vertices.begin(), vertices.end());
    }

    file.close();
}

void Graph::print(){

    cout<<endl<<"Graph: "<<endl<<endl;
    for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
        cout <<it->toString();
    cout<<endl;
}

bool Graph::checkIfGraphConnected(vector<Edge> &ed, int x){

    bool *visited = new bool[vertices.size()];
	for (int i = 0; i < vertices.size(); i++) visited[i] = false;
	stack<int>stack;
	int vc = 0;

	stack.push(0);
	visited[0] = true;

	while (!stack.empty()) {
		int v = stack.top();
		stack.pop();
		vc++;
		for (int u = 0; u < ed.size(); u++) {
			
			if (ed[u].getA() == v) {
				if (!visited[ed[u].getB()]){
					visited[ed[u].getB()] = true;
					stack.push(ed[u].getB());
				}
			} else if (ed[u].getB() == v) {
				if (!visited[ed[u].getA()]){
					visited[ed[u].getA()] = true;
					stack.push(ed[u].getA());
				}
			}
		}

	}
	
	delete [] visited;

    return (vc == vertices.size()-x) ? true : false;

}

bool Graph::checkIfEdgeExistsInGraph(Edge e){
    return (find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end()) ? true : false;
}

int Graph::getEdgeIndex(Edge e){
    return distance(edges.begin(), find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())));
}

bool Graph::checkIfAllEdgesEvenDegree(){

    int counter = 0, i = 0;

    for(auto v : vertices){
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) counter++;
        }
        if(counter % 2 == 0) i++;
    }

    return (i == vertices.size()) ? true : false;

}

int Graph::getNeighboursCount(int v){
    
    int l = 0;

    for(auto e : edges)
        if(e.getA() == v || e.getB() == v)
            l++;

    return l;

}

bool Graph::checkIfStillConnected(Edge e, int x){
    
    vector<Edge> tmp;

    for(auto e : edges)
        tmp.push_back(e);

    for(int i = 0; i < tmp.size(); i++)
		if (tmp[i].getA() == e.getA() && tmp[i].getB() == e.getB()) {
			tmp.erase(tmp.begin() + i);
			i = tmp.size();
        }
    
    return checkIfGraphConnected(tmp, x) ? true : false;
}

int Graph::getZeroDegreeCount(int v){
    int l = 0;
    int zeroDegreeVertex = 0;
    for(auto v : vertices){
        l = 0;
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) l++;
        }
        if(l == 0) zeroDegreeVertex++;
    }

    return zeroDegreeVertex;
}

void Graph::removeEdgeWithOneNeighbour(int &v){

    vector<Edge>::iterator it = find(edges.begin(), edges.end(), v);
    
    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    edges.erase(it);
}

void Graph::removeEdgeWithMoreNeighbour(int &v){
    for(vector<Edge>::iterator i = edges.begin(); i != edges.end(); i++){
        if(i->getA() == v){
            
            if(checkIfStillConnected(*i, getZeroDegreeCount(v))){
                cout<<"A"<<endl;
                v = i->getB();
                edges.erase(i);
                i = prev(edges.end());
            }
        } else if(i->getB() == v){
            
            if(checkIfStillConnected(*i, getZeroDegreeCount(v))){
                cout<<"B"<<endl;
                v = i->getA();
                edges.erase(i);
                i = prev(edges.end());
            }
        }
    }
}

void Graph::determineEulerCycle(){

    bool condition = (checkIfGraphConnected(edges, 0) && checkIfAllEdgesEvenDegree());
    int v = 1;

    print();
    cout<<"1. v = "<<v<<endl;
    cout<<"1. z = "<<getZeroDegreeCount(v)<<endl;
    cout<<"1. n = "<<getNeighboursCount(v)<<endl;

    removeEdgeWithMoreNeighbour(v);

    print();

    cout<<"2. v = "<<v<<endl;
    cout<<"2. z = "<<getZeroDegreeCount(v)<<endl;
    cout<<"2. n = "<<getNeighboursCount(v)<<endl;

    removeEdgeWithOneNeighbour(v);

    print();

    cout<<"3. v = "<<v<<endl;
    cout<<"3. z = "<<getZeroDegreeCount(v)<<endl;
    cout<<"3. n = "<<getNeighboursCount(v)<<endl;

    removeEdgeWithMoreNeighbour(v);


    /*
    if(condition){
        cout << "Euler cycle:" << endl << endl << v;

        while(!edges.empty()){
            
            switch(getNeighboursCount(v)){
                case 1 : {
                    removeEdgeWithOneNeighbour(v);
                    break;
                }
                default: {
                    removeEdgeWithMoreNeighbour(v);
                    break;
                }
            }
            cout <<" -> "<<v;
        }
        cout << endl << endl;
    } else {
        cout<<"Invalid graph."<<endl;
        if(!checkIfGraphConnected(edges, 0))
            cout <<"Graph is not connected"<<endl;
        else if(!checkIfAllEdgesEvenDegree())
            cout <<"Not all the edges are even"<<endl;
    }
    */
}