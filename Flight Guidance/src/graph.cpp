#include "graph.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <climits>
using std::unordered_set;
using std::unordered_map;
using std::vector;
using std::stack;

bool Graph::insertVertex(Vertex v) {
    if (adj_list_.find(v) != adj_list_.end()) {
        return false;
    }
    adj_list_[v] = unordered_map<Vertex, Edge>();
    return true;
}


bool Graph::insertEdge(Vertex source, Vertex destination) {
    if (adj_list_.find(source) == adj_list_.end()) {
        return false;
    } else if (adj_list_.find(destination) == adj_list_.end()) {
        return false;
    } else if (adj_list_[source].find(destination) != adj_list_[source].end()) {
        return false;
    }

    // insert edge
    adj_list_[source][destination] = Edge(source, destination, 10);
    return true;
}

bool Graph::canTravel(Vertex source, Vertex destination) {
    if (adj_list_.find(source) == adj_list_.end()) {
        return false;
    }
    return adj_list_[source].find(destination) != adj_list_[source].end();
}

std::vector<Vertex> Graph::getVertices() const {
    vector<Vertex> vec;
    for (unordered_map<Vertex, unordered_map<Vertex, Edge> >::const_iterator
    iter = adj_list_.cbegin(); iter != adj_list_.cend(); ++iter) {
        vec.push_back(iter->first);
    }
    return vec;
}

vector<Vertex> Graph::getAdjacent(Vertex source) {
    vector<Vertex> ret;
    if (adj_list_.find(source) == adj_list_.end()) {
        return ret;
    }
    for (unordered_map<Vertex, Edge>::const_iterator
        i = adj_list_[source].cbegin(); i != adj_list_[source].cend(); ++i) {
        ret.push_back(i->first);
    }
    return ret;
}

vector<vector<Vertex> > Graph::stronglyConnectedComponents() {
    vector<vector<Vertex>> ret;
    unordered_set<Vertex> visited;
    stack<Vertex> st;
    Graph r = reversed();

    for (Vertex v : getVertices()) {
        if (visited.find(v) == visited.end()) {
            fill(v, visited, st);
        }
    }
    
    visited.clear();
    while (!st.empty()) {
        Vertex v = st.top();
        st.pop();
        if (visited.find(v) == visited.end()) {
            vector<Vertex> vec;
            r.DFS(v, visited, vec);
            ret.push_back(vec);
        }
    }
    return ret;
}

Graph Graph::reversed() {
    Graph r;
    for (const Vertex v : getVertices()) {
        r.insertVertex(v);
    }
    for (auto & p : adj_list_) {
        for (auto & v : p.second) {
            r.insertEdge(v.first, p.first);
        }
    }
    return r;
}

void Graph::fill(Vertex vertex, std::unordered_set<Vertex> & visited, std::stack<Vertex> & st) {
    visited.insert(vertex);
    for (Vertex v : getAdjacent(vertex)) {
        if (visited.find(v) == visited.end()) {
            fill(v, visited, st);
        }
    }
    st.push(vertex);
}

void Graph::DFS(Vertex vertex, unordered_set<Vertex> & visited, std::vector<Vertex> & vec) {
    visited.insert(vertex);
    vec.push_back(vertex);
    auto adjacent = getAdjacent(vertex);
    for (Vertex v : adjacent) {
        if (visited.find(v) == visited.end()) {
            DFS(v, visited, vec);
        }
    }
}
unordered_map<Vertex, Path> Graph::shortestPath(Vertex start) {
    unordered_map<Vertex, Path> result;
    
    auto vertices = getVertices();

    for(auto vertex: vertices) {
        Path infinite = Path(start);
        infinite.distance = INT_MAX;
        result[vertex] = infinite;
    }
    unordered_set<Vertex> unsured(vertices.begin(),vertices.end());
    unsured.erase(start);
    auto Adjacent = getAdjacent(start);

    result[start] = Path(start);

    // update adjacent
    for(auto adj : Adjacent) {
        std::vector<Edge> edges;
        edges.push_back(adj_list_[start][adj]);
        result[adj] = Path(start, edges);
    }
    while(! unsured.empty()) {
        int smallest = INT_MAX;
        Vertex smallestVertex;
        //shortest in unsure
        for (auto vertex:unsured) {
            if (result[vertex].distance < smallest) {
                smallest = result[vertex].distance;
                smallestVertex = vertex;
            }
        }
        if (smallest == INT_MAX) {
            break;
        }
        //update 
        for (auto vertex : getAdjacent(smallestVertex)) {
            if (unsured.find(vertex) != unsured.end()) {
                int edgeWeight = adj_list_[smallestVertex][vertex].getWeight();
                if (smallest+edgeWeight < result[vertex].distance) {
                    Path p = result[smallestVertex];
                    p.edges.push_back(adj_list_[smallestVertex][vertex]);
                    p.distance += edgeWeight;
                    result[vertex] = p;
                }
            }
        }
        unsured.erase(smallestVertex);
    }
    return result;
}

void Graph::setEdgeWeight(Vertex source, Vertex dest, int weight) {
    adj_list_[source][dest].setWeight(weight);
}

int Graph::getEdgeWeight(Vertex source, Vertex dest) {
    return adj_list_[source][dest].getWeight();
}

Edge Graph::getEdge(Vertex source, Vertex destination) {
    if (adj_list_.find(source) == adj_list_.end()) {
        return Edge();
    } else if (adj_list_[source].find(destination) == adj_list_[source].end()) {
        return Edge();
    }

    return adj_list_[source][destination];
}




