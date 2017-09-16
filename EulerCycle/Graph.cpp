#include "Graph.h"
#include "Edge.h"
#include "Concepts.cpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>

template<typename T, typename U>
Graph<T,U>::Graph() {}

template<typename T, typename U>
Graph<T,U>::~Graph() {}

template<typename T, Sequence U>
void sortVertices() {
    sort(vertices2.begin(), vertices2.end());
}

template<typename T, Associative_container U>
void sortVertices() {
    
}

template<typename T, typename U>
void Graph<T,U>::fill() {

    ifstream file("../data/file3.txt");

    if(!file){
        cout << "Error input file" << endl;
		exit(0);
    }

    int a,b;

    while(file >> a >> b){
        
        Edge e(a,b);

        edges.push_back(e);

        typename U::iterator it = find(vertices.begin(), vertices.end(), a);
        if(it == vertices.end()) vertices.push_back(a);

        it = find(vertices.begin(), vertices.end(), b);
        if(it == vertices.end()) vertices.push_back(b);

    }

    // sortVertices<T,U>();

    file.close();

}



template<typename T, typename U>
void Graph<T,U>::print() { 
    cout<<endl;
    for(typename T::iterator it = edges.begin(); it != edges.end(); it++)
        cout<<it->toString();
    cout<<endl;
}

template<typename T, typename U>
bool Graph<T,U>::checkIfGraphConnected(T &ed, int x, int startVertice) {

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

        for(typename T::iterator it = ed.begin(); it != ed.end(); it++){
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

template<Associative_container T, typename U>
bool Graph<T,U>::checkIfEdgeExistsInGraph(Edge e){
    return (find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end());
}

template<typename T, typename U>
int Graph<T,U>::getEdgeIndex(Edge e){
    return distance(edges.begin(), find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())));
}

template<typename T, typename U>
bool Graph<T,U>::checkIfAllEdgesEvenDegree(){
    int counter = 0, i = 0;
    for(auto v : vertices){
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) counter++;
        }
        if(counter % 2 == 0) i++;
    }
    return (i == vertices.size()) ? true : false;
}

template<typename T, typename U>
int Graph<T,U>::getNeighboursCount(int v){
    int l = 0;
    for(auto e : edges)
        if(e.getA() == v || e.getB() == v)
            l++;
    return l;
}

template<typename T, typename U>
bool Graph<T,U>::checkIfStillConnected(Edge e, int x, int startVertice){
    
    T tmp;

    for(auto e : edges)
        tmp.push_back(e);

    for(typename T::iterator it = tmp.begin(); it != tmp.end(); it++)
		if (it->getA() == e.getA() && it->getB() == e.getB()) {
			tmp.erase(it);
			it = prev(tmp.end());
        }
        
    return checkIfGraphConnected(tmp, x, startVertice);
}

template<typename T, typename U>
int Graph<T,U>::getZeroDegreeCount(){
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

template<typename T, typename U>
void Graph<T,U>::removeEdgeWithOneNeighbour(int &v){
    
    typename T::iterator it = find(edges.begin(), edges.end(), v);
    
    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    edges.erase(it);
}

template<typename T, typename U>
void Graph<T,U>::removeEdgeWithMoreNeighbour(int &v){
    for(typename T::iterator i = edges.begin(); i != edges.end(); i++){
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

template<typename T, typename U>
void Graph<T,U>::determineEulerCycle(){
    
    int v = 3;
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