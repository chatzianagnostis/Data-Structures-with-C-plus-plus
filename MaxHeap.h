#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <string>

class MaxHeap {
private:
    std::vector<int> heap;
    
    // Helper functions
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    
public:
    MaxHeap();
    
    // Main operations
    int buildFromFile(const std::string& filename);
    int getSize() const;
    int findMax() const;
    void insert(int value);
    int deleteMax();
};

#endif // MAXHEAP_H