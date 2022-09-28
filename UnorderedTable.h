
#ifndef UNORDERED_TABLE_H
#define UNORDERED_TABLE_H
#define MAX_SIZE 25000000

#include <string>

using namespace std;

struct simpleNode2 {
public:
	string concatWord;
	int counter;
	simpleNode2(string concatWord)
	{
		this->concatWord = concatWord;
		this->counter = 1;
	}
};

class UnorderedTable {

public:
	simpleNode2** unorderedTable;
	int end;
	UnorderedTable();
	void insert(string);
	int  search(string);

};


#endif// UNORDERED_TABLE_H
