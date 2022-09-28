#include "UnorderedTable.h"

static int counterFill = 1;


UnorderedTable::UnorderedTable()
{
    end = 0;
    unorderedTable = new simpleNode2 * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        unorderedTable[i] = nullptr;
}

void UnorderedTable::insert(string concatWord)
{
    for (int i = 0; i < end; i++)
    {
        if (unorderedTable[i]->concatWord == concatWord)
        {
            unorderedTable[i]->counter = unorderedTable[i]->counter + 1;
            return;
        }
    }
    if (end < MAX_SIZE)
    {
        simpleNode2* newNode = new simpleNode2(concatWord);
        unorderedTable[end] = newNode;
        end = end + 1;
        return;
    }
    if (counterFill * MAX_SIZE == end)
    {
        counterFill = counterFill + 1;
        simpleNode2** newMatrix = new simpleNode2 * [counterFill * MAX_SIZE];
        for (int i = 0; i < end; i++)
        {
            newMatrix[i] = unorderedTable[i];
        }
        newMatrix[end] = new simpleNode2(concatWord);
        unorderedTable = newMatrix;
        end = end + 1;
        return;
    }
}

int UnorderedTable::search(string concatWord)
{
    for (int i = 0; i < end; i++)
    {
        if (unorderedTable[i]->concatWord == concatWord)
        {
            return unorderedTable[i]->counter;
        }
    }
    return 0;
}

