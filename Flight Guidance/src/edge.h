#pragma once

#include "vertex.h"

class Edge {
    public:
    Edge() {} // only for unordered_map
    Edge(Vertex source, Vertex dest, int weight) :
        source_(source),
        dest_(dest),
        weight_(weight) {}

    Edge(Vertex source, Vertex dest) :
        source_(source),
        dest_(dest),
        weight_(1) {}

    int getWeight() const;
    void setWeight(int w);
    Vertex getSource() const;
    Vertex getDestination() const;

    private:
    Vertex source_;
    Vertex dest_;
    int weight_;
};