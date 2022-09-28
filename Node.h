
#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

class Node {
private:
	string concatWords;
	int counter;
	Node* leftChild;
	Node* rightChild;
	unsigned int height;

public:
	Node();
	void setConcatWords(string);
	void setCounter(int);
	void setLeftChild(Node*);
	void setRightChild(Node*);
	void setHeight(unsigned int);

	string getConcatWords();
	int getCounter();
	Node* getLeftChild();
	Node* getRightChild();
	unsigned int getHeight();

	void makeLeftChildNull();
	void makeRightChildNull();

	template <class T> const T& max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}

};




#endif // NODE_H
