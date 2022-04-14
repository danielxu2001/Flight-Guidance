#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <stack>

#include "vertex.h"
#include "edge.h"
struct Path{
    std::vector<Edge> edges;
    int distance;
    Vertex start;
    Path() {}
    Path(const Vertex &start, const std::vector<Edge> &route) {
        edges = route;
        distance = 0;
        this->start = start;
        for (auto &edge : edges) {
            distance += edge.getWeight();
        }
    }
    Path(const Vertex &start) {
        edges = std::vector<Edge>();
        this->start = start;
        distance = 0;
    }
};

// customized minimum adjacency list implementation of a directed graph
class Graph {
    public:
    // returns true if insertion is successful
    bool insertVertex(Vertex v);
    // returns true if edge is created/updated
    bool insertEdge(Vertex source, Vertex destination);
    // directed version of areAdjacent
    bool canTravel(Vertex source, Vertex destination);

    std::vector<Vertex> getVertices() const;
    Edge getEdge(Vertex source, Vertex destination);

    std::vector<Vertex> getAdjacent(Vertex source);

    // Kosaraju’s algorithm
    // each vector represents a strongly connected component
    std::vector<std::vector<Vertex> > stronglyConnectedComponents();
    std::unordered_map<Vertex, Path> shortestPath(Vertex start);
    
    void setEdgeWeight(Vertex source, Vertex dest, int weight);
    int getEdgeWeight(Vertex source, Vertex dest);


    private:
    Graph reversed();
    void fill(Vertex vertex, std::unordered_set<Vertex> & visited, std::stack<Vertex> & st);
    void DFS(Vertex vertex, std::unordered_set<Vertex> & visited, std::vector<Vertex> & vec);
    std::unordered_map<Vertex, std::unordered_map<Vertex, Edge> > adj_list_;
};