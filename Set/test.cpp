#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Edge {

    public:

        Edge(int aa, int bb) : a(aa), b(bb) {}
        // Edge(int value) : value(value) {
        //     cout <<"konstuktor jedej zmiennej: "<<value<<endl;
        // }
        ~Edge(){}
        bool operator<(const Edge &e) const {
            return true;
        }
        // bool operator<(int &v){
        //     return (v < a || v < b);
        // }
        bool operator()(Edge edge){
            return (edge.getA() == a && edge.getB() == b);
        }
        // bool operator()(){
        //     return (a == value || b == value);
        // }
        string toString() const {
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
        // int value;
};

struct findByAOrB {
    findByAOrB(int value) : value(value){}
    bool operator()(Edge edge) {
        return (edge.getA() == value || edge.getB() == value);
    }
    private:
        int value;
};

int main (){

    set<Edge> edges;
    edges.insert(Edge(4,5));
    edges.insert(Edge(1,2));
    edges.insert(Edge(3,12));
    edges.insert(Edge(56,1));
    edges.insert(Edge(3,6));
    edges.insert(Edge(111,2222));
    edges.insert(Edge(40,50));
    edges.insert(Edge(19,22));

    set<Edge>::iterator result = find_if(edges.begin(), edges.end(), findByAOrB(101));

    if(result != edges.end()) cout <<"znaleziono"<<endl;
    else cout <<"nie znaleziono"<<endl;

    

    return 0;
}