#include "Graph.h"
#include "Edge.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

void Graph::fillSet(){

    ifstream file("../data/file3.txt");

    if(!file) {
        cout << "Error while opening the file"<<endl;
        exit(0);
    }

    int a,b;

    while(file >> a >> b){
        Edge e(a,b);

        edges.insert(e);

        set<int>::iterator it = vertices.find(a);

        if(it == vertices.end())
            vertices.insert(a);

        it = vertices.find(b);

        if(it == vertices.end())
            vertices.insert(b);

    }

    file.close();

}

void Graph::print(){
    cout<<endl<<"Graph: "<<endl<<endl;
    for(set<Edge>::reverse_iterator it = edges.rbegin(); it != edges.rend(); it++)
        cout << it->toString();
    cout<<endl;
}

bool Graph::checkIfGraphConnected(set<Edge> &ed, int x, int startVertice) {
    
    bool *visited = new bool[vertices.size()];
    for (int i = 0; i < vertices.size(); i++) visited[i] = false;

    stack<int>stack;
    int vc = 0;
    
    stack.push(startVertice);
    visited[startVertice] = true;
    
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        vc++;

        for(set<Edge>::iterator it = ed.begin(); it != ed.end(); it++){
            if(it->getA() == v && !visited[it->getB()]){
                visited[it->getB()] = true;
                stack.push(it->getB());
            } else if(it->getB() == v && !visited[it->getA()]){
                visited[it->getA()] = true;
                stack.push(it->getA());
            }
        }

    }

    delete [] visited;

    return (vc == vertices.size()-x);

}

bool Graph::checkIfEdgeExistsInGraph(Edge e){
    return (find_if(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end());
}

int Graph::getEdgeIndex(Edge e){
    return distance(edges.begin(), find_if(edges.begin(), edges.end(), Edge(e.getA(), e.getB())));
}

bool Graph::checkIfAllEdgesEvenDegree(){
    int counter = 0, i = 0;
    for(auto v : vertices){
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) counter++;
        }
        if(counter % 2 == 0) i++;
    }
    return (i == vertices.size());
}

int Graph::getNeighboursCount(int v){
    int l = 0;
    for(auto e : edges)
        if(e.getA() == v || e.getB() == v)
            l++;
    return l;
}

bool Graph::checkIfStillConnected(Edge e, int x, int startVertice){
    
    set<Edge> tmp;

    for(auto e : edges)
        tmp.insert(e);

    for(set<Edge>::iterator it = tmp.begin(); it != tmp.end(); it++)
		if (it->getA() == e.getA() && it->getB() == e.getB()) {
			tmp.erase(it);
			it = prev(tmp.end());
        }
        
    return checkIfGraphConnected(tmp, x, startVertice);
}

int Graph::getZeroDegreeCount(){
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

findByAOrB::findByAOrB(int value) : value(value){}

bool findByAOrB::operator()(Edge edge) {
	return (edge.getA() == value || edge.getB() == value);
}

void Graph::removeEdgeWithOneNeighbour(int &v){
    
    set<Edge>::iterator it = find_if(edges.begin(), edges.end(), findByAOrB(v));
    
    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    edges.erase(it);
}

void Graph::removeEdgeWithMoreNeighbour(int &v){
    for(set<Edge>::iterator i = edges.begin(); i != edges.end(); i++){
        if(i->getA() == v && checkIfStillConnected(*i, getZeroDegreeCount(), v)){
            v = i->getB();
            edges.erase(i);
            i = prev(edges.end());
        } else if(i->getB() == v && checkIfStillConnected(*i, getZeroDegreeCount(), v)){
            v = i->getA();
            edges.erase(i);
            i = prev(edges.end());
        }
    }
}

void Graph::determineEulerCycle(){
    
    int v = 1;
    bool condition = (checkIfGraphConnected(edges, 0, v) && checkIfAllEdgesEvenDegree());

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
        if(!checkIfGraphConnected(edges, 0, v))
            cout <<"Graph is not connected"<<endl;
        else if(!checkIfAllEdgesEvenDegree())
            cout <<"Not all the edges are even"<<endl;
    }
    
}