//#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <time.h>
#include <chrono>
#include <cstring>
#include <ctime>

//Import Data Structure Classes
#include "UnorderedTable.h"
#include "OrderedMap.h"
#include "BinaryTree.h"
#include "AVL.h"
#include "HashTable.h"
#include "UnorderedMap.h"

using namespace std;
using namespace chrono;  // For time

int main()
{
    char exludedCharacters[] = " ?><'´;{}!@#$%^&*()+-.=/,`~_[] ";  //Characters to be excluded

    //Initializations of our Data Structures, file readers-writers and important times to sum up
    ifstream fileread;
    ofstream output;
    UnorderedTable* unorderedT = new UnorderedTable;
    OrderedMap* ordered = new OrderedMap;
    BinaryTree* bst = new BinaryTree;
    AVL* avl = new AVL;
    HashTable* ht = new HashTable;
    UnorderedMap* unordered = new UnorderedMap;


    //time relating variables
    double create1 = 0.;
    double create2 = 0.;
    double create3 = 0.;
    double create4 = 0.;
    double create5 = 0.;
    double create6 = 0.;
    double searche1 = 0.;
    double searche2 = 0.;
    double searche3 = 0.;
    double searche4 = 0.;
    double searche5 = 0.;
    double searche6 = 0.;

    clock_t start;

    string stringFromText;
    string randomWords[1000]; // 1000 random concatenated words to search later

    fileread.open("small-file.txt");
    output.open("output.txt");
    //fileread.open("gutenberg.txt");

    int count = 0;
    int countAdd = 0;
    char input[10000];
    char* command;
    string firstWord;

    while (!fileread.eof())
    {
        fileread.getline(input, 10000);

        command = strtok(input, exludedCharacters);

        while (command != NULL)
        {
            string a = (string)command;
            for (unsigned int i = 0; i < a.size(); i++)
            {
                command[i] = tolower(command[i]);
            }

            if (count != 0)
            {
                string final_string = firstWord + "-" + (string)command;

                start = clock();
                unorderedT->insert(final_string);
                create1 = create1 + double(clock() - start);

                start = clock();
                ordered->insert(final_string);
                create2 = create2 + double(clock() - start);

                start = clock();
                bst->insert(final_string, bst->getRoot());
                create3 = create3 + double(clock() - start);

                start = clock();
                avl->insert(final_string, avl->getRoot());
                create4 = create4 + double(clock() - start);

                start = clock();
                ht->insert(final_string);
                create5 = create5 + double(clock() - start);

                start = clock();
                unordered->insert(final_string);
                create6 = create6 + double(clock() - start);

                if (count % 100 == 0 && countAdd < 1000)
                {
                    randomWords[countAdd] = final_string;
                    countAdd = countAdd + 1;
                }
            }

            firstWord = (string)command;
            command = strtok(NULL, exludedCharacters);
            count = count + 1;
        }
    }


    output << "Create time for UNORDERED TABLE: " << create1 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Create time for ORDERED TABLE: " << create2 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Create time for BINARY TREE: " << create3 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Create time for AVL: " << create4 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Create time for HASH TABLE: " << create5 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Create time for UNORDERED MAP: " << create6 / CLOCKS_PER_SEC << "seconds" << endl;

    //Searching the 1000 concatenated words on every Data Structure
    int var, var1, var2, var3, var4, var5;

    for (int i = 0; i <= 999; i++)
    {
        start = clock();
        var = unorderedT->search(randomWords[i]);
        searche1 = searche1 + double(clock() - start);

        start = clock();
        var1 = ordered->search(randomWords[i]);
        searche2 = searche2 + double(clock() - start);

        start = clock();
        var2 = bst->search(randomWords[i], bst->getRoot());
        searche3 = searche3 + double(clock() - start);

        start = clock();
        var3 = avl->search(randomWords[i], avl->getRoot());
        searche4 = searche4 + double(clock() - start);

        start = clock();
        var4 = ht->search(randomWords[i]);
        searche5 = searche5 + double(clock() - start);

        start = clock();
        var5 = unordered->search(randomWords[i]);
        searche6 = searche6 + double(clock() - start);

        output << randomWords[i] << " " << var << " " << var1 << " " << var2 << " " << var3 << " " << var4 << " " << var5 << " " << endl;

    }


    output << "Search time for 1000 words in UNORDERED TABLE: " << searche1 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Search time for 1000 words in ORDERED TABLE: " << searche2 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Search time for 1000 words in BINARY TREE: " << searche3 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Search time for 1000 words in AVL: " << searche4 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Search time for 1000 words in HASH TABLE: " << searche5 / CLOCKS_PER_SEC << "seconds" << endl;
    output << "Search time for 1000 words in UNORDERED MAP: " << searche6 / CLOCKS_PER_SEC << "seconds" << endl;


    //fileread.close();
    output.close();
    return 0;

}
