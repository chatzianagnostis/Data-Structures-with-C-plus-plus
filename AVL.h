
#ifndef AVL_H
#define AVL_H

#include "BinaryTree.h"

class AVL : public BinaryTree {

public:
	AVL();
	void insert(string, Node*);
	int balance(Node*);
	Node* leftRotation(Node*);
	Node* rightRotation(Node*);
};

#endif// AVL_H
