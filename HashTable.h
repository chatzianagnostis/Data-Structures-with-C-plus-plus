
#ifndef HASH_TABLE_H
#define HAS_TABLE_H
#include <string>

#define HASH_TABLE_SIZE 25000000
using namespace std;

struct hashNode
{
public:
	unsigned int key;
	string concatWord;
	int counter;
	hashNode(unsigned int key, string concatWord, int counter)
	{
		this->key = key;
		this->concatWord = concatWord;
		this->counter = counter;
	}
};

class HashTable {
private:
	unsigned int currentLength;
	hashNode** hashTable;

public:
	HashTable();
	unsigned int hashMap(string);
	unsigned int hashFunction(unsigned int);
	void insert(string);
	int search(string);

};

#endif// HASH_TABLE_H
