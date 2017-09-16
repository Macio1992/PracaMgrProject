#ifndef Edge_H
#define Edge_H

#include <iostream>

using namespace std;

class Edge {
    public:
        Edge(int, int);
        ~Edge();
        bool operator==(Edge);
        bool operator==(int);
        bool operator()(Edge);
        bool operator<(const Edge&) const;
        int getA() const;
        int getB() const;
        string toString() const;

    private:
        int a;
        int b;
};

#endif