#include "MaxHeap.h"
#include <fstream>
#include <stdexcept>

MaxHeap::MaxHeap() {}

// Build heap from file
int MaxHeap::buildFromFile(const std::string& filename) {
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
int MaxHeap::getSize() const {
    return heap.size();
}

// Find maximum element
int MaxHeap::findMax() const {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}

// Insert element into heap
void MaxHeap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

// Delete maximum element
int MaxHeap::deleteMax() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    
    int maxValue = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    
    return maxValue;
}

// Heapify up (used after insert)
void MaxHeap::heapifyUp(int index) {
    if (index == 0) return;
    
    int parentIndex = parent(index);
    if (heap[parentIndex] < heap[index]) {
        std::swap(heap[parentIndex], heap[index]);
        heapifyUp(parentIndex);
    }
}

// Heapify down (used for building heap and after delete)
void MaxHeap::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    int size = heap.size();
    
    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }
    
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }
    
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}