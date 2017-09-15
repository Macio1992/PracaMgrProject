#ifndef Edge_H
#define Edge_H

#include <iostream>

#include <string>

using namespace std;

class Edge {
    public:
        Edge(int, int);
        ~Edge();
        bool operator==(Edge);
        bool operator==(int);
        int getA() const;
        int getB() const;
        string toString() const;

    private:
        int a;
        int b;
};

#endif