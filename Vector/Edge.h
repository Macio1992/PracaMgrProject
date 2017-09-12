#ifndef Edge_H
#define Edge_H

#include <iostream>

using namespace std;

class Edge
{
public:
	Edge(int, int);
	~Edge();
	bool operator==(Edge);
	bool operator==(int);
	string toString();
	int getA();
	int getB();
	void setA(int);
	void setB(int);

private:
	int a;
	int b;
};


#endif