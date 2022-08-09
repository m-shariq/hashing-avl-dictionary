/*
DATA STRUCTURES AND ALGORITHMS WE USED:
1) Hashing
2) AVL Tree
3) Linked List
4) Trie
5) Queue
6) Arrays
7) Recursion
*/

//Included libraries

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

//Included Files

#include "AVLTree.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "Tries.h"
#include "Functions.h"
#include "Runner.h"

using namespace std;

int main() {
    FileReading();//reads the file and inserts in data structure
    int a;
    do {
        a = RunnerFunction();//allows user to operate dictionary
    } while (a != 8);
    return 0;
}
