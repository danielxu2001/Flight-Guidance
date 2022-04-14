#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../graph.h"
#include "../bfs.h"

#include "../utils.h"

#include <vector>
#include <iostream>
#include <climits>
using std::vector;

TEST_CASE("test insertVertex", "[weight=1]") {
    Graph g1;
    REQUIRE(g1.insertVertex("a"));
    REQUIRE(g1.insertVertex("b"));
    REQUIRE(!g1.insertVertex("a"));
    REQUIRE(!g1.insertVertex("b"));
}
TEST_CASE("test insertEdge", "[weight=1]") {
    Graph g2;
    g2.insertVertex("a");
    g2.insertVertex("b");
    g2.insertVertex("c");
    REQUIRE(g2.insertEdge("a","b"));
    REQUIRE(g2.insertEdge("b","c"));
    REQUIRE(!g2.insertEdge("a", "e"));
    REQUIRE(!g2.insertEdge("f", "g"));
}
TEST_CASE("test canTravel", "[weight=1]") {
    Graph g3;
    g3.insertVertex("a");
    g3.insertVertex("b");
    g3.insertVertex("c");
    g3.insertVertex("d");
    g3.insertEdge("a","b");
    g3.insertEdge("b","c");
    REQUIRE(g3.canTravel("a","b"));
    REQUIRE(g3.canTravel("b","c"));
    REQUIRE(!g3.canTravel("b","d"));
    REQUIRE(!g3.canTravel("c","b")); 
}
TEST_CASE("test getVertices", "[weight=1]") {
    Graph g4;
    REQUIRE(g4.getVertices().size() == 0);
    g4.insertVertex("a");
    REQUIRE(g4.getVertices().size() == 1);
    g4.insertVertex("b");
    REQUIRE(g4.getVertices().size() == 2);
    g4.insertVertex("c");
    REQUIRE(g4.getVertices().size() == 3);
}
TEST_CASE("test getAdjacent", "[weight=1]") {
    Graph g5;
    g5.insertVertex("a");
    g5.insertVertex("b");
    g5.insertVertex("c");
    g5.insertEdge("a","b");
    g5.insertEdge("a","c");
    g5.insertEdge("b","c");
    REQUIRE(g5.getAdjacent("a").size() == 2);
    REQUIRE(g5.getAdjacent("b").size() == 1);
}
TEST_CASE("test bfs with no edge", "[weight=1]") {
  Graph graph1;
  graph1.insertVertex("ABC");
  graph1.insertVertex("ABB");
  graph1.insertVertex("ACD");
  graph1.insertVertex("BBC");
  graph1.insertVertex("BAC");
  BFS traversal(&graph1, "ABC");
  auto iter = traversal.begin();
  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test bfs with one edge", "[weight=1]") {
  Graph graph2;
  graph2.insertVertex("ABC");
  graph2.insertVertex("ABB");
  graph2.insertVertex("ACD");
  graph2.insertVertex("BBC");
  graph2.insertVertex("BAC");
  graph2.insertEdge("ABC", "ABB");
  BFS traversal(&graph2, "ABC");
  auto iter = traversal.begin();
  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test bfs with several edge1", "[weight=1]") {
  Graph g;
  g.insertVertex("ABC");
  g.insertVertex("ABB");
  g.insertVertex("ACD");
  g.insertVertex("BBC");
  g.insertVertex("BAC");
  g.insertEdge("ABC", "ABB");
  g.insertEdge("ABC", "BAC");
  BFS traversal(&g, "ABC");
  auto iter = traversal.begin();
  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test bfs with several edge2", "[weight=1]") {
  Graph graph;
  graph.insertVertex("ABC");
  graph.insertVertex("ABB");
  graph.insertVertex("ACD");
  graph.insertVertex("BBC");
  graph.insertVertex("BAC");
  graph.insertEdge("ABC", "ABB");
  graph.insertEdge("ABB", "BAC");
  BFS traversal(&graph, "ABC");
  auto iter = traversal.begin();

  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test bfs with two separate edge1" "[weight=1]") {
  Graph graph3;
  graph3.insertVertex("ABC");
  graph3.insertVertex("ABB");
  graph3.insertVertex("ACD");
  graph3.insertVertex("BBC");
  graph3.insertVertex("BAC");
  graph3.insertEdge("ABC", "ABB");
  graph3.insertEdge("BBC", "BAC");
  BFS traversal(&graph3, "ABC");
  auto iter = traversal.begin();
  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test bfs with two separate edge2" "[weight=1]") {
  Graph graph5;
  graph5.insertVertex("ABC");
  graph5.insertVertex("ABB");
  graph5.insertVertex("ACD");
  graph5.insertVertex("BBC");
  graph5.insertVertex("BAC");
  graph5.insertEdge("ABC", "ABB");
  graph5.insertEdge("ABB", "BAC");
  graph5.insertEdge("BBC", "BAC");
  BFS traversal(&graph5, "ABC");
  auto iter = traversal.begin();
  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test bfs with all connected edge" "[weight=1]") {
  Graph graph4;
  graph4.insertVertex("ABC");
  graph4.insertVertex("ABB");
  graph4.insertVertex("ACD");
  graph4.insertVertex("BBC");
  graph4.insertVertex("BAC");
  graph4.insertEdge("ABC", "ABB");
  graph4.insertEdge("ABB", "ACD");
  graph4.insertEdge("ACD", "BBC");
  graph4.insertEdge("BBC", "BAC");
  BFS traversal(&graph4, "ABC");
  auto iter = traversal.begin();
  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test bfs with one edge connnected to all vertex" "[weight=1]") {
  Graph graph6;
  graph6.insertVertex("ABC");
  graph6.insertVertex("ABB");
  graph6.insertVertex("ACD");
  graph6.insertVertex("BBC");
  graph6.insertVertex("BAC");
  graph6.insertEdge("ABC", "ABB");
  graph6.insertEdge("ABC", "BAC");
  graph6.insertEdge("ABC", "BBC");
  graph6.insertEdge("ABC", "ACD");
  BFS traversal(&graph6, "ABC");
  auto iter = traversal.begin();
  REQUIRE(*iter == "ABC");
  ++iter;
  REQUIRE(*iter == "ACD");
  ++iter;
  REQUIRE(*iter == "BBC");
  ++iter;
  REQUIRE(*iter == "BAC");
  ++iter;
  REQUIRE(*iter == "ABB");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}

TEST_CASE("test ten vertices bfs1", "[weight=1]") {
  Graph graph2;
  graph2.insertVertex("AAA");
  graph2.insertVertex("AAB");
  graph2.insertVertex("AAC");
  graph2.insertVertex("AAD");
  graph2.insertVertex("AAE");
  graph2.insertVertex("AAF");
  graph2.insertVertex("AAG");
  graph2.insertVertex("AAH");
  graph2.insertVertex("AAI");
  graph2.insertVertex("AAJ");
  graph2.insertEdge("AAA","AAB");
  graph2.insertEdge("AAC","AAD");
  graph2.insertEdge("AAE","AAF");
  graph2.insertEdge("AAG","AAH");
  graph2.insertEdge("AAI","AAJ");
  BFS traversal(&graph2, "AAA");
  auto iter = traversal.begin();
  REQUIRE(*iter == "AAA");
  ++iter;
  REQUIRE(*iter == "AAB");
  ++iter;
  REQUIRE(*iter == "AAJ");
  ++iter;
  REQUIRE(*iter == "AAH");
  ++iter;
  REQUIRE(*iter == "AAF");
  ++iter;
  REQUIRE(*iter == "AAI");
  ++iter;
  REQUIRE(*iter == "AAE");
  ++iter;
  REQUIRE(*iter == "AAD");
  ++iter;
  REQUIRE(*iter == "AAG");
  ++iter;
  REQUIRE(*iter == "AAC");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}

TEST_CASE("test ten vertices bfs2", "[weight=1]") {
  Graph graph3;
  graph3.insertVertex("AAA");
  graph3.insertVertex("AAB");
  graph3.insertVertex("AAC");
  graph3.insertVertex("AAD");
  graph3.insertVertex("AAE");
  graph3.insertVertex("AAF");
  graph3.insertVertex("AAG");
  graph3.insertVertex("AAH");
  graph3.insertVertex("AAI");
  graph3.insertVertex("AAJ");
  graph3.insertEdge("AAA","AAB");
  graph3.insertEdge("AAB","AAC");
  graph3.insertEdge("AAD","AAE");
  graph3.insertEdge("AAE","AAF");
  graph3.insertEdge("AAG","AAH");
  graph3.insertEdge("AAH","AAI");
  BFS traversal(&graph3, "AAA");
  auto iter = traversal.begin();
  REQUIRE(*iter == "AAA");
  ++iter;
  REQUIRE(*iter == "AAB");
  ++iter;
  REQUIRE(*iter == "AAC");
  ++iter;
  REQUIRE(*iter == "AAJ");
  ++iter;
  REQUIRE(*iter == "AAH");
  ++iter;
  REQUIRE(*iter == "AAI");
  ++iter;
  REQUIRE(*iter == "AAF");
  ++iter;
  REQUIRE(*iter == "AAE");
  ++iter;
  REQUIRE(*iter == "AAD");
  ++iter;
  REQUIRE(*iter == "AAG");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}

TEST_CASE("test ten vertices bfs3", "[weight=1]") {
  Graph graph4;
  graph4.insertVertex("AAA");
  graph4.insertVertex("AAB");
  graph4.insertVertex("AAC");
  graph4.insertVertex("AAD");
  graph4.insertVertex("AAE");
  graph4.insertVertex("AAF");
  graph4.insertVertex("AAG");
  graph4.insertVertex("AAH");
  graph4.insertVertex("AAI");
  graph4.insertVertex("AAJ");
  graph4.insertEdge("AAA","AAB");
  graph4.insertEdge("AAB","AAC");
  graph4.insertEdge("AAC","AAD");
  graph4.insertEdge("AAE","AAF");
  graph4.insertEdge("AAF","AAG");
  graph4.insertEdge("AAG","AAH");
  BFS traversal(&graph4, "AAA");
  auto iter = traversal.begin();
  REQUIRE(*iter == "AAA");
  ++iter;
  REQUIRE(*iter == "AAB");
  ++iter;
  REQUIRE(*iter == "AAC");
  ++iter;
  REQUIRE(*iter == "AAD");
  ++iter;
  REQUIRE(*iter == "AAJ");
  ++iter;
  REQUIRE(*iter == "AAH");
  ++iter;

  REQUIRE(*iter == "AAF");
  ++iter;
  REQUIRE(*iter == "AAG");
  ++iter;
  REQUIRE(*iter == "AAI");
  ++iter;
  REQUIRE(*iter == "AAE");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}

TEST_CASE("test ten vertices bfs4", "[weight=1]") {
  Graph graph14;
  graph14.insertVertex("AAA");
  graph14.insertVertex("AAB");
  graph14.insertVertex("AAC");
  graph14.insertVertex("AAD");
  graph14.insertVertex("AAE");
  graph14.insertVertex("AAF");
  graph14.insertVertex("AAG");
  graph14.insertVertex("AAH");
  graph14.insertVertex("AAI");
  graph14.insertVertex("AAJ");
  graph14.insertEdge("AAA","AAB");
  graph14.insertEdge("AAA","AAC");
  graph14.insertEdge("AAA","AAD");
  graph14.insertEdge("AAA","AAE");
  graph14.insertEdge("AAF","AAG");
  graph14.insertEdge("AAF","AAH");
  graph14.insertEdge("AAF","AAI");
  graph14.insertEdge("AAF","AAJ");
  BFS traversal(&graph14, "AAA");
  auto iter = traversal.begin();
  REQUIRE(*iter == "AAA");
  ++iter;
  REQUIRE(*iter == "AAE");
  ++iter;
  REQUIRE(*iter == "AAD");
  ++iter;
  REQUIRE(*iter == "AAC");
  ++iter;
  REQUIRE(*iter == "AAB");
  ++iter;
  REQUIRE(*iter == "AAJ");
  ++iter;
  REQUIRE(*iter == "AAH");
  ++iter;
  REQUIRE(*iter == "AAF");
  ++iter;
  REQUIRE(*iter == "AAI");
  ++iter;
  REQUIRE(*iter == "AAG");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}

TEST_CASE("test ten vertices bfs5", "[weight=1]") {
  Graph graph10;
  graph10.insertVertex("AAA");
  graph10.insertVertex("AAB");
  graph10.insertVertex("AAC");
  graph10.insertVertex("AAD");
  graph10.insertVertex("AAE");
  graph10.insertVertex("AAF");
  graph10.insertVertex("AAG");
  graph10.insertVertex("AAH");
  graph10.insertVertex("AAI");
  graph10.insertVertex("AAJ");
  graph10.insertEdge("AAA","AAB");
  graph10.insertEdge("AAB","AAC");
  graph10.insertEdge("AAC","AAD");
  graph10.insertEdge("AAD","AAE");
  graph10.insertEdge("AAE","AAF");
  graph10.insertEdge("AAF","AAG");
  graph10.insertEdge("AAG","AAH");
  graph10.insertEdge("AAH","AAI");
  graph10.insertEdge("AAI","AAJ");
  BFS traversal(&graph10, "AAA");
  auto iter = traversal.begin();
  REQUIRE(*iter == "AAA");
  ++iter;
  REQUIRE(*iter == "AAB");
  ++iter;
  REQUIRE(*iter == "AAC");
  ++iter;
  REQUIRE(*iter == "AAD");
  ++iter;
  REQUIRE(*iter == "AAE");
  ++iter;
  REQUIRE(*iter == "AAF");
  ++iter;
  REQUIRE(*iter == "AAG");
  ++iter;
  REQUIRE(*iter == "AAH");
  ++iter;
  REQUIRE(*iter == "AAI");
  ++iter;
  REQUIRE(*iter == "AAJ");
  ++iter;
  REQUIRE_FALSE(iter != traversal.end());
}
TEST_CASE("test basic stronglyConnectedComponents1" "[weight=1]") {
  Graph graph;
  graph.insertVertex("A");
  graph.insertVertex("B");
  graph.insertVertex("C");
  graph.insertEdge("A","B");
  graph.insertEdge("B","C");
  REQUIRE(graph.stronglyConnectedComponents().size() == 3);
}
TEST_CASE("test basic stronglyConnectedComponents2" "[weight=1]") {
  Graph graph;
  graph.insertVertex("A");
  graph.insertVertex("B");
  graph.insertVertex("C");
  graph.insertEdge("A","B");
  graph.insertEdge("B","C");
  graph.insertEdge("C","A");
  REQUIRE(graph.stronglyConnectedComponents().size() == 1);
}
TEST_CASE("test basic stronglyConnectedComponents3" "[weight=1]") {
  Graph graph;
  graph.insertVertex("A");
  graph.insertVertex("B");
  graph.insertVertex("C");
  graph.insertVertex("D");
  graph.insertVertex("E");
  graph.insertEdge("A","B");
  graph.insertEdge("B","C");
  graph.insertEdge("A","C");
  graph.insertEdge("C","D");
  graph.insertEdge("D","E");
  graph.insertEdge("E","B");
  REQUIRE(graph.stronglyConnectedComponents().size() == 2);
}
TEST_CASE("test advanced stronglyConnectedComponents1" "[weight=1]") {
  Graph graph;
  graph.insertVertex("A");
  graph.insertVertex("B");
  graph.insertVertex("C");
  graph.insertVertex("D");
  graph.insertVertex("E");
  graph.insertVertex("F");
  graph.insertEdge("A","B");
  graph.insertEdge("B","C");
  graph.insertEdge("C","A");
  graph.insertEdge("C","E");
  graph.insertEdge("E","F");
  graph.insertEdge("F","D");
  graph.insertEdge("D","E");
  REQUIRE(graph.stronglyConnectedComponents().size() == 2);
}
TEST_CASE("test advanced stronglyConnectedComponents2" "[weight=1]") {
  Graph graph;
  graph.insertVertex("A");
  graph.insertVertex("B");
  graph.insertVertex("C");
  graph.insertVertex("D");
  graph.insertVertex("E");
  graph.insertVertex("F");
  graph.insertEdge("A","B");
  graph.insertEdge("B","C");
  graph.insertEdge("C","D");
  graph.insertEdge("D","E");
  REQUIRE(graph.stronglyConnectedComponents().size() == 6);
}
TEST_CASE("test advanced stronglyConnectedComponents3" "[weight=1]") {
  Graph graph;
  graph.insertVertex("A");
  graph.insertVertex("B");
  graph.insertVertex("C");
  graph.insertVertex("D");
  graph.insertVertex("E");
  graph.insertVertex("F");
  graph.insertVertex("G");
  graph.insertVertex("H");
  graph.insertVertex("I");
  graph.insertVertex("J");
  graph.insertEdge("A","C");
  graph.insertEdge("A","H");
  graph.insertEdge("B","A");
  graph.insertEdge("B","G");
  graph.insertEdge("C","D");
  graph.insertEdge("D","F");
  graph.insertEdge("E","A");
  graph.insertEdge("F","J");
  graph.insertEdge("G","I");
  graph.insertEdge("E","I");
  graph.insertEdge("I","H");
  graph.insertEdge("H","G");
  graph.insertEdge("H","F");
  graph.insertEdge("J","C");
  REQUIRE(graph.stronglyConnectedComponents().size() == 5);
}
TEST_CASE("test shortestpath" "[weight=1]") {
  Graph graph;
  graph.insertVertex("A");
  graph.insertVertex("B");
  graph.insertVertex("C");
  graph.insertVertex("D");
  graph.insertVertex("E");
  graph.insertVertex("F");
  graph.insertVertex("S");
  graph.insertEdge("A","B");
  graph.setEdgeWeight("A","B", 6);
  graph.insertEdge("A","D");
  graph.setEdgeWeight("A","D",1);
  graph.insertEdge("B","E");
  graph.setEdgeWeight("B","E",1);
  graph.insertEdge("C","A");
  graph.setEdgeWeight("C","A",2);
  graph.insertEdge("C","D");
  graph.setEdgeWeight("C","D",3);
  graph.insertEdge("D","E");
  graph.setEdgeWeight("D","E",4);
  graph.insertEdge("S","C");
  graph.setEdgeWeight("S","C",2);
  graph.insertEdge("S","A");
  graph.setEdgeWeight("S","A",3);
  graph.insertEdge("S","F");
  graph.setEdgeWeight("S","F",6);
  graph.insertEdge("F","E");
  graph.setEdgeWeight("F","E",2);
  REQUIRE(graph.shortestPath("S").at("D").distance == 4);
  REQUIRE(graph.shortestPath("F").at("E").distance == 2);
  REQUIRE(graph.shortestPath("A").at("F").distance == INT_MAX);
  REQUIRE(graph.shortestPath("C").at("E").distance == 7);
  REQUIRE(graph.shortestPath("S").at("E").distance == 8);
  REQUIRE(graph.shortestPath("A").at("E").edges.size() == 2);
  REQUIRE(graph.shortestPath("C").at("E").edges.size() == 2);
  REQUIRE(graph.shortestPath("S").at("D").edges.size() == 2);
  REQUIRE(graph.shortestPath("S").at("E").edges.size() == 3);
  REQUIRE(graph.shortestPath("S").at("E").edges.at(0).getWeight() == 3);
  REQUIRE(graph.shortestPath("S").at("E").edges.at(1).getWeight() == 1);
  REQUIRE(graph.shortestPath("S").at("E").edges.at(2).getWeight() == 4);
  REQUIRE(graph.shortestPath("A").at("E").edges.at(0).getWeight() == 1);
  REQUIRE(graph.shortestPath("A").at("E").edges.at(1).getWeight() == 4);
}
TEST_CASE("test toRadian" "[weight=1]") {
  REQUIRE(abs(toRadian(60) - 1.0471975512) <= 0.0000001);
  REQUIRE(abs(toRadian(276) - 4.8171087355) <= 0.0000001);
  REQUIRE(abs(toRadian(134) - 2.33874) <= 0.00001);
}
TEST_CASE("test calculateDistance" "[weight=1]") {
  REQUIRE(abs(calculateDistance(20,15,70,80) - 6978) <= 5);
  REQUIRE(abs(calculateDistance(43,82,87,22) - 5062) <= 5);
  REQUIRE(abs(calculateDistance(45,56,57,62) - 1397) <= 5);
}