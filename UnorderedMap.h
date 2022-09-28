
#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H
#define MAX_SIZE 25000000

#include <string>

using namespace std;

struct simpleNode {
public:
	string concatWord;
	int counter;
	simpleNode* next;
	simpleNode(string concatWord)
	{
		this->concatWord = concatWord;
		this->counter = 1;
		this->next = nullptr;
	}
};

class UnorderedMap {
private:
	simpleNode** unorderedTable;
public:
	UnorderedMap();
	void insert(string);
	int  search(string);

};


#endif// UNORDERED_MAP_H
