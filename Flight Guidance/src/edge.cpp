#include "edge.h"

int Edge::getWeight() const {
        return weight_;
    }

void Edge::setWeight(int w) {
    weight_ = w;
}

Vertex Edge::getSource() const {
    return source_;
}

Vertex Edge::getDestination() const {
    return dest_;
}