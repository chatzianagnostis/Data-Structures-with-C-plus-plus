
#include "AVL.h"

AVL::AVL()
{
    root = nullptr;
}

void AVL::insert(string concatWord, Node* root)
{
    int balanceFactor;
    BinaryTree::insert(concatWord, root);
    balanceFactor = balance(root);

    if (balanceFactor < -1 && concatWord < (root->getRightChild())->getConcatWords())
    {
        root->setRightChild(rightRotation(root->getRightChild()));
        leftRotation(root);
    }
    else if (balanceFactor < -1 && concatWord >(root->getRightChild())->getConcatWords())
    {
        leftRotation(root);
    }
    else if (balanceFactor > 1 && concatWord < (root->getLeftChild())->getConcatWords())
    {
        rightRotation(root);
    }
    else if (balanceFactor > 1 && concatWord > (root->getLeftChild())->getConcatWords())
    {
        root->setLeftChild(leftRotation(root->getLeftChild()));
        rightRotation(root);
    }

}

int AVL::balance(Node* root)
{
    if (root == nullptr || (root->getLeftChild() == nullptr && root->getLeftChild()))
        return 0;
    if (root->getLeftChild() == nullptr)
        return (-1) * root->getRightChild()->getHeight();
    if (root->getRightChild() == nullptr)
        return root->getLeftChild()->getHeight();

    return root->getLeftChild()->getHeight() - root->getRightChild()->getHeight();
}

Node* AVL::leftRotation(Node* root)
{
    Node* right = root->getRightChild();
    Node* left = right->getLeftChild();

    right->setLeftChild(root);
    root->setRightChild(left);

    root->setHeight(max(root->getLeftChild()->getHeight(), root->getRightChild()->getHeight()) + 1);
    right->setHeight(max(right->getLeftChild()->getHeight(), right->getRightChild()->getHeight()) + 1);
    return right;
}

Node* AVL::rightRotation(Node*)
{
    Node* left = root->getLeftChild();
    Node* right = left->getRightChild();

    left->setRightChild(root);
    root->setLeftChild(right);

    root->setHeight(max(root->getLeftChild()->getHeight(), root->getRightChild()->getHeight()) + 1);
    left->setHeight(max(left->getLeftChild()->getHeight(), left->getRightChild()->getHeight()) + 1);
    return left;
}


