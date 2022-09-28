
#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	root = nullptr;
}


void BinaryTree::setRoot(Node* root)
{
	this->root = root;
}

Node* BinaryTree::getRoot()
{
	return root;
}

void BinaryTree::insert(string concatWord, Node* root)
{
	if (root == nullptr)
	{
		root = new Node;
		root->setConcatWords(concatWord);
		root->makeLeftChildNull();
		root->makeRightChildNull();
		setRoot(root);
	}

	else {

		if (concatWord < root->getConcatWords())
		{
			if (root->getLeftChild() != nullptr)
			{
				insert(concatWord, root->getLeftChild());
			}
			else
			{
				Node* temp = new Node;
				temp->setConcatWords(concatWord);
				temp->makeLeftChildNull();
				temp->makeRightChildNull();
				root->setLeftChild(temp);

			}
		}

		else if (concatWord > root->getConcatWords())
		{
			if (root->getRightChild() != nullptr)
			{
				insert(concatWord, root->getRightChild());
			}
			else
			{
				Node* temp = new Node;
				temp->setConcatWords(concatWord);
				temp->makeLeftChildNull();
				temp->makeRightChildNull();
				root->setRightChild(temp);
			}
		}

		else
		{
			root->setCounter(root->getCounter() + 1);
		}
	}
}

int BinaryTree::search(string concatWord, Node* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	if (root->getConcatWords() == concatWord)
	{
		return root->getCounter();
	}
	if (concatWord > root->getConcatWords())
	{
		return search(concatWord, root->getRightChild());
	}
	else
	{
		return search(concatWord, root->getLeftChild());
	}
}
