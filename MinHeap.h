#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <string>

class MinHeap {
private:
    std::vector<int> heap;
    
    // Helper functions
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    
public:
    MinHeap();
    
    // Main operations
    int buildFromFile(const std::string& filename);
    int getSize() const;
    int findMin() const;
    void insert(int value);
    int deleteMin();
};

#endif // MINHEAP_H