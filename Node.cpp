
#include "Node.h"

Node::Node()
{
    counter = 1;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 1;
}

void Node::setConcatWords(string concatWords)
{
    this->concatWords = concatWords;
}

void Node::setCounter(int counter)
{
    this->counter = counter;
}


void Node::setLeftChild(Node* leftChild)
{
    this->leftChild = leftChild;
}

void Node::setRightChild(Node* rightChild)
{
    this->rightChild = rightChild;
}

void Node::setHeight(unsigned int height)
{
    this->height = height;
}

string Node::getConcatWords()
{
    return concatWords;
}

int Node::getCounter()
{
    return counter;
}

Node* Node::getLeftChild()
{
    return leftChild;
}

Node* Node::getRightChild()
{
    return rightChild;
}

unsigned int Node::getHeight()
{
    return height;
}


void Node::makeLeftChildNull()
{
    leftChild = nullptr;
}

void Node::makeRightChildNull()
{
    rightChild = nullptr;
}
