#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

class Edge {
    public:
        Edge(int a, int b) : a(a), b(b) {}
        bool operator<(const Edge &e) const{
            return true;
        }
        string toString(){
            stringstream s;
            s << a << " - " << b << endl;
            return s.str();
        }
        int getA(){
            return a;
        }
        int getB(){
            return b;
        }

    private:
        int a;
        int b;
};

int main(){

    list<Edge> edges;
    // list<int> vertices;
    vector<int> vertices;

    edges.push_back(Edge(1,2));
    edges.push_back(Edge(3,4));
    edges.push_back(Edge(5,6));
    edges.push_back(Edge(7,8));

    vertices.push_back(11);
    vertices.push_back(1);
    vertices.push_back(9);
    vertices.push_back(112);

    for(list<Edge>::iterator i = edges.begin(); i != edges.end(); i++){
        // if(i->getA() == 5)
            // edges.erase(i);
    }

    for(auto e : edges)
        cout<<e.toString();

    return 0;
}