#include "bfs.h"

const Vertex BFS::Iterator::TRAVERSAL_END = "TRAEND";

BFS::Iterator BFS::begin() {
    next_idx_ = 0;
    visited_.insert(start_);
    std::vector<Vertex> adjacent = graph_->getAdjacent(start_);
    for (size_t i = 0; i != adjacent.size(); ++i) {
        if (visited_.find(adjacent[i]) == visited_.end()) {
            queue_.push(adjacent[i]);
            visited_.insert(adjacent[i]);
        }
    }
    return Iterator(this, start_);
}

BFS::Iterator BFS::end() {
    return Iterator(this);
}

Vertex BFS::next() {
    Vertex next;
    if (!empty()) {
        if (queue_.empty()) {
            next = vertices_[next_idx_];
            visited_.insert(next);
            next_idx_++;
        } else {
            next = queue_.front();
            queue_.pop();
        }
        std::vector<Vertex> adjacent = graph_->getAdjacent(next);
        for (size_t i = 0; i != adjacent.size(); ++i) {
            if (visited_.find(adjacent[i]) == visited_.end()) {
                queue_.push(adjacent[i]);
                visited_.insert(adjacent[i]);
            }
        }
    }
    return next;
}

bool BFS::empty() {
    goToNextIdx();
    return next_idx_ >= vertices_.size() && queue_.empty();
}

// update next_idx_ to next unvisited vertex
void BFS::goToNextIdx() {
    while (next_idx_ < vertices_.size()
        && visited_.find(vertices_[next_idx_]) != visited_.end()) {
        ++next_idx_;
    }
}