#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

class Graph {
private:
    // Adjacency list representation
    // Map vertex -> list of (neighbor, weight) pairs
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;
    int numEdges;
    
    // Helper functions
    void dfs(int vertex, std::unordered_map<int, bool>& visited);
    
public:
    Graph();
    
    // Main operations
    std::pair<int, int> buildFromFile(const std::string& filename);
    std::pair<int, int> getSize() const;
    int computeShortestPath(int source, int target);
    int computeSpanningTree();
    int findConnectedComponents();
    void insertEdge(int u, int v, int weight);
    bool removeEdge(int u, int v);
};

#endif // GRAPH_H