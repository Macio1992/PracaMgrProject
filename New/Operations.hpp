// #include "Operations.cpp"
// #include "Operations.h"
#include "Concepts.hpp"
#include "Edge.h"
// #include "Edge.cpp"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <stack>
#include <set>

using namespace std;

struct findByAOrB {
    findByAOrB(int) : value(value){}
    bool operator()(Edge edge){
        return (edge.getA() == value || edge.getB() == value);
    }
    private:
        int value;
};

template<Sequence S, Random_access_iterator R>
void sortVertices(S &seq){
    // sort(seq.begin(), seq.end());
}

template<Sequence S, Bidirectional_iterator R>
void sortVertices(S &seq){
    // seq.sort();
}

template<Sequence S, Forward_iterator R>
void sortVertices(S &seq){
    // seq.sort();
}

template<Associative_container A>
void sortVertices(A &seq){}

template<Sequence S, Sequence V>
void readData(ifstream &file, S &seq, V &vertices){

    cout<<"Sequence"<<endl;
    int a,b;

    while(file >> a >> b){

        Edge e(a,b);

        seq.push_back(e);

        typename V::iterator it = find(vertices.begin(), vertices.end(), a);
        if(it == vertices.end()) vertices.push_back(a);
        
        it = find(vertices.begin(), vertices.end(), b);
        if(it == vertices.end()) vertices.push_back(b);

    }

}

template<Associative_container S, Associative_container V>
void readData(ifstream &file, S &seq, V &vertices){

    cout<<"ASS"<<endl;
    int a,b;

    while(file >> a >> b){

        Edge e(a,b);

        seq.insert(e);

        typename V::iterator it = vertices.find(a);
        if(it == vertices.end()) vertices.insert(a);
        
        it = vertices.find(b);
        if(it == vertices.end()) vertices.insert(b);
        
    }

}

template<Sequence E, Sequence V>
void fill(E &edges, V &vertices){

    ifstream file("../data/file3.txt");
    
    if(!file){
        cout <<"Error input file";
        exit(0);
    }

    readData(file, edges, vertices);
    sortVertices<V, typename V::iterator>(vertices);
    file.close();

}

template<Associative_container E, Associative_container V>
void fill(E &edges, V &vertices){

    ifstream file("../data/file3.txt");
    
    if(!file){
        cout <<"Error input file";
        exit(0);
    }

    readData(file, edges, vertices);
    sortVertices<V>(vertices);
    file.close();

}

template<typename E>
void print(E &edges){
    cout<<endl<<"Graph: "<<endl<<endl;
    for(typename E::iterator it = edges.begin(); it != edges.end(); it++)
        cout << it->toString();
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
    return distance(edges.begin(), find_if(edges.begin(), edges.end(), Edge(e.getA(), e.getB())));
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
    
    // cout<<"przekazane v:"<<v<<endl;
    // typename A::iterator it = find_if(edges.begin(), edges.end(), findByAOrB(v));
    typename A::iterator it2;
    for(typename A::iterator it = edges.begin(); it != edges.end(); it++){
        if(it->getA() == v || it->getB() == v){
            // cout<<it->toString();
            // cout<<"HEHJHJJJJJ"<<endl;
            it2 = it;
            if(it->getA() == v) v = it->getB();
            else v = it->getA();
            it = prev(edges.end());
        }
    }

    // cout<<"found: "<<it2->toString();
    // if(it->getA() == v) v = it->getB();
    // else v = it->getA();

    edges.erase(it2);
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