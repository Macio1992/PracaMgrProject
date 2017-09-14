#include "Edge.h"

Edge::Edge(int a, int b): a(a), b(b) {}

Edge::~Edge(){}

bool Edge::operator==(Edge e) {
	return (a == e.getB() && b == e.getA());
}

bool Edge::operator==(int v) {
	return (a == v || b == v);
}

int Edge::getA() const{
	return a;
}

int Edge::getB() const{
	return b;
}

string Edge::toString() const{
    
    stringstream stm;
    stm << a << " - " << b << endl;

    return stm.str();
}