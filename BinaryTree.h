#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"

class BinaryTree {
protected:
	Node* root;

public:
	BinaryTree();

	void setRoot(Node*);
	Node* getRoot();
	void insert(string concatWord, Node* root);
	int search(string concatWord, Node* root);
};

#endif// BINARYTREE_H
