#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <algorithm>
#include <stack>

// #include "Graph.h"
// #include "Graph.cpp"
#include "Edge.h"
#include "Edge.cpp"

#include "Concepts.hpp"

using namespace std;

struct findByAOrB {
    findByAOrB(int);
    bool operator()(const Edge) const;
    private:
        int value;
};

findByAOrB::findByAOrB(int value) : value(value){}

bool findByAOrB::operator()(const Edge edge) const {
	return (edge.getA() == value || edge.getB() == value);
}

template<Sequence S>
void sort(S &seq);

template<Associative_container A>
void sort(A &seq);

template<Sequence S, typename V>
void readData(ifstream&, S&, V&);

template<Associative_container A, typename V>
void readData(ifstream&, A&, V&);

template<typename E, typename V>
void fill(E &edges, V &vertices);

template<typename E>
void print(E &edges);

template<typename E, typename V>
bool checkIfGraphConnected(E &edges, V &vertices, int x, int startVertice);

template<Sequence S>
bool checkIfEdgeExistsInGraph(S&, Edge);

template<Associative_container A>
bool checkIfEdgeExistsInGraph(A&, Edge);

template<typename E>
int getEdgeIndex(E&, Edge);

template<typename E, typename V>
bool checkIfAllEdgesEvenDegree(E&, V&);

template<typename E>
int getNeighboursCount(E&, int);

template<Sequence E, typename V>
bool checkIfStillConnected(E&, Edge, int, int, V&);

template<Associative_container E, typename V>
bool checkIfStillConnected(E&, Edge, int, int, V&);

template<typename E, typename V>
int getZeroDegreeCount(E&, V&);

template<Sequence Seq>
void removeEdgeWithOneNeighbour(Seq&, int&);

template<Associative_container A>
void removeEdgeWithOneNeighbour(A&, int&);

template<typename E, typename V>
void removeEdgeWithMoreNeighbour(E&, int&, V&);

template<typename E, typename V>
void determineEulerCycle(E&, V&);

int main () {

    set<Edge> edgesSet;
    set<int> verticesSet;

    fill(edgesSet, verticesSet);
    print(edgesSet);
    determineEulerCycle(edgesSet, verticesSet);

    // vector<Edge> edgesVector;
    // vector<int> verticesVector;
    // fill(edgesVector, verticesVector);
    // print(edgesVector);
    // determineEulerCycle(edgesVector, verticesVector);

    return 0;
}

template<Sequence S>
void sort(S &seq){
    sort(seq.begin(), seq.end());
}

template<Associative_container A>
void sort(A &seq){}

template<Sequence S, typename V>
void readData(ifstream& file, S& seq, V& vertices){

    int a, b;
    while(file >> a >> b){
        
        Edge e(a,b);

        seq.push_back(e);

        typename V::iterator it = find(vertices.begin(), vertices.end(), a);
        if(it == vertices.end()) vertices.push_back(a);

        it = find(vertices.begin(), vertices.end(), b);
        if(it == vertices.end()) vertices.push_back(b);

    }

}

template<Associative_container A, typename V>
void readData(ifstream& file, A& seq, V& vertices){

    int a, b;
    while(file >> a >> b){
        
        Edge e(a,b);

        seq.insert(e);

        typename V::iterator it = find(vertices.begin(), vertices.end(), a);
        if(it == vertices.end()) vertices.insert(a);

        it = find(vertices.begin(), vertices.end(), b);
        if(it == vertices.end()) vertices.insert(b);

    }

}

template<typename E, typename V>
void fill(E &edges, V &vertices) {
    
    ifstream file("../data/file3.txt");

    if(!file){
        cout << "Error input file" << endl;
        exit(0);
    }

    readData(file, edges, vertices);

    sort<V>(vertices);

    file.close();

}

template<typename E>
void print(E &edges){
    cout<<endl;
    for(typename E::iterator it = edges.begin(); it != edges.end(); it++)
        cout<<it->toString();
    cout<<endl;
}

template<typename E, typename V>
bool checkIfGraphConnected(E &ed, V &vertices, int x, int startVertice) {
    
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

        for(typename E::iterator it = ed.begin(); it != ed.end(); it++){
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

template<Sequence S>
bool checkIfEdgeExistsInGraph(S &edges, Edge e){
    return (find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end());
}

template<Associative_container A>
bool checkIfEdgeExistsInGraph(A &edges, Edge e){
    return (find_if(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end());
}

template<typename E>
int getEdgeIndex(E &edges, Edge e){
    return distance(edges.begin(), find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())));
}

template<typename E, typename V>
bool checkIfAllEdgesEvenDegree(E &edges, V &vertices){
    int counter = 0, i = 0;
    for(auto v : vertices){
        for(auto e : edges){
            if(e.getA() == v || e.getB() == v) counter++;
        }
        if(counter % 2 == 0) i++;
    }
    return (i == vertices.size()) ? true : false;
}

template<typename E>
int getNeighboursCount(E &edges, int v){
    int l = 0;
    for(auto e : edges)
        if(e.getA() == v || e.getB() == v)
            l++;
    return l;
}

template<Sequence E, typename V>
bool checkIfStillConnected(E &edges, Edge e, int x, int startVertice, V &vertices){
    
    E tmp;

    for(auto e : edges)
        tmp.push_back(e);

    for(typename E::iterator it = tmp.begin(); it != tmp.end(); it++)
		if (it->getA() == e.getA() && it->getB() == e.getB()) {
			tmp.erase(it);
			it = prev(tmp.end());
        }
        
    return checkIfGraphConnected(tmp, vertices, x, startVertice);
}

template<Associative_container E, typename V>
bool checkIfStillConnected(E &edges, Edge e, int x, int startVertice, V &vertices){
    
    E tmp;

    for(auto e : edges)
        tmp.insert(e);

    for(typename E::iterator it = tmp.begin(); it != tmp.end(); it++)
		if (it->getA() == e.getA() && it->getB() == e.getB()) {
			tmp.erase(it);
			it = prev(tmp.end());
        }
        
    return checkIfGraphConnected(tmp, vertices, x, startVertice);
}

template<typename E, typename V>
int getZeroDegreeCount(E &edges, V &vertices){

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

template<Sequence S>
void removeEdgeWithOneNeighbour(S &edges, int &v){
    
    typename S::iterator it = find(edges.begin(), edges.end(), v);
    
    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    edges.erase(it);
}

template<Associative_container A>
void removeEdgeWithOneNeighbour(A &edges, int &v){
    
    typename A::iterator it = find(edges.begin(), edges.end(), findByAOrB(v));
    
    if(it->getA() == v) v = it->getB();
    else v = it->getA();

    edges.erase(it);
}

template<typename E, typename V>
void removeEdgeWithMoreNeighbour(E &edges, int &v, V &vertices){
    for(typename E::iterator i = edges.begin(); i != edges.end(); i++){
        if(i->getA() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getB();
            edges.erase(i);
            i = prev(edges.end());
        } else if(i->getB() == v && checkIfStillConnected(edges, *i, getZeroDegreeCount(edges, vertices), v, vertices)){
            v = i->getA();
            edges.erase(i);
            i = prev(edges.end());
        }
    }
}

template<typename E, typename V>
void determineEulerCycle(E &edges, V &vertices){

    int v = 0;

    bool condition = (checkIfGraphConnected(edges, vertices, 0, v) && checkIfAllEdgesEvenDegree(edges, vertices));
    
        if(condition){
            cout << "Euler cycle:" << endl << endl << v;
            while(!edges.empty()){
                switch(getNeighboursCount(edges, v)){
                    case 1 : {
                        removeEdgeWithOneNeighbour(edges, v);
                        break;
                    }
                    default: {
                        removeEdgeWithMoreNeighbour(edges, v, vertices);
                        break;
                    }
                }
                cout <<" -> "<<v;
            }
            cout << endl << endl;
        } else {
            cout<<"Invalid graph."<<endl;
            if(!checkIfGraphConnected(edges, vertices, 0, v))
                cout <<"Graph is not connected"<<endl;
            else if(!checkIfAllEdgesEvenDegree(edges, vertices))
                cout <<"Not all the edges are even"<<endl;
        }

}