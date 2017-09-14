#include "Graph.h"
#include "Edge.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

void Graph::fill(){
    
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
    stack<int>stack;
    int vc = 0;

    stack.push(0);
    visited[0] = true;

    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        vc++;

        for(auto e : edges){
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
    return (find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end());
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
            tmp.erase(i++);
            i = prev(tmp.end());
        }
    }

    cout<<"x: "<<x<<endl;

    cout<<"tmp:"<<endl;
    for(auto t : tmp)
        cout<<t.toString();
    
    return checkIfGraphConnected(tmp, x) ? true : false;
}

int Graph::getZeroDegreeCount(int v){
    int l = 0, zeroDegreeVertex = 0;
    for(auto v : vertices){
        l = 0;
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) l++;
        }
        if(l == 0) zeroDegreeVertex++;
    }
    return zeroDegreeVertex;
}

void Graph::determineEulerCycle(){

    bool condition = (checkIfGraphConnected(edges, 0) && checkIfAllEdgesEvenDegree());
    // int zeroDegreeVertex = 0, l = 0, v = 0;
    int v = 0;

    print();
    //---1---
    cout<<"1. v = "<<v<<endl;
    cout<<"1. n = "<<getNeighboursCount(v)<<endl;
    cout<<"1. z = "<<getZeroDegreeCount(v)<<endl;

    list<Edge>::iterator it = edges.begin();

    for(list<Edge>::iterator it = edges.begin(); it != edges.end(); it++){
        if(it->getA() == v && checkIfStillConnected(*it, getZeroDegreeCount(v))){
            v = it->getB();
            edges.erase(it++);
            it = prev(edges.end());
        } else if(it->getB() == v && checkIfStillConnected(*it, getZeroDegreeCount(v))){
            v = it->getA();
            edges.erase(it++);
            it = prev(edges.end());
        }
    }

    print();

    //---2---
    cout<<"2. v = "<<v<<endl;
    cout<<"2. n = "<<getNeighboursCount(v)<<endl;
    cout<<"2. z = "<<getZeroDegreeCount(v)<<endl;

    it = find(edges.begin(), edges.end(), v);

    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    edges.erase(it++);

    print();

    //---3---
    cout<<"3. v = "<<v<<endl;
    cout<<"3. n = "<<getNeighboursCount(v)<<endl;
    cout<<"3. z = "<<getZeroDegreeCount(v)<<endl;

    it = edges.begin();
    cout<<"beg: "<<it->toString();

    if(checkIfStillConnected(*it, getZeroDegreeCount(v))) cout<<"dalej spojny"<<endl;
    else cout<<"niespojny"<<endl;

    /*
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
                    
                    list<Edge>::iterator it = find(edges.begin(), edges.end(), v);

                    if(it->getA() == v) v = it->getB();
                    else v = it->getA();

                    edges.erase(it++);

                    break;
                }
                default: {
                    cout<<"edges.size: "<<edges.size()<<endl;
                    for(list<Edge>::iterator it = edges.begin(); it != edges.end(); it++){
                        if(it->getA() == v && checkIfStillConnected(*it, zeroDegreeVertex)){
                            v = it->getB();
                            edges.erase(it++);
                            it = prev(edges.end());
                        } else if(it->getB() == v && checkIfStillConnected(*it, zeroDegreeVertex)){
                            v = it->getA();
                            edges.erase(it++);
                            it = prev(edges.end());
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
    */
}