#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

// AVL Tree Node
struct AVLNode {
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    int size;
    
    // Helper functions
    int height(AVLNode* node) const;
    int getBalance(AVLNode* node) const;
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insertNode(AVLNode* node, int value);
    AVLNode* minValueNode(AVLNode* node) const;
    AVLNode* deleteNode(AVLNode* root, int value, bool& success);
    void clearTree(AVLNode* node);
    bool searchNode(AVLNode* node, int value) const;
    void countNodes(AVLNode* node, int& count) const;
    
public:
    AVLTree();
    ~AVLTree();
    
    // Main operations
    int buildFromFile(const std::string& filename);
    int getSize() const;
    int findMin() const;
    bool search(int value) const;
    void insert(int value);
    bool remove(int value);
};

#endif // AVLTREE_H