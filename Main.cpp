#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include "MinHeap.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "Graph.h"
#include "HashTable.h"

using namespace std;
using namespace std::chrono;

// Function to measure execution time
template<typename Func>
std::pair<typename std::result_of<Func()>::type, long long> measureExecutionTime(Func func) {
    auto start = high_resolution_clock::now();
    auto result = func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    return std::make_pair(result, duration);
}

int main() {
    ifstream commandFile("commands.txt");
    ofstream outputFile("output.txt");
    
    if (!commandFile.is_open()) {
        cerr << "Unable to open commands.txt" << endl;
        return 1;
    }
    
    if (!outputFile.is_open()) {
        cerr << "Unable to open output.txt" << endl;
        return 1;
    }
    
    string line;
    MinHeap minHeap;
    MaxHeap maxHeap;
    AVLTree avlTree;
    Graph graph;
    HashTable hashTable;
    
    while (getline(commandFile, line)) {
        istringstream iss(line);
        string command, structure;
        iss >> command >> structure;
        
        if (command == "BUILD") {
            string filename;
            iss >> filename;
            
            if (structure == "MINHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return minHeap.buildFromFile(filename);
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MINHEAP built with " << result << " elements. (" << duration << " μs)" << endl;
            } 
            else if (structure == "MAXHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return maxHeap.buildFromFile(filename);
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MAXHEAP built with " << result << " elements. (" << duration << " μs)" << endl;
            }
            else if (structure == "AVLTREE") {
                auto result_pair = measureExecutionTime([&]() {
                    return avlTree.buildFromFile(filename);
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "AVLTREE built with " << result << " elements. (" << duration << " μs)" << endl;
            }
            else if (structure == "GRAPH") {
                auto result_pair = measureExecutionTime([&]() {
                    return graph.buildFromFile(filename);
                });
                auto vertices_edges = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "GRAPH built with " << vertices_edges.first << " vertices and " 
                         << vertices_edges.second << " edges. (" << duration << " μs)" << endl;
            }
            else if (structure == "HASHTABLE") {
                auto result_pair = measureExecutionTime([&]() {
                    return hashTable.buildFromFile(filename);
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "HASHTABLE built with " << result << " elements. (" << duration << " μs)" << endl;
            }
        }
        else if (command == "GETSIZE") {
            if (structure == "MINHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return minHeap.getSize();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MINHEAP size: " << result << " (" << duration << " μs)" << endl;
            }
            else if (structure == "MAXHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return maxHeap.getSize();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MAXHEAP size: " << result << " (" << duration << " μs)" << endl;
            }
            else if (structure == "AVLTREE") {
                auto result_pair = measureExecutionTime([&]() {
                    return avlTree.getSize();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "AVLTREE size: " << result << " (" << duration << " μs)" << endl;
            }
            else if (structure == "GRAPH") {
                auto result_pair = measureExecutionTime([&]() {
                    return graph.getSize();
                });
                auto vertices_edges = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "GRAPH vertices: " << vertices_edges.first << ", edges: " << vertices_edges.second 
                         << " (" << duration << " μs)" << endl;
            }
            else if (structure == "HASHTABLE") {
                auto result_pair = measureExecutionTime([&]() {
                    return hashTable.getSize();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "HASHTABLE size: " << result << " (" << duration << " μs)" << endl;
            }
        }
        else if (command == "FINDMIN") {
            if (structure == "MINHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return minHeap.findMin();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MINHEAP min element: " << result << " (" << duration << " μs)" << endl;
            }
            else if (structure == "AVLTREE") {
                auto result_pair = measureExecutionTime([&]() {
                    return avlTree.findMin();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "AVLTREE min element: " << result << " (" << duration << " μs)" << endl;
            }
        }
        else if (command == "FINDMAX") {
            if (structure == "MAXHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return maxHeap.findMax();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MAXHEAP max element: " << result << " (" << duration << " μs)" << endl;
            }
        }
        else if (command == "SEARCH") {
            int number;
            iss >> number;
            
            if (structure == "AVLTREE") {
                auto result_pair = measureExecutionTime([&]() {
                    return avlTree.search(number);
                });
                bool result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "AVLTREE search " << number << ": " << (result ? "SUCCESS" : "FAILURE") 
                         << " (" << duration << " μs)" << endl;
            }
            else if (structure == "HASHTABLE") {
                auto result_pair = measureExecutionTime([&]() {
                    return hashTable.search(number);
                });
                bool result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "HASHTABLE search " << number << ": " << (result ? "SUCCESS" : "FAILURE") 
                         << " (" << duration << " μs)" << endl;
            }
        }
        else if (command == "COMPUTESHORTESTPATH") {
            int node1, node2;
            iss >> node1 >> node2;
            
            auto result_pair = measureExecutionTime([&]() {
                return graph.computeShortestPath(node1, node2);
            });
            int result = result_pair.first;
            long long duration = result_pair.second;
            outputFile << "GRAPH shortest path from " << node1 << " to " << node2 << ": " 
                     << result << " (" << duration << " μs)" << endl;
        }
        else if (command == "COMPUTESPANNINGTREE") {
            auto result_pair = measureExecutionTime([&]() {
                return graph.computeSpanningTree();
            });
            int result = result_pair.first;
            long long duration = result_pair.second;
            outputFile << "GRAPH minimum spanning tree cost: " << result << " (" << duration << " μs)" << endl;
        }
        else if (command == "FINDCONNECTEDCOMPONENTS") {
            auto result_pair = measureExecutionTime([&]() {
                return graph.findConnectedComponents();
            });
            int result = result_pair.first;
            long long duration = result_pair.second;
            outputFile << "GRAPH connected components: " << result << " (" << duration << " μs)" << endl;
        }
        else if (command == "INSERT") {
            int number;
            iss >> number;
            
            if (structure == "MINHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    minHeap.insert(number);
                    return 0;
                });
                long long duration = result_pair.second;
                outputFile << "MINHEAP inserted " << number << " (" << duration << " μs)" << endl;
            }
            else if (structure == "MAXHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    maxHeap.insert(number);
                    return 0;
                });
                long long duration = result_pair.second;
                outputFile << "MAXHEAP inserted " << number << " (" << duration << " μs)" << endl;
            }
            else if (structure == "AVLTREE") {
                auto result_pair = measureExecutionTime([&]() {
                    avlTree.insert(number);
                    return 0;
                });
                long long duration = result_pair.second;
                outputFile << "AVLTREE inserted " << number << " (" << duration << " μs)" << endl;
            }
            else if (structure == "HASHTABLE") {
                auto result_pair = measureExecutionTime([&]() {
                    hashTable.insert(number);
                    return 0;
                });
                long long duration = result_pair.second;
                outputFile << "HASHTABLE inserted " << number << " (" << duration << " μs)" << endl;
            }
            else if (structure == "GRAPH") {
                int node1 = number;
                int node2, weight;
                iss >> node2 >> weight;
                
                auto result_pair = measureExecutionTime([&]() {
                    graph.insertEdge(node1, node2, weight);
                    return 0;
                });
                long long duration = result_pair.second;
                outputFile << "GRAPH inserted edge " << node1 << " -- " << node2 
                         << " with weight " << weight << " (" << duration << " μs)" << endl;
            }
        }
        else if (command == "DELETEMIN") {
            if (structure == "MINHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return minHeap.deleteMin();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MINHEAP deleted min: " << result << " (" << duration << " μs)" << endl;
            }
        }
        else if (command == "DELETEMAX") {
            if (structure == "MAXHEAP") {
                auto result_pair = measureExecutionTime([&]() {
                    return maxHeap.deleteMax();
                });
                int result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "MAXHEAP deleted max: " << result << " (" << duration << " μs)" << endl;
            }
        }
        else if (command == "DELETE") {
            int number;
            iss >> number;
            
            if (structure == "AVLTREE") {
                auto result_pair = measureExecutionTime([&]() {
                    return avlTree.remove(number);
                });
                bool result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "AVLTREE deleted " << number << ": " << (result ? "SUCCESS" : "FAILURE") 
                         << " (" << duration << " μs)" << endl;
            }
            else if (structure == "GRAPH") {
                int node1 = number;
                int node2;
                iss >> node2;
                
                auto result_pair = measureExecutionTime([&]() {
                    return graph.removeEdge(node1, node2);
                });
                bool result = result_pair.first;
                long long duration = result_pair.second;
                outputFile << "GRAPH deleted edge " << node1 << " -- " << node2 << ": " 
                         << (result ? "SUCCESS" : "FAILURE") << " (" << duration << " μs)" << endl;
            }
        }
    }
    
    commandFile.close();
    outputFile.close();
    
    return 0;
}