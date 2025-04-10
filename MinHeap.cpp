#include "MinHeap.h"
#include <fstream>
#include <stdexcept>

MinHeap::MinHeap() {}

// Build heap from file
int MinHeap::buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    
    // Clear existing heap
    heap.clear();
    
    // Read numbers from file
    int number;
    while (file >> number) {
        heap.push_back(number);
    }
    
    // Heapify the array
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
    
    file.close();
    return heap.size();
}

// Get size of heap
int MinHeap::getSize() const {
    return heap.size();
}

// Find minimum element
int MinHeap::findMin() const {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}

// Insert element into heap
void MinHeap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

// Delete minimum element
int MinHeap::deleteMin() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    
    int minValue = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    
    return minValue;
}

// Heapify up (used after insert)
void MinHeap::heapifyUp(int index) {
    if (index == 0) return;
    
    int parentIndex = parent(index);
    if (heap[parentIndex] > heap[index]) {
        std::swap(heap[parentIndex], heap[index]);
        heapifyUp(parentIndex);
    }
}

// Heapify down (used for building heap and after delete)
void MinHeap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    int size = heap.size();
    
    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}