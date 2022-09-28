
#ifndef ORDERED_MAP_H
#define ORDERED_MAP_H
#define MAX_SIZE 25000000

#include <string>

using namespace std;

struct simplerNode {
public:
	string concatWord;
	int counter;
	unsigned int key;
	simplerNode(string concatWord, unsigned int key)
	{
		this->concatWord = concatWord;
		this->key = key;
		this->counter = 1;
	}
};

class OrderedMap {
public:
	simplerNode** orderedTable;
	int end;
	OrderedMap();
	void insert(string);
	int  search(string);
};


#endif// ORDERED_MAP_H
