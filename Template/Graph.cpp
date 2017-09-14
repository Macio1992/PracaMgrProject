#include "Graph.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>

using namespace std;

template<typename T, typename U>
Graph<T,U>::Graph(){}

template<typename T, typename U>
Graph<T,U>::~Graph(){}

template<typename T, typename U>
void Graph<T,U>::fill(){

    ifstream file("../data/file2.txt");

    if(!file) {
        cout << "Error while opening the file"<<endl;
        exit(0);
    }

    int a,b;

    while(file >> a >> b){
        Edge e(a,b);

        edges.push_back(e);

        typename U::iterator it = find(vertices.begin(), vertices.end(), a);

        if(it == vertices.end())
            vertices.push_back(a);

        it = find(vertices.begin(), vertices.end(), b);

        if(it == vertices.end())
            vertices.push_back(b);

        sort(vertices.begin(), vertices.end());
    }

    file.close();

}

template<typename T, typename U>
void Graph<T,U>::print(){
    cout<<endl<<"Graph: "<<endl<<endl;
    for(typename T::iterator it = edges.begin(); it != edges.end(); ++it)
        cout <<it->toString();
    cout<<endl;
}

template<typename T, typename U>
bool Graph<T,U>::checkIfGraphConnected(T &ed, int x){
    
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
		for(typename T::iterator i = edges.begin(); i != edges.end(); i++) {
			if (i->getA() == v) {
				if (!visited[i->getB()]){
					visited[i->getB()] = true;
					stack.push(i->getB());
				}
			} else if (i->getB() == v) {
				if (!visited[i->getA()]){
					visited[i->getA()] = true;
					stack.push(i->getA());
				}
			}
		}

	}
    
    delete [] visited;

    return (vc == vertices.size()-x) ? true : false;

}

template<typename T, typename U>
bool Graph<T,U>::checkIfEdgeExistsInGraph(Edge e){
    return (find(edges.begin(), edges.end(), Edge(e.getA(), e.getB())) != edges.end()) ? true : false;
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
bool Graph<T,U>::checkIfStillConnected(Edge e, int x){
    
    T tmp;

    for(auto e : edges)
        tmp.push_back(e);

    for(typename T::iterator i = tmp.begin(); i != tmp.end(); i++)
        if (i->getA() == e.getA() && i->getB() == e.getB()) {
			tmp.erase(i);
			i = prev(tmp.end());
        }

    return checkIfGraphConnected(tmp, x) ? true : false;
}

template<typename T, typename U>
int Graph<T,U>::getZeroDegreeCount(int v){
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
        if(i->getA() == v){
            if(checkIfStillConnected(*i, getZeroDegreeCount(v))){
                v = i->getB();
                edges.erase(i);
                i = prev(edges.end());
            }
        } else if(i->getB() == v){
            if(checkIfStillConnected(*i, getZeroDegreeCount(v))){
                v = i->getA();
                edges.erase(i);
                i = prev(edges.end());
            }
        }
    }
}

template<typename T, typename U>
void Graph<T,U>::determineEulerCycle(){

    bool condition = (checkIfGraphConnected(edges, 0) && checkIfAllEdgesEvenDegree());
    int v = 0;

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

}