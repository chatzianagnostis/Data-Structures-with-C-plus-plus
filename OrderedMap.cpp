
#include "OrderedMap.h"

static int counterFill = 1;

OrderedMap::OrderedMap()
{
    orderedTable = new simplerNode * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        orderedTable[i] = nullptr;
    end = 0;
}

void OrderedMap::insert(string concatWord)
{
    unsigned int key = 0;
    int certainConstant = 5;
    for (int i = 0; i < concatWord.length(); i++)
    {
        key = certainConstant * key + concatWord.at(i);
    }

    if (end == 0)
    {
        orderedTable[end] = new simplerNode(concatWord, key);
        end = end + 1;
        return;
    }
    int tempStart = 0;
    int tempEnd = end - 1;
    int tempMiddle = (tempStart + tempEnd) / 2;

    while (tempEnd - tempStart > 1)
    {
        if (orderedTable[tempMiddle]->concatWord == concatWord)
        {
            orderedTable[tempMiddle]->counter = orderedTable[tempMiddle]->counter + 1;
            return;
        }
        if (orderedTable[tempMiddle]->concatWord < concatWord)
        {
            tempStart = tempMiddle + 1;
        }
        else
        {
            tempEnd = tempMiddle;
        }
        tempMiddle = (tempStart + tempEnd) / 2;
    }

    simplerNode* newOne = new simplerNode(concatWord, key);


    if (counterFill * MAX_SIZE == end)
    {
        if (orderedTable[tempEnd]->concatWord == concatWord)
        {
            orderedTable[tempEnd]->counter = orderedTable[tempEnd]->counter + 1;
            return;
        }

        if (orderedTable[tempStart]->concatWord == concatWord)
        {
            orderedTable[tempStart]->counter = orderedTable[tempStart]->counter + 1;
            return;
        }

        counterFill = counterFill + 1;
        simplerNode** newMatrix = new simplerNode * [counterFill * MAX_SIZE];


        if (orderedTable[tempEnd]->concatWord < concatWord)
        {
            for (int i = 0; i < tempEnd + 1; i++)
            {
                newMatrix[i] = orderedTable[i];
            }
            newMatrix[tempEnd + 1] = newOne;
            for (int i = end; i > tempEnd + 1; i--)
            {
                newMatrix[i] = orderedTable[i - 1];
            }
            end = end + 1;
            this->orderedTable = newMatrix;
            return;
        }

        if (orderedTable[tempStart]->concatWord > concatWord)
        {
            for (int i = 0; i < tempStart; i++)
            {
                newMatrix[i] = orderedTable[i];
            }
            newMatrix[tempStart] = newOne;
            for (int i = end; i > tempStart; i--)
            {
                newMatrix[i] = orderedTable[i - 1];
            }
            end = end + 1;
            this->orderedTable = newMatrix;
            return;
        }
        else if (orderedTable[tempStart]->concatWord < concatWord)
        {
            for (int i = 0; i < tempStart + 1; i++)
            {
                newMatrix[i] = orderedTable[i];
            }
            newMatrix[tempStart + 1] = newOne;
            for (int i = end; i > tempStart + 1; i--)
            {
                newMatrix[i] = orderedTable[i - 1];
            }
            end = end + 1;
            this->orderedTable = newMatrix;
            return;
        }

        if (orderedTable[tempEnd]->key < key)
        {
            for (int i = 0; i < tempEnd + 1; i++)
            {
                newMatrix[i] = orderedTable[i];
            }
            newMatrix[tempEnd + 1] = newOne;
            for (int i = tempEnd + 1; i < end; i++)
            {
                newMatrix[i + 1] = orderedTable[i];
            }
            for (int i = end + 1; i < counterFill * MAX_SIZE; i++)
            {
                newMatrix[i] = nullptr;
            }
            end = end + 1;
            this->orderedTable = newMatrix;
            return;
        }
        else
        {
            for (int i = 0; i < tempEnd; i++)
            {
                newMatrix[i] = orderedTable[i];
            }
            newMatrix[tempEnd] = newOne;
            for (int i = tempEnd; i < end; i++)
            {
                newMatrix[i + 1] = orderedTable[i];
            }
            for (int i = end + 1; i < counterFill * MAX_SIZE; i++)
            {
                newMatrix[i] = nullptr;
            }
            orderedTable = newMatrix;
            end = end + 1;
            this->orderedTable = newMatrix;
            return;
        }
    }

    if (tempEnd - tempStart == 1)
    {
        if (orderedTable[tempStart]->key == key)
        {
            orderedTable[tempStart]->counter = orderedTable[tempStart]->counter + 1;
            return;
        }
        else if (orderedTable[tempEnd] != nullptr)
        {
            if (orderedTable[tempEnd]->key == key)
            {
                orderedTable[tempEnd]->counter = orderedTable[tempEnd]->counter + 1;
                return;
            }
        }
        else if (orderedTable[tempStart]->key > key)
        {
            for (int i = end; i > tempStart; i--)
            {
                orderedTable[i] = orderedTable[i - 1];
            }
            orderedTable[tempStart] = newOne;
            end = end + 1;
            return;
        }
        else
        {
            for (int i = end; i > tempStart + 1; i--)
            {
                orderedTable[i] = orderedTable[i - 1];
            }
            orderedTable[tempStart + 1] = newOne;
            end = end + 1;
            return;
        }
    }


    if (orderedTable[tempEnd]->concatWord == concatWord)
    {
        orderedTable[tempEnd]->counter = orderedTable[tempEnd]->counter + 1;
        return;
    }

    if (orderedTable[tempStart]->concatWord == concatWord)
    {
        orderedTable[tempStart]->counter = orderedTable[tempStart]->counter + 1;
        return;
    }

    if (orderedTable[tempEnd]->concatWord < concatWord)
    {
        for (int i = end; i > tempEnd + 1; i--)
        {
            orderedTable[i] = orderedTable[i - 1];
        }
        orderedTable[tempEnd + 1] = newOne;
        end = end + 1;
        return;
    }

    if (orderedTable[tempStart]->concatWord > concatWord)
    {
        for (int i = end; i > tempStart; i--)
        {
            orderedTable[i] = orderedTable[i - 1];
        }
        orderedTable[tempStart] = newOne;
        end = end + 1;
        return;
    }
    else if (orderedTable[tempStart]->concatWord < concatWord)
    {
        for (int i = end; i > tempStart + 1; i--)
        {
            orderedTable[i] = orderedTable[i - 1];
        }
        orderedTable[tempStart + 1] = newOne;
        end = end + 1;
        return;
    }

}

int OrderedMap::search(string concatWord)
{

    unsigned int key = 0;
    int certainConstant = 5;
    for (unsigned int i = 0; i < concatWord.length(); i++)
    {
        key = certainConstant * key + concatWord.at(i);
    }


    int tempStart = 0;
    int tempEnd = end - 1;
    int tempMiddle = (tempStart + tempEnd) / 2;


    while (tempEnd - tempStart > 1)
    {
        if (orderedTable[tempMiddle]->concatWord == concatWord)
        {
            return orderedTable[tempMiddle]->counter;
        }
        if (orderedTable[tempMiddle]->concatWord < concatWord)
        {
            tempStart = tempMiddle + 1;
        }
        else
        {
            tempEnd = tempMiddle;
        }
        tempMiddle = (tempStart + tempEnd) / 2;
    }

    if (orderedTable[tempStart]->concatWord == concatWord)
    {
        return orderedTable[tempStart]->counter;
    }
    if (orderedTable[tempEnd]->concatWord == concatWord)
    {
        return orderedTable[tempEnd]->counter;
    }
    return 0;
}
