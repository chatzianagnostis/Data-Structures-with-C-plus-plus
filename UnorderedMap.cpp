
#include "UnorderedMap.h"

using namespace std;
UnorderedMap::UnorderedMap()
{
    unorderedTable = new simpleNode * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        unorderedTable[i] = nullptr;
}

void UnorderedMap::insert(string concatWord)
{
    unsigned int key = 0;
    int certainConstant = 5;
    for (unsigned int i = 0; i < concatWord.length(); i++)
    {
        key = certainConstant * key + concatWord.at(i);
    }
    key = key % MAX_SIZE;
    if (unorderedTable[key] == nullptr)
    {
        unorderedTable[key] = new simpleNode(concatWord);
    }
    else
    {
        if (unorderedTable[key]->concatWord == concatWord)
        {
            unorderedTable[key]->counter = unorderedTable[key]->counter + 1;
            return;
        }
        simpleNode* currentNode = unorderedTable[key];
        while (currentNode->next != nullptr)
        {
            if (currentNode->concatWord == concatWord)
            {
                currentNode->counter = currentNode->counter + 1;
                return;
            }
            currentNode = currentNode->next;
        }
        currentNode->next = new simpleNode(concatWord);
    }
}

int UnorderedMap::search(string concatWord)
{
    unsigned int key = 0;
    int certainConstant = 5;
    for (unsigned int i = 0; i < concatWord.length(); i++)
    {
        key = certainConstant * key + concatWord.at(i);
    }
    key = key % MAX_SIZE;

    if (unorderedTable[key] == nullptr)
    {
        return 0;
    }
    else
    {
        simpleNode* currentNode = unorderedTable[key];
        while (currentNode != nullptr)
        {
            if (currentNode->concatWord == concatWord)
            {
                return currentNode->counter;
            }
            currentNode = currentNode->next;
        }
        return 0;
    }

}
