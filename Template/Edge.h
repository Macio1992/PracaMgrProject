#ifndef Edge_H
#define Edge_H

#include <iostream>
#include <sstream>

using namespace std;

class Edge
{
public:
	Edge(int, int);
    ~Edge();
    bool operator==(Edge);
	bool operator==(int);
    string toString() const;
    int getA() const;
	int getB() const;

private:
	int a;
	int b;
};

#endif // !Edge_H