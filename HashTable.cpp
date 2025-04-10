#include "HashTable.h"
#include <fstream>
#include <stdexcept>

HashTable::HashTable(int size) : table(size), count(0) {}

// Hash function
int HashTable::hash(int key) const {
    return key % table.size();
}

// Build hash table from file
int HashTable::buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    
    // Clear existing hash table
    for (auto& list : table) {
        list.clear();
    }
    count = 0;
    
    // Read numbers and insert into hash table
    int number;
    while (file >> number) {
        insert(number);
    }
    
    file.close();
    return count;
}

// Get size of hash table
int HashTable::getSize() const {
    return count;
}

// Search for a key
bool HashTable::search(int key) const {
    int index = hash(key);
    const std::list<int>& list = table[index];
    
    for (int value : list) {
        if (value == key) {
            return true;
        }
    }
    
    return false;
}

// Insert a key
void HashTable::insert(int key) {
    // Check if key already exists
    if (search(key)) {
        return;
    }
    
    int index = hash(key);
    table[index].push_back(key);
    count++;
}