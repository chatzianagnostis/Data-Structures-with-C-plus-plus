
#include "HashTable.h"

using namespace std;

HashTable::HashTable()
{
    currentLength = 0;
    hashTable = new hashNode * [HASH_TABLE_SIZE];
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hashTable[i] = nullptr;
    }
}

unsigned int HashTable::hashMap(string concatWord)
{
    int certainConstant = 5;
    unsigned int hashKey = 0;
    for (int i = 0; i < concatWord.length(); i++)
    {
        hashKey = certainConstant * hashKey + concatWord.at(i);
    }
    return hashKey;
}

unsigned int HashTable::hashFunction(unsigned int hashKey)
{
    return hashKey % HASH_TABLE_SIZE;
}

void HashTable::insert(string concatWord)
{
    unsigned int certainKey = hashMap(concatWord);
    unsigned int hashKey = hashFunction(certainKey);
    while (hashTable[hashKey] != nullptr)
    {
        if (hashTable[hashKey]->key == certainKey && (hashTable[hashKey]->concatWord == concatWord))
        {
            hashTable[hashKey]->counter = hashTable[hashKey]->counter + 1;
            return;
        }
        hashKey = (hashKey + 1) % HASH_TABLE_SIZE;
    }
    hashTable[hashKey] = new hashNode(certainKey, concatWord, 1);
    currentLength++;
}

int HashTable::search(string concatWord)
{
    unsigned int certainKey = hashMap(concatWord);
    unsigned int hashKey = hashFunction(certainKey);

    while (hashTable[hashKey] != nullptr && hashTable[hashKey]->key != certainKey)
    {
        hashKey = (hashKey + 1) % HASH_TABLE_SIZE;
    }
    if (hashTable[hashKey] == nullptr)
        return 0;
    return hashTable[hashKey]->counter;
}
