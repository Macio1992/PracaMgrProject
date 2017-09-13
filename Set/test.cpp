#include <iostream>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Edge {

    public:
        Edge(int aa, int bb){
            a = aa;
            b = bb;
        }
        ~Edge(){}
        bool operator<(const Edge &e) const {
            return true;
        }
        bool operator==(const Edge &e) const {
            return true;
        }
        string toString() const {
            stringstream s;
            s << a << " + " << b;
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

int main (){

    Edge e(4,5);
    set<Edge> edges;
    edges.insert(e);

    return 0;
}