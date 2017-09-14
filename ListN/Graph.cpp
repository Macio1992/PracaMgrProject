#include "Graph.h"
#include "Edge.h"

#include <iostream>
#include <fstream>
#include <list>
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

        list<int>::iterator it = find(vertices.begin(), vertices.end(), a);

        if(it == vertices.end())
            vertices.push_back(a);

        it = find(vertices.begin(), vertices.end(), b);

        if(it == vertices.end())
            vertices.push_back(b);

        vertices.sort();
    }

    file.close();

}

void Graph::print(){
    cout<<endl<<"Graph: "<<endl<<endl;
    for(list<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
        cout <<it->toString();
    cout<<endl;
}

bool Graph::checkIfGraphConnected(list<Edge> &ed, int x){
    
    bool *visited = new bool[vertices.size()];
    for (int i = 0; i < vertices.size(); i++) visited[i] = false;
    stack<int> stack;
    int vc = 0;

    stack.push(0);
    visited[0] = true;

    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        vc++;
        for (auto e : edges) {
            if (e.getA() == v) {
                if (!visited[e.getB()]){
                    visited[e.getB()] = true;
                    stack.push(e.getB());
                }
            } else if (e.getB() == v) {
                if (!visited[e.getA()]){
                    visited[e.getA()] = true;
                    stack.push(e.getA());
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
    
    list<Edge> tmp;

    for(auto e : edges)
        tmp.push_back(e);

    for(list<Edge>::iterator i = tmp.begin(); i != tmp.end(); i++){
        if(i->getA() == e.getA() && i->getB() == e.getB()){
            i = tmp.erase(i);
            i = prev(tmp.end());
        }
    }
    
    return checkIfGraphConnected(tmp, x) ? true : false;
}

void Graph::determineEulerCycle(){
    
    bool condition = (checkIfGraphConnected(edges, 0) && checkIfAllEdgesEvenDegree());
    int zeroDegreeVertex = 0, l = 0, v = 0;

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
                    
                    auto it = find(edges.begin(), edges.end(), v);

                    if(it->getA() == v) v = it->getB();
                    else v = it->getA();

                    it = edges.erase(it);

                    break;
                }
                default: {


                    for(list<Edge>::iterator i = edges.begin(); i != edges.end(); i++){
                        if(i->getA() == v){
                            if(checkIfStillConnected(*i, zeroDegreeVertex)){
                                v = i->getB();
                                i = edges.erase(i);
                                i = prev(edges.end());
                            }
                        } else if(i->getB() == v){
                            if(checkIfStillConnected(*i, zeroDegreeVertex)){
                                v = i->getA();
                                i = edges.erase(i);
                                i = prev(edges.end());
                            }
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