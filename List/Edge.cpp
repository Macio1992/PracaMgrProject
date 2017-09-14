#include "Edge.h"

#include <iostream>
#include <sstream>

using namespace std;

Edge::Edge(int aa, int bb) : a(aa), b(bb) {}

Edge::~Edge(){}

bool Edge::operator==(Edge e) {
	return (a == e.getB() && b == e.getA()) ? true : false;
}

bool Edge::operator==(int v) {
	return (a == v || b == v);
}

int Edge::getA(){
	return a;
}

int Edge::getB(){
	return b;
}

string Edge::toString() const{

	stringstream stm;

	stm << a << " - " << b << endl;

	return stm.str();
}