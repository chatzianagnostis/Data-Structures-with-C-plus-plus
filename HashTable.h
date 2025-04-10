#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <list>

class HashTable {
private:
    static const int DEFAULT_SIZE = 1024;
    std::vector<std::list<int>> table;
    int count;
    
    // Hash function
    int hash(int key) const;
    
public:
    HashTable(int size = DEFAULT_SIZE);
    
    // Main operations
    int buildFromFile(const std::string& filename);
    int getSize() const;
    bool search(int key) const;
    void insert(int key);
};

#endif // HASHTABLE_H