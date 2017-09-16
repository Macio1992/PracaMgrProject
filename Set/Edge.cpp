#include "Edge.h"

#include <iostream>
#include <sstream>

using namespace std;

Edge::Edge(int aa, int bb) : a(aa), b(bb) {}

Edge::~Edge(){}

bool Edge::operator()(Edge edge){
	return (edge.getA() == a && edge.getB() == b);
}

bool Edge::operator<(const Edge &e) const{
	return true;
}

int Edge::getA() const{
	return a;
}

void Edge::setA(int aa) {
	a = aa;
}

int Edge::getB() const{
	return b;
}

void Edge::setB(int bb) {
	b = bb;
}

string Edge::toString() const{

	stringstream stm;

	stm << a << " - " << b << endl;

	return stm.str();
}
