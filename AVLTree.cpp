#include "AVLTree.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

AVLTree::AVLTree() : root(nullptr), size(0) {}

AVLTree::~AVLTree() {
    clearTree(root);
}

void AVLTree::clearTree(AVLNode* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

// Get height of a node (nullptr returns 0)
int AVLTree::height(AVLNode* node) const {
    if (node == nullptr) return 0;
    return node->height;
}

// Get balance factor of a node
int AVLTree::getBalance(AVLNode* node) const {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Right rotation
AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    
    // Return new root
    return x;
}

// Left rotation
AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    
    // Return new root
    return y;
}

// Insert a node in AVL tree
AVLNode* AVLTree::insertNode(AVLNode* node, int value) {
    // 1. Perform standard BST insert
    if (node == nullptr) {
        size++;
        return new AVLNode(value);
    }
    
    if (value < node->value)
        node->left = insertNode(node->left, value);
    else if (value > node->value)
        node->right = insertNode(node->right, value);
    else // Equal values not allowed
        return node;
    
    // 2. Update height of this ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));
    
    // 3. Get the balance factor of this ancestor node
    int balance = getBalance(node);
    
    // Left Left Case
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);
    
    // Right Right Case
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // Return unchanged node pointer
    return node;
}

// Find node with minimum value
AVLNode* AVLTree::minValueNode(AVLNode* node) const {
    AVLNode* current = node;
    
    // Loop to find the leftmost leaf
    while (current && current->left != nullptr)
        current = current->left;
    
    return current;
}

// Delete a node from AVL tree
AVLNode* AVLTree::deleteNode(AVLNode* node, int value, bool& success) {
    // Standard BST delete
    if (node == nullptr) {
        success = false;
        return nullptr;
    }
    
    if (value < node->value)
        node->left = deleteNode(node->left, value, success);
    else if (value > node->value)
        node->right = deleteNode(node->right, value, success);
    else {
        // Node found, delete it
        success = true;
        size--;
        
        // Node with only one child or no child
        if (node->left == nullptr) {
            AVLNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            AVLNode* temp = node->left;
            delete node;
            return temp;
        }
        
        // Node with two children
        AVLNode* temp = minValueNode(node->right);
        
        // Copy the inorder successor's data to this node
        node->value = temp->value;
        
        // Delete the inorder successor
        bool dummySuccess;
        node->right = deleteNode(node->right, temp->value, dummySuccess);
    }
    
    // If tree had only one node then return
    if (node == nullptr)
        return node;
    
    // Update height of the current node
    node->height = 1 + std::max(height(node->left), height(node->right));
    
    // Get the balance factor
    int balance = getBalance(node);
    
    // If unbalanced, handle the four cases
    
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
    
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);
    
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

// Search for a value in the tree
bool AVLTree::searchNode(AVLNode* node, int value) const {
    if (node == nullptr)
        return false;
    
    if (value == node->value)
        return true;
    
    if (value < node->value)
        return searchNode(node->left, value);
    else
        return searchNode(node->right, value);
}

// Count nodes in the tree
void AVLTree::countNodes(AVLNode* node, int& count) const {
    if (node) {
        count++;
        countNodes(node->left, count);
        countNodes(node->right, count);
    }
}

// Build tree from file
int AVLTree::buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    
    // Clear existing tree
    clearTree(root);
    root = nullptr;
    size = 0;
    
    // Read numbers and insert into tree
    int number;
    while (file >> number) {
        insert(number);
    }
    
    file.close();
    return size;
}

// Get size of tree
int AVLTree::getSize() const {
    return size;
}

// Find minimum value in tree
int AVLTree::findMin() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    
    AVLNode* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    
    return current->value;
}

// Search for a value
bool AVLTree::search(int value) const {
    return searchNode(root, value);
}

// Insert a value
void AVLTree::insert(int value) {
    root = insertNode(root, value);
}

// Remove a value
bool AVLTree::remove(int value) {
    bool success = false;
    root = deleteNode(root, value, success);
    return success;
}