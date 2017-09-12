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

    ifstream file("../data/file2.txt");

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

                    edges.erase(edges.begin() + distance(edges.begin(), it));

                    break;
                }
                default: {

                    for(int u = 0; u < edges.size(); u++){
                        if(edges[u].getA() == v){
                            if(checkIfStillConnected(edges[u], zeroDegreeVertex)){
                                v = edges[u].getB();
                                edges.erase(edges.begin() + u);
                                u = edges.size();
                            }
                        } else if(edges[u].getB() == v){
                            if(checkIfStillConnected(edges[u], zeroDegreeVertex)){
                                v = edges[u].getA();
                                edges.erase(edges.begin() + u);
                                u = edges.size();
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