#include "Edge.h"
#include <iostream>
#include <sstream>

using namespace std;

Edge::Edge(int a, int b): a(a), b(b) {}

Edge::~Edge() {}

bool Edge::operator==(Edge e){
    return (e.getA() == a && e.getB() == b);
}
bool Edge::operator==(int value){
    return (value == a || value == b);
}
bool Edge::operator()(Edge edge){
	return (edge.getA() == a && edge.getB() == b);
}
bool Edge::operator<(const Edge &e) const{
	return true;
}
int Edge::getA() const {
    return a;
}
int Edge::getB() const {
    return b;
}
string Edge::toString() const {
    
    stringstream s;
    s<<a<<" - "<<b<<endl;

    return s.str();

}