#include "Graph.h"
#include <fstream>
#include <stdexcept>
#include <queue>
#include <algorithm>
#include <limits>
#include <set>

Graph::Graph() : numEdges(0) {}

// Build graph from file
std::pair<int, int> Graph::buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    
    // Clear existing graph
    adjList.clear();
    numEdges = 0;
    
    // Read edges from file
    int u, v, weight;
    while (file >> u >> v >> weight) {
        insertEdge(u, v, weight);
    }
    
    file.close();
    return std::make_pair(adjList.size(), numEdges);
}

// Get size of graph (vertices and edges)
std::pair<int, int> Graph::getSize() const {
    return std::make_pair(adjList.size(), numEdges);
}

// Insert edge
void Graph::insertEdge(int u, int v, int weight) {
    // Check if edge already exists
    bool edgeExists = false;
    for (auto& pair : adjList[u]) {
        if (pair.first == v) {
            edgeExists = true;
            pair.second = weight; // Update weight if edge exists
            break;
        }
    }
    
    if (!edgeExists) {
        // Add edge in both directions (undirected graph)
        adjList[u].push_back(std::make_pair(v, weight));
        adjList[v].push_back(std::make_pair(u, weight));
        numEdges++;
    }
}

// Remove edge
bool Graph::removeEdge(int u, int v) {
    // Check if vertices exist
    if (adjList.find(u) == adjList.end() || adjList.find(v) == adjList.end()) {
        return false;
    }
    
    // Find and remove edge from u to v
    bool found = false;
    auto& adjU = adjList[u];
    for (auto it = adjU.begin(); it != adjU.end(); ++it) {
        if (it->first == v) {
            adjU.erase(it);
            found = true;
            break;
        }
    }
    
    // If edge was found, also remove edge from v to u
    if (found) {
        auto& adjV = adjList[v];
        for (auto it = adjV.begin(); it != adjV.end(); ++it) {
            if (it->first == u) {
                adjV.erase(it);
                break;
            }
        }
        numEdges--;
    }
    
    return found;
}

// Compute shortest path using Dijkstra's algorithm
int Graph::computeShortestPath(int source, int target) {
    // Check if vertices exist
    if (adjList.find(source) == adjList.end() || adjList.find(target) == adjList.end()) {
        return -1; // Vertices don't exist
    }
    
    const int INF = std::numeric_limits<int>::max();
    std::unordered_map<int, int> dist;  // Map vertex -> distance from source
    
    // Initialize distances
    for (const auto& pair : adjList) {
        dist[pair.first] = INF;
    }
    dist[source] = 0;
    
    // Priority queue for Dijkstra's algorithm
    // pair: (distance, vertex)
    std::priority_queue<std::pair<int, int>, 
                         std::vector<std::pair<int, int>>, 
                         std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, source));
    
    // Dijkstra's algorithm
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        // Found target
        if (u == target) {
            return d;
        }
        
        // Skip if we've found a better path already
        if (d > dist[u]) {
            continue;
        }
        
        // Explore neighbors
        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            // Relaxation
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
    
    // If target is not reachable
    return -1;
}

// Compute minimum spanning tree using Prim's algorithm
int Graph::computeSpanningTree() {
    if (adjList.empty()) {
        return 0;
    }
    
    const int INF = std::numeric_limits<int>::max();
    int totalWeight = 0;
    std::unordered_map<int, bool> inMST;
    std::unordered_map<int, int> key;
    
    // Initialize keys and inMST
    for (const auto& pair : adjList) {
        key[pair.first] = INF;
        inMST[pair.first] = false;
    }
    
    // Start with any vertex
    int start = adjList.begin()->first;
    key[start] = 0;
    
    // Priority queue for Prim's algorithm
    // pair: (key, vertex)
    std::priority_queue<std::pair<int, int>, 
                         std::vector<std::pair<int, int>>, 
                         std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, start));
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        // Skip if already in MST
        if (inMST[u]) {
            continue;
        }
        
        // Add to MST
        inMST[u] = true;
        totalWeight += key[u];
        
        // Update keys of adjacent vertices
        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
            }
        }
    }
    
    // Check if MST connects all vertices
    for (const auto& pair : inMST) {
        if (!pair.second) {
            // Graph is not connected
            return -1;
        }
    }
    
    return totalWeight;
}

// Helper function for DFS
void Graph::dfs(int vertex, std::unordered_map<int, bool>& visited) {
    visited[vertex] = true;
    
    for (const auto& neighbor : adjList[vertex]) {
        if (!visited[neighbor.first]) {
            dfs(neighbor.first, visited);
        }
    }
}

// Find number of connected components
int Graph::findConnectedComponents() {
    std::unordered_map<int, bool> visited;
    
    // Initialize visited map
    for (const auto& pair : adjList) {
        visited[pair.first] = false;
    }
    
    int count = 0;
    
    // Perform DFS from each unvisited vertex
    for (const auto& pair : adjList) {
        int vertex = pair.first;
        if (!visited[vertex]) {
            dfs(vertex, visited);
            count++;
        }
    }
    
    return count;
}