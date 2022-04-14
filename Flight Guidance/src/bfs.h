#pragma once

#include <iterator>
#include <queue>
#include <vector>
#include <unordered_set>
#include <iostream>
#include "graph.h"

class BFS {
    public:
        class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
            public:
                static const Vertex TRAVERSAL_END;
                Iterator(BFS * bfs) :
                    bfs_(bfs),
                    curr_(TRAVERSAL_END) {

                }

                Iterator(BFS * bfs, Vertex v) :
                    bfs_(bfs),
                    curr_(v) {
                    
                }

                Iterator & operator++() {
                    if (bfs_->empty()) {
                        curr_ = TRAVERSAL_END;
                    } else {
                        curr_ = bfs_->next();
                    }
                    return *this;
                }

                Vertex operator*() {
                    return curr_;
                }

                bool operator!=(const Iterator & other) const {
                    return bfs_ != other.bfs_ || curr_ != other.curr_;
                }

            private:
                BFS * bfs_;
                Vertex curr_;
        };

        BFS(Graph * graph, Vertex start) :
            start_(start),
            queue_(std::queue<Vertex>()),
            graph_(graph),
            visited_(std::unordered_set<Vertex>()) {
            vertices_ = graph->getVertices();
            visited_ = std::unordered_set<Vertex>();
        }

        Iterator begin();
        Iterator end();

    private:
        Vertex next();
        bool empty();
        void goToNextIdx();

        Vertex start_;
        std::queue<Vertex> queue_;
        Graph * graph_;
        std::vector<Vertex> vertices_;
        std::unordered_set<Vertex> visited_;
        size_t next_idx_;
};