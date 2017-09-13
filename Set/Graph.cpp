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

bool Graph::checkIfGraphConnected(set<Edge> &ed, int x){

    bool *visited = new bool[vertices.size()];
    stack<int>stack;
	int vc = 0;

    for (int i = 0; i < vertices.size(); i++) visited[i] = false;

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

    return (vc == vertices.size()-x) ? true : false;

}

bool Graph::checkIfEdgeExistsInGraph(Edge e){
    return (find_if(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end()) ? true : false;
}

int Graph::getEdgeIndex(Edge e){
    return distance(edges.begin(), (find_if(edges.begin(), edges.end(), Edge(e.getA(), e.getB()))));
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

    set<Edge> tmp;
    
    for(auto e : edges)
        tmp.insert(e);

    for(auto t : tmp){
        if(t.getA() == e.getA() && t.getB() == e.getB()){
            tmp.erase(t);
        }
    }

    return checkIfGraphConnected(tmp, x) ? true : false;

}

findByAOrB::findByAOrB(int value) : value(value){}

bool findByAOrB::operator()(Edge edge) {
	return (edge.getA() == value || edge.getB() == value);
}

void Graph::printEulerCycle(){
    cout << endl << "Euler cycle: " <<endl;
    
    cout << endl;
}

void Graph::determineEulerCycle(){

    bool condition = (checkIfGraphConnected(edges, 0) && checkIfAllEdgesEvenDegree());
    int zeroDegreeVertex = 0, l = 0, v = 3;

    if(condition){

        cout << "Euler cycle:" << endl << endl << v;

        while(!edges.empty()){
            l = 0;
            zeroDegreeVertex = 0;
            for(auto v : vertices){
                l = 0;
                for(auto e : edges){
                    if(e.getA() == v || e.getB() == v) l++;
                }
                if(l == 0) zeroDegreeVertex++;
            }

            switch(getNeighboursCount(v)){
                case 1 : {
                    
                    set<Edge>::iterator it = find_if(edges.begin(), edges.end(), findByAOrB(v));
                    
                    if(it->getA() == v) v = it->getB();
                    else v = it->getA();

                    edges.erase(it);

                    break;
                }
                default: {

                    for(set<Edge>::iterator it = edges.begin(); it != edges.end(); it++){
                        if(it->getA() == v && checkIfStillConnected(*it, zeroDegreeVertex)){
                            v = it->getB();
                            edges.erase(it);
                        }
                        else if(it->getB() == v && checkIfStillConnected(*it, zeroDegreeVertex)){
                            v = it->getA();
                            edges.erase(it);
                        }
                    }
                   
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

}