#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "vertex.h"
#include "airport.h"
#include "edge.h"
#include "graph.h"
#include "bfs.h"
#include "utils.h"

using std::istringstream;
using std::string;
using std::vector;

int main() {
    Graph graph;
    std::unordered_map<Vertex, Airport> airports;

    std::ifstream airport_file("dataset/airports.dat");
    string line;
    string word;
    vector<string> words(15);
    if (airport_file.is_open()) {
        while (getline(airport_file, line)) {
            int idx = 0;
            istringstream ss(line);
            while (getline(ss, words[idx++], ',')) {}
            // some airports don't have IATA code
            // IATA -> words[4]; ICAO -> words[5]
            if (words[4] != "\\N") {
                // get rid of double quotes
                words[4] = words[4].substr(1, words[4].length() - 2);
                airports[words[4]] = Airport(words[4], stod(words[6]), stod(words[7]));
                graph.insertVertex(words[4]);
            } else {
                words[5] = words[5].substr(1, words[5].length() - 2);
                airports[words[5]] = Airport(words[5], stod(words[6]), stod(words[7]));
                graph.insertVertex(words[5]);
            }
        }
    }
    std::cout << "# of airports " << airports.size() << std::endl;

    std::ifstream route_file("dataset/routes.dat");
    int num = 0;
    if (route_file.is_open()) {
        while (getline(route_file, line)) {
            int idx = 0;
            istringstream ss(line);
            while (getline(ss, words[idx++], ',')) {}

            if (graph.insertEdge(words[2], words[4])) {
                // use distance between airports as edge weight
                Airport a1 = airports.at(words[2]);
                Airport a2 = airports.at(words[4]);
                double dis =  calculateDistance(a1.getLatitude(), a1.getLongtitude(),
                                               a2.getLatitude(), a2.getLongtitude());
                graph.setEdgeWeight(words[2], words[4], (int) ceil(dis / 200));
                ++num;
            }
        }
    }
    std::cout << "# of routes " << num << std::endl;

    vector<Vertex> p;
    BFS traversal(&graph, "NKG");

    // supports enhanced for loop
    // for (auto v : traversal) {
    //     std::cout << v << std::endl;
    // }

    for (auto iter = traversal.begin(); iter != traversal.end(); ++iter) {
        p.push_back(*iter);
    }
    std::cout << "traversed " << p.size() << " airports" << std::endl;
    std::cout << "The first 20 airports we went to: " << std::endl;
    for (int i = 0; i != 20; ++i) {
        std::cout << p[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Strongly connected components: " << std::endl;
    vector<vector<Vertex>> components = graph.stronglyConnectedComponents();
    for (auto v : components) {
        if (v.size() > 1) {
            std::cout << v.size() << std::endl;
            for (auto vertex : v) {
                std::cout << vertex << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}