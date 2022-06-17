/*
DATA STRUCTURES AND ALGORITHMS I USED:
1) Hashing
2) AVL Tree
3) Linked List
4) Trie
5) Queue
6) Arrays
7) Recursion
*/

//Inlcuded libraries

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <windows.h>

using namespace std;
const int MAX = 1700; //SIZE FOR QUEUE
const int TABLE_SIZE = 14000; //SIZE FOR HASHTABLE


class HashTable; // FORWARD DECLARATION

//----------------------------------------------------------------------//
//------------------------------AVL-TREE--------------------------------//
//----------------------------------------------------------------------//

template<class T> //MAKING THE CLASS GENERIC
/*
CREATING THE AVLTree CLASS for storing the nodes of
words, meanings and examples where the address of the
root is stored in the hash table
*/
class AVLTree {
public:
    HashTable *datA;
    AVLTree *leftChild;
    AVLTree *rightChild;
};

template<class T>
class AVL {
public:
    AVLTree<T> *root;

    AVL() {
        root = NULL; //initialising the root ot NULL
    }

    //Insertion in AVlTree
    void Insert(T *value) {
        root = SubInsert(root, value);
    }

    /*Function for insertion. This function inserts
    a node containing word, meaning and sentences.*/
    AVLTree<T> *SubInsert(AVLTree<T> *x, T *value) {
        if (x == NULL) { //if root is NULL the following instructions execute
            x = new AVLTree<T>;
            x->datA = value;
            x->leftChild = NULL;
            x->rightChild = NULL;
            return x;
            /*
            If the word being inserted already exists in the tree and also
            have same meanings and examples than the word will not be inserted
            */

            /*If the word being inserted is less than the word in the parent,
             the word goes at the left child of the parent*/
        } else if (value->word < x->datA->word && value->m_list->start->data != x->datA->m_list->start->data) {
            x->leftChild = SubInsert(x->leftChild, value);
            x = Rotation(x);
            /*If the word being inserted is greater than or equal the word in the parent,
             the word goes at the right child of the parent*/
        } else if (value->word >= x->datA->word && value->m_list->start->data != x->datA->m_list->start->data) {
            x->rightChild = SubInsert(x->rightChild, value);
            x = Rotation(x);
        }
        return x;
    }

    //Rotation Function
    AVLTree<T> *Rotation(AVLTree<T> *x) {
        int rotate = BalanceFactor(x); // returns the balance factor of tree from parent
        if (rotate > 1) {//for left child
            if (BalanceFactor(x->leftChild) > 0)
                /*if the balance factor of
                leftChild is greater than 0*/
                x = LeftRotate(x);
            else
                x = LeftRightRotate(x);
        } else if (rotate < -1) {//for right child
            if (BalanceFactor(x->rightChild) > 0)
                /*if the balance factor of
                rightChild is greater than 0*/
                x = RightLeftRotate(x);
            else
                x = RightRotate(x);
        }
        return x;
    }

    //CalculateHeight functions calculates height of the parent node
    int CalculateHeight(AVLTree<T> *x) {
        if (x == NULL)
            return -1;
        else
            /*returns the max height trqaversing
            both childs using recursion*/
            return max(CalculateHeight(x->leftChild),
                       CalculateHeight(x->rightChild)) + 1;

    }

    /*BalanceFactor checks the difference of height between
    left and right child trees of a parent tree using recursion*/
    int BalanceFactor(AVLTree<T> *t) {
        return CalculateHeight(t->leftChild) - CalculateHeight(t->rightChild);
    }

    //LeftRotation
    AVLTree<T> *LeftRotate(AVLTree<T> *x) {
        AVLTree<T> *nn;
        nn = x->leftChild;
        x->leftChild = nn->rightChild;
        nn->rightChild = x;
        return nn;
    }

    //RightRotation
    AVLTree<T> *RightRotate(AVLTree<T> *x) {
        AVLTree<T> *nn;
        nn = x->rightChild;
        x->rightChild = nn->leftChild;
        nn->leftChild = x;
        return nn;
    }

    //LeftRightRotate
    AVLTree<T> *LeftRightRotate(AVLTree<T> *x) {
        AVLTree<T> *nn;
        nn = x->leftChild;
        x->leftChild = RightRotate(nn);
        return LeftRotate(x);
    }

    //RightLeftRotate
    AVLTree<T> *RightLeftRotate(AVLTree<T> *x) {
        AVLTree<T> *nn;
        nn = x->rightChild;
        x->rightChild = LeftRotate(nn);
        return RightRotate(x);
    }
    /*------------------------------------------------
    ------------------BASE FUNCTIONS------------------
    ------------------------------------------------*/

    /*PRINTS THE MEANINGS AND EXAMPLES OF THE SEARCHED WORD*/
    //Complexty BigO(LogN)
    void InOrder(AVLTree<T> *node, string word) {
        if (node == NULL)
            return;
        //TRAVERSAL IS DONE MAKING USE OF RECURSION
        InOrder(node->leftChild, word);
        if (node->datA->word == word) {
            node->datA->m_list->printList();
            node->datA->e_list->printList();
        }
        InOrder(node->rightChild, word);
    }

    /*PRINTS THE MEANINGS OF THE SEARCHED WORD*/
    //Complexty BigO(LogN)
    void InOrderForMeaning(AVLTree<T> *node, string word) {
        if (node == NULL)
            return;
        InOrderForMeaning(node->leftChild, word);
        if (node->datA->word == word) {
            node->datA->m_list->printList();//PrintList FUNCTION IS CALLED
        }
        InOrderForMeaning(node->rightChild, word);
    }

    /*PRINTS THE EXAMPLES OF THE SEARCHED WORD*/
    //Complexty BigO(LogN)
    void InOrderForExamples(AVLTree<T> *node, string word) {
        if (node == NULL)
            return;
        InOrderForExamples(node->leftChild, word);
        if (node->datA->word == word) {
            node->datA->e_list->printList(); //PrintList FUNCTION IS CALLED
        }
        InOrderForExamples(node->rightChild, word);
    }

    /*THIS FUNCTION IS USED TO INSERT AN
    EXAMPLE OF THE GIVEN WORD IN THE TREE*/
    //Complexty BigO(LogN)
    void AddExample(AVLTree<T> *node, string word, string newexample) {
        if (node == NULL)
            return;
        AddExample(node->leftChild, word, newexample);
        if (node->datA->word == word) {
            node->datA->e_list->InsertValueAtTail(newexample);//InsertValueAtTail FUNCTION IS CALLED
        }
        AddExample(node->rightChild, word, newexample);
    }

    /*THIS FUNCTION IS USED TO INSERT A
    MEANING OF THE GIVEN WORD IN THE TREE*/
    //Complexty BigO(LogN)
    void AddMeaning(AVLTree<T> *node, string word, string newmeaning) {
        if (node == NULL)
            return;
        AddMeaning(node->leftChild, word, newmeaning);
        if (node->datA->word == word) {
            node->datA->m_list->InsertValueAtTail(newmeaning);//InsertValueAtTail FUNCTION IS CALLED
        }
        AddMeaning(node->rightChild, word, newmeaning);
    }

    /*THIS FUNCTION IS USED TO DELETE AN
    EXAMPLE OF THE GIVEN WORD IN THE TREE*/
    //Complexty BigO(LogN)
    void DeleteExample(AVLTree<T> *node, string word, string example) {
        if (node == NULL)
            return;
        DeleteExample(node->leftChild, word, example);
        if (node->datA->word == word) {
            node->datA->e_list->Delete(example); //DELETE FUNCTION IS CALLED
        }
        DeleteExample(node->rightChild, word, example);
    }

    /*THIS FUNCTION IS USED TO DELETE A
    MEANING OF THE GIVEN WORD IN THE TREE*/
    //Complexty BigO(LogN)
    void DeleteMeaning(AVLTree<T> *node, string word, string meaning) {
        if (node == NULL)
            return;
        DeleteMeaning(node->leftChild, word, meaning);
        if (node->datA->word == word) {
            node->datA->m_list->Delete(meaning);//DELETE FUNCTION IS CALLED
        }
        DeleteMeaning(node->rightChild, word, meaning);
    }

};

//----------------------------------------------------------------------//
//------------------------- Meaning-LIST--------------------------------//
//----------------------------------------------------------------------//

class MeaningNode {
public:
    string data;
    MeaningNode *next;
};

//---------------------------------//
class MeaningList {
public:
    MeaningNode *start = NULL;
    MeaningNode *last = NULL;
    MeaningNode *Loc_ = NULL;
    MeaningNode *PredLoc_ = NULL;


    bool isEmpty() {
        return start == NULL;
    }

    //Complexty BigO(N)
    void InsertValueAtTail(string value)//Inserts value at tail and updates the last node
    {
        MeaningNode *node = new MeaningNode();
        node->data = value;
        if (isEmpty()) {
            start = node;
            last = node;
        } else {
            last->next = node;
            last = node;
        }
    }

    /*This function prints the meaning list by
    traversing through nodes of the meaning sll*/
    //Complexty BigO(N)
    void printList() {
        MeaningNode *temp = start;
        int a = 1;
        if (!isEmpty()) {
            cout << "MEANINGS: " << endl;
            while (temp != NULL) {
                cout << a << ") " << temp->data << endl;
                // advance temp to successor node.
                temp = temp->next;
                a++;
            }
        }
        cout << endl;
    }

    //Gives the pointer and the pointer to previous of the value searched
    //Complexty BigO(N)
    void search(string value) {
        Loc_ = start;
        PredLoc_ = NULL;
        if (isEmpty())
            return;
        while (Loc_ != NULL && Loc_->data != value) {
            PredLoc_ = Loc_;
            Loc_ = Loc_->next;
        }
        if (Loc_ != NULL && Loc_->data != value) {
            Loc_ = NULL;
        }
    }

    //Deletes a node given the value(meaning) stored in it
    void Delete(string value) {
        if (isEmpty()) {
            return;
        }
        search(value);
        if (Loc_ != NULL) {
            if (PredLoc_ == NULL) {
                start = start->next;
                delete Loc_;
            } else {
                //update link using ploc
                if (Loc_ == last)
                    last = PredLoc_;
                PredLoc_->next = Loc_->next;
                //finally free memory using delete command.
                delete Loc_;
            }
        }
    }
};

//----------------------------------------------------------------------//
//------------------------- Example-LIST--------------------------------//
//----------------------------------------------------------------------//

class ExampleNode {
public:
    string data;
    ExampleNode *next;
};

//---------------------------------//
class ExampleList {
public:
    ExampleNode *start = NULL;
    ExampleNode *last = NULL;
    ExampleNode *Loc_ = NULL;
    ExampleNode *PredLoc_ = NULL;


    bool isEmpty() {
        return start == NULL;
    }

    //Complexty BigO(N)
    void InsertValueAtTail(string value)//Inserts value at tail
    {
        ExampleNode *node = new ExampleNode();
        node->data = value;
        if (isEmpty()) {
            start = node;
            last = node;
        } else {
            last->next = node;
            last = node;
        }
    }

    /*This function prints the example list by
    traversing through nodes of the example sll*/
    //Complexty BigO(N)
    void printList() {
        ExampleNode *temp = start;
        int a = 1;
        if (!isEmpty()) {
            cout << "EXAMPLES: " << endl;
            while (temp != NULL) {
                cout << a << ") " << temp->data << endl;
                // advance temp to successor node.
                temp = temp->next;
                a++;
            }
        }
        cout << endl;
    }

    //Gives the pointer and the pointer to previous of the value searched
    //Complexty BigO(N)
    void search(string value) {
        Loc_ = start;
        PredLoc_ = NULL;
        if (isEmpty())
            return;
        while (Loc_ != NULL && Loc_->data != value) {
            PredLoc_ = Loc_;
            Loc_ = Loc_->next;
        }
        if (Loc_ != NULL && Loc_->data != value) {
            Loc_ = NULL;
        }
    }

    //Deletes a node given the value(example) stored in it
    void Delete(string value) {
        if (isEmpty()) {
            return;
        }
        search(value);
        if (Loc_ != NULL) {
            if (PredLoc_ == NULL) {
                start = start->next;
                delete Loc_;
            } else {
                //update link using ploc
                if (Loc_ == last)
                    last = PredLoc_;
                PredLoc_->next = Loc_->next;
                //finally free memory using delete command.
                delete Loc_;
            }
        }
    }
};

//----------------------------------------------------------------------//
//---------------------------HASH-TABLE---------------------------------//
//----------------------------------------------------------------------//

/*This class contains a string type word,an integer key to store indexes
for nodes and the objects of meaning and example list classes*/

class HashTable {
public:
    string word;
    MeaningList *m_list = new MeaningList();
    ExampleList *e_list = new ExampleList();
    int key;

    //HashTable *next;
    //CONSTRUCTOR TO INITIALISE ALL THE FIELDS
    HashTable(int key, string word, MeaningList *m_list, ExampleList *e_list) {
        this->key = key;
        this->word = word;
        //    this->next = NULL;
        this->m_list = m_list;
        this->e_list = e_list;
    }
};

//---------------------------------//
class HashMapTable {
public:
    AVL<HashTable> **hash_table;

    //Constructor assigning NULL to the whole table
    HashMapTable() {
        hash_table = new AVL<HashTable> *[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            hash_table[i] = NULL;
    }

    /*Hash Function generates a key corresponding to where
     the node is to be inserted into the AVL tree*/
    int HashFunc(string word) {
        int sum = 0;
        int special = 717;
        for (string::size_type i = 0; i < word.length(); i++) {
            sum += word[i] * special;
            special += 7;
        }
        return sum % TABLE_SIZE;
    }

    //Insert into hash hash_table
    //Average Complexty BigO(1)
    void Insert(string word, MeaningList *ml, ExampleList *el) {
        int hash_v = HashFunc(word);

        AVL<HashTable> *en = hash_table[hash_v];
        HashTable *T = new HashTable(hash_v, word, ml, el);
        //checks if the there is avl tree at the given has value
        //if not akes a new tree and if exists simpe insertion takes place
        if (en == NULL) {

            AVL<HashTable> *avl = new AVL<HashTable>();
            avl->Insert(T);

            hash_table[hash_v] = avl;
        } else {
            en->Insert(T);
        }
    }

};

//----------------------------------------------------------------------//
//------------------------------QUEUE-----------------------------------//
//----------------------------------------------------------------------//
//Creates a QUEUE using an array so that words cn be retrieved fron the trie
template<typename T>
class QueueNode {
public:
    T q[MAX];//Max size array is declared
    int first = 0;
    int last = -1;

    bool isEmpty() {
        return last == -1;
    }

    bool isFull() {
        return first == MAX - 1;
    }

    T peek() {
        return q[first];//returns the first element of the QUEUE
    }

    void Enqueue(T a) {
        if (!isFull()) {
            last++;
            q[last] = a;
        }
    }

    //delete the first and moves each forward
    //Complexty BigO(N)
    T Dequeue() {
        T x = q[first];
        if (!isEmpty()) {
            for (int i = 0; i <= last; i++) {
                q[i] = q[i + 1];
            }
            last--;
        }
        return x;
    }
};

//----------------------------------------------------------------------//
//------------------------------Linked List-----------------------------//
//----------------------------------------------------------------------//

class ListNode {
public:
    string data;
    ListNode *next;
};

class LinkedList {
public:

    ListNode *start;
    ListNode *last;

    LinkedList() {
        start = NULL;
    }

    bool isEmpty() {
        return start == NULL;
    }

//Complexty BigO(N)
    void InsertAtEnd(string value) {
        ListNode *newnode = new ListNode();
        newnode->data = value;
        if (isEmpty()) {
            start = newnode;
            last = newnode;
        } else {
            last->next = newnode;
            last = newnode;
        }
    }

//complexity BigO(N)
    void PrintList(string key) {
        int a = 1;
        ListNode *temp = start;
        if (!isEmpty()) {
            while (temp != NULL) {
                if (key != temp->data) {
                    cout << a << ") " << temp->data << endl;
                    a++;
                }
                temp = temp->next;
            }
            cout << "" << endl;
        } else
            cout << "List is Empty " << endl;
    }
};

//----------------------------------------------------------------------//
//------------------------------TRIE-DS---------------------------------//
//----------------------------------------------------------------------//
//components of the trie node
class TrieNode {
public:
    bool is_word;
    TrieNode *child[29]; //The size for pointer array is 29 having 26 for alphabets and 3 extra for space, - and '
};

//The values of nodes is initialized as null
TrieNode *NewNode() {
    TrieNode *temp = new TrieNode();
    temp->is_word = false;
    for (int i = 0; i < 29; i++) {
        temp->child[i] = NULL;
    }
    return temp;
}

class Container {
public:
    TrieNode *test;
    string str;
};

HashMapTable hash1;
TrieNode *root = NewNode();

//=======================================================================================//
//===================================FUNCTIONS===========================================//
//=======================================================================================//

void SearchKey(string word);

void SearchForMeaning(string word);

void SearchForExamples(string word);

void InsertTrie(TrieNode *root, string key);

void UserInsert();

bool WordsForCorrection(TrieNode *root, string key, LinkedList all_suggestion);

bool WordsForSuggestion(TrieNode *root, string key, LinkedList all_suggestion, string original);


//----------------------------------------------------------------------//
//------------------------------FUNCTION--------------------------------//
//----------------------------------------------------------------------//

//---------FUNCTION-PROJECT2---------//

/*Function inserts all the words by inserting
their characters separately in the nodes*/
void InsertTrie(TrieNode *root, string key) {
    TrieNode *temp = root;
    int ind = 0;
    for (int i = 0; i < (int) key.length(); i++) {
        //Checks for assigning index to words
        if (int(key[i]) == ' ') {
            ind = 26;
        } else if (int(key[i]) == '-') {
            ind = 27;
        } else if (int(key[i]) == '\'') {
            ind = 28;
        } else {
            ind = int(key[i]) - 'a';
        }
        /*creating a newnode in case any of the
        characters in the word doesn't exist*/
        if (temp->child[ind] == NULL) {
            temp->child[ind] = NewNode();
        }
        temp = temp->child[ind]; //traversing the trie using index assigned above
    }
    temp->is_word = true; //Setting is_word true for the last character of the entered word
}


//---------FUNCTION-PROJECT2---------//

bool WordsForCorrection(TrieNode *root, string key) {
    //if root is empty, the function returns true
    if (root == NULL)
        return true;
    TrieNode *temp = root;
    int sub_key = 0; //giving indexes to the input word

    for (int i = 0; i < (int) key.size(); i++) {
        if (int(key[i]) == ' ') sub_key = 26;
        else if (int(key[i]) == '-') sub_key = 27;
        else if (int(key[i]) == '\'') sub_key = 28;
        else sub_key = int(key[i]) - 'a';

        /*if the input value at the index does
        not match the actual value at the index*/

        if (temp->child[sub_key] == NULL) return false;
        temp = temp->child[sub_key];
    }

    /*Generic type queue node with the container
    class node being passed in it*/
    QueueNode<Container *> q;
    Container *pTemp = new Container();
    /*Entering the last character of the correct
    (available) substring of the entered string in pTemp*/
    pTemp->test = temp;
    //The correct substring is stored here
    pTemp->str = key;
    //The whole pTemp node is enqueued (Pushed in the queue)
    q.Enqueue(pTemp);

    string this_word;
    while (!q.isEmpty()) {
        temp = q.peek()->test;//Storing the character in first element of the queue into temp

        /*Storing the whole string that was passed
        from the first element of the queue into this_word*/
        this_word = q.peek()->str;

        // storing the dequeued queue in the tempDelete pointer of type Container
        Container *tempDelete = q.Dequeue();
        delete tempDelete;
        /*This loop throughs all the childs of the node value stored in temp
         *It adds the character at the end of the suggestion based on the index
         * and enqueues it in pp*/
        for (int i = 0; i < 29; i++) {
            if (temp->child[i] != NULL) {
                Container *pp = new Container();
                pp->test = temp->child[i];
                if (i < 26) pp->str = this_word + char(i + int('a'));
                else if (i == 26) pp->str = this_word + char(int(' '));
                else if (i == 27) pp->str = this_word + char(int('-'));
                else pp->str = this_word + char(int('\''));
                q.Enqueue(pp);
            }
        }
    }
    return true;
}

//---------FUNCTION-PROJECT2---------//

bool WordsForSuggestion(TrieNode *root, string key, LinkedList all_suggestion, string original) {
    //if root is empty, the function returns true
    if (root == NULL)
        return true;

    TrieNode *temp = root;
    int sub_key = 0;     //giving indexes to the input word
    for (int i = 0; i < (int) key.size(); i++) {
        if (int(key[i]) == ' ') sub_key = 26;
        else if (int(key[i]) == '-') sub_key = 27;
        else if (int(key[i]) == '\'') sub_key = 28;
        else sub_key = int(key[i]) - 'a';

        /*if the input value at the index does
        not match the actual value at the index*/

        if (temp->child[sub_key] == NULL) {
            cout << "No suggestion Found";
            return false;
        }
        temp = temp->child[sub_key];
    }

    QueueNode<Container *> q;
    Container *pTemp = new Container();

    pTemp->test = temp;
    pTemp->str = key;
    q.Enqueue(pTemp);

    string this_word;

    while (!q.isEmpty()) {
        temp = q.peek()->test; //Storing the character in first element of the queue into temp

        /*Storing the whole string that was passed
        from the first element of the queue into this_word*/
        this_word = q.peek()->str;

        /*Check to see if the word is complete or
        not and inserting it in the sll if it is*/

        if (temp->is_word)
            all_suggestion.InsertAtEnd(this_word);
        // storing the dequeued queue in the tempDelete pointer of type Container
        Container *tempDelete = q.Dequeue();

        delete tempDelete;

        /*This loop throughs all the childs of the node value stored in temp
         *It adds the character at the end of the suggestion based on the index
         * and enqueues it in pp*/
        for (int i = 0; i < 29; i++) {
            if (temp->child[i] != NULL) {
                Container *pp = new Container();
                pp->test = temp->child[i];
                if (i < 26) pp->str = this_word + char(i + int('a'));
                else if (i == 26) pp->str = this_word + char(int(' '));
                else if (i == 27) pp->str = this_word + char(int('-'));
                else pp->str = this_word + char(int('\''));
                q.Enqueue(pp);
            }
        }
    }
    /*If the word entered is correct but there are suggestion related
    to it then the original word is not shown in the suggestions*/
    all_suggestion.PrintList(original);
    return true;
}

//---------FUNCTION-PROJECT2---------//
//gives the suggestions along with possible  options for the word
bool WordCompletion(TrieNode *root, string key, string original) {
    if (key.length() == 0)
        return true;
    LinkedList all_words;
    return WordsForSuggestion(root, key, all_words, original);
}

//---------FUNCTION-PROJECT2---------//
//gives the suggestions along with possible correct options for the word
void WordCorrection(TrieNode *root, string key, string original) {
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    transform(original.begin(), original.end(), original.begin(), ::tolower);
    if (key.length() == 0) return;
    //checks for invalid input
    for (int i = 0; i < key.length(); i++) {
        if (!((key[i] >= 'a' && key[i] <= 'z') || key[i] == ' ' || key[i] == '-' || key[i] == '\'')) {
            cout << "Incorrect Input!";
            return;
        }
    }
    if (key[0] == ' ' || key[0] == '-' || key[0] == '\'') {
        cout << "Incorrect Input!";
        return;
    }
    bool word_check = WordsForCorrection(root, key);
    //until the word is not able to give proper suggestion or cooerction  the length of word will be ommited by one
    if (word_check == false) {
        string newKey = key.substr(0, key.length() - 1);
        WordCorrection(root, newKey, original);
    } else {
        WordCompletion(root, key, original);

        return;
    }
}

//---------FUNCTION-PROJECT1---------//
//returns all the information of the word store in the hash table
//by gonig to base function in the given function
void SearchKey(string word) {
    if (word.length() <= 1)return;
    cout << endl << "WORD IS: " << word << endl << endl;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    //gets key of the word
    int hash_v = hash1.HashFunc(word);
    //checks if the index of hastable is valid or not
    if (hash1.hash_table[hash_v] != NULL)
        hash1.hash_table[hash_v]->InOrder(hash1.hash_table[hash_v]->root, word);
    return;
}

//---------FUNCTION-PROJECT1---------//
//returns all meaining of the word store in the hash table
//by gonig to base function in the given function
void SearchForMeaning(string word) {
    if (word.length() <= 1)return;
    cout << endl << "WORD IS: " << word << endl << endl;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int hash_v = hash1.HashFunc(word);
    //checks if the index of hastable is valid or not
    if (hash1.hash_table[hash_v] != NULL)
        hash1.hash_table[hash_v]->InOrderForMeaning(hash1.hash_table[hash_v]->root, word);
    return;
}

//---------FUNCTION-PROJECT1---------//
//returns all examples of the word store in the hash table
//by gonig to base function in the given function
void SearchForExamples(string word) {
    if (word.length() <= 1)return;
    cout << endl << "WORD IS: " << word << endl << endl;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int hash_v = hash1.HashFunc(word);
    //checks if the index of hastable is valid or not
    if (hash1.hash_table[hash_v] != NULL)
        hash1.hash_table[hash_v]->InOrderForExamples(hash1.hash_table[hash_v]->root, word);
    return;
}

//---------FUNCTION-PROJECT1---------//
//this fuction lets the user insert values into the hashtable
void UserInsert() {
    MeaningList *ml = new MeaningList();
    ExampleList *el = new ExampleList();

    string input;
    string word;
    string meaning;
    string example;
//takes the word
    cout << "word: ";
    getline(cin, input);
    word = input;
//takes the inputs for meanings
    cout << "Meaning: (Maximum 3) \n";
    for (int i = 1; i <= 3; i++) {
        cout << i << ") :";
        getline(cin, input);
        meaning = input;
        ml->InsertValueAtTail(meaning);
    }
//takes the inputs for examples
    cout << "Example: (Maximum 3) \n";
    for (int i = 1; i <= 3; i++) {
        cout << i << ") :";
        getline(cin, input);
        example = input;
        el->InsertValueAtTail(example);
    }
    //inserts word and information in hastable
    hash1.Insert(word, ml, el);
    //inserts the word n the trie
    InsertTrie(root, word);
    SearchKey(word);
}

//---------FUNCTION-PROJECT1---------//
//takes the user in put of which word is to be searched for meanings
void MeaningOfWord() {
    string input;
    string word;

    cout << "Enter a word:\n ";
    getline(cin, input);
    word = input;
    SearchForMeaning(word);
    cout << "\nAll possible Suggestions and Correction:\n";
    WordCorrection(root, word, word);
}

//---------FUNCTION-PROJECT1---------//
//takes the user in put of which word is to be searched for examples
void ExampleOfWord() {
    string input;
    string word;

    cout << "Enter a word:\n ";
    getline(cin, input);
    word = input;
    SearchForExamples(word);
    cout << "\nAll possible Suggestions and Correction:\n";
    WordCorrection(root, word, word);
}

//---------FUNCTION-PROJECT1---------//
//takes the user in put of which word is to be searched for all its information
void InformationOfWord() {
    string input;
    string word;

    cout << "Enter a word:\n ";
    getline(cin, input);
    word = input;
    SearchKey(word);
    cout << "\nAll possible Suggestions and Correction:\n";
    WordCorrection(root, word, word);
}

//---------FUNCTION-PROJECT1---------//
//takes input of the word you want to get suggestion of
void SuggestionOfWord() {
    string input;
    string word;

    cout << "Enter a word:\n";
    getline(cin, input);
    word = input;
    cout << "\nAll possible Suggestions and Correction:\n";
    WordCorrection(root, word, word);
}

//---------FUNCTION-PROJECT1---------//
//takes input from user and then finds its meaning then
//promts user to write the meaning which he wants to delete
void DeleteMeaningToWord() {
    string word;
    string example;
    string input;
    cout << "Enter word:\n";
    getline(cin, input);
    word = input;
    SearchForMeaning(word);

    cout << "Enter meaning to delete:\n";
    getline(cin, input);
    example = input;

    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int hash_v = hash1.HashFunc(word);
    //checks if the index of hastable is valid or not
    if (hash1.hash_table[hash_v] != NULL)
        hash1.hash_table[hash_v]->DeleteMeaning(hash1.hash_table[hash_v]->root, word, example);
    SearchForMeaning(word);
    return;

}

//---------FUNCTION-PROJECT1---------//
//takes input from user and then finds its meaning then
// promts user to write the meaning which he wants to add
void AddMeaningToWord() {
    string word;
    string newexample;
    string input;
    cout << "Enter word:\n";
    getline(cin, input);
    word = input;
    SearchForMeaning(word);

    cout << "Enter new meaning:\n";
    getline(cin, input);
    newexample = input;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int hash_v = hash1.HashFunc(word);
    //checks if the index of hastable is valid or not
    if (hash1.hash_table[hash_v] != NULL)
        hash1.hash_table[hash_v]->AddMeaning(hash1.hash_table[hash_v]->root, word, newexample);
    SearchForMeaning(word);
    return;

}

//---------FUNCTION-PROJECT1---------//
//takes input from user and then finds its example then
// promts user to write the example which he wants to delete
void DeleteExampleToWord() {
    string word;
    string example;
    string input;
    cout << "Enter word:\n";
    getline(cin, input);
    word = input;
    SearchForExamples(word);

    cout << "Enter Example to delete:\n";
    getline(cin, input);
    example = input;

    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int hash_v = hash1.HashFunc(word);
    //checks if the index of hastable is valid or not
    if (hash1.hash_table[hash_v] != NULL)
        hash1.hash_table[hash_v]->DeleteExample(hash1.hash_table[hash_v]->root, word, example);
    SearchForExamples(word);
    return;

}

//---------FUNCTION-PROJECT1---------//
//takes input from user and then finds its example then
//promts user to write the example which he wants to add
void AddExampleToWord() {
    string word;
    string newexample;
    string input;
    cout << "Enter word:\n";
    getline(cin, input);
    word = input;
    SearchForExamples(word);

    cout << "Enter new example:\n";
    getline(cin, input);
    newexample = input;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int hash_v = hash1.HashFunc(word);
    //checks if the index of hastable is valid or not
    if (hash1.hash_table[hash_v] != NULL)
        hash1.hash_table[hash_v]->AddExample(hash1.hash_table[hash_v]->root, word, newexample);
    SearchForExamples(word);
    return;

}

//---------FUNCTION-PROJECT1---------//
//In this function user gets option of what he wants to add in  the dictionary
int EditInformation() {
    cout << "\n\tFUNCTION NO.1:  Add Meaning to Word." << endl;
    cout << "\tFUNCTION NO.2:  Add Example sentence of a word." << endl;
    cout << "\tFUNCTION NO.3:  Exit." << endl;
    cout << "\nSELECT ANY OF THE ABOVE OPTION BY WRITING FUNCTION No.:";
    int a = 1;
    //selects operation to be performed
    cin >> a;
    switch (a) {
        case 1:
            cin.ignore();
            AddMeaningToWord();//Adds meaning to said word
            system("pause");
            return 0;
        case 2:
            cin.ignore();
            AddExampleToWord();//Adds example to said word
            system("pause");
            return 0;
        default:
            cin.ignore();
            return a;
    }
}

//---------FUNCTION-PROJECT1---------//
//In this function user gets option of what he wants to add in  the delete
int DeleteInformation() {
    cout << "\n\tFUNCTION NO.1:  Delete Meaning to Word." << endl;
    cout << "\tFUNCTION NO.2:  Delete Example sentence of a word." << endl;
    cout << "\tFUNCTION NO.3:  Exit." << endl;
    cout << "\nSELECT ANY OF THE ABOVE OPTION BY WRITING FUNCTION No.:";
    int a = 1;

    cin >> a;
    switch (a) {
        case 1:
            cin.ignore();
            DeleteMeaningToWord();//deletes meaning of said word
            system("pause");
            return 0;
        case 2:
            cin.ignore();
            DeleteExampleToWord();//deletes example of said word
            system("pause");
            return 0;
        default:
            cin.ignore();
            return a;
    }
}

//----------------------------------------------------------------------//
//-------------------------RUNNER-FUNCTION------------------------------//
//----------------------------------------------------------------------//

int RunnerFunction() {

    cout << "\n\t\tFUNCTION NO.1:  Search Suggestions or Correction of a word." << endl;
    cout << "\t\tFUNCTION NO.2:  Search Meaning of a word." << endl;
    cout << "\t\tFUNCTION NO.3:  Search Example sentences of a word." << endl;
    cout << "\t\tFUNCTION NO.4:  Search Complete information of a word." << endl;
    cout << "\t\tFUNCTION NO.5:  Insert a word and its complete information." << endl;
    cout << "\t\tFUNCTION NO.6:  Insert new Information to a word." << endl;
    cout << "\t\tFUNCTION NO.7:  Delete existing Information of a word." << endl;
    cout << "\t\tFUNCTION NO.8:  Exit." << endl;
    cout << "\nSELECT ANY OF THE ABOVE OPTION BY WRITING FUNCTION No.:";
    int a = 1;
    //selects the function to be performed
    cin >> a;
    switch (a) {
        case 1:
            cin.ignore();
            SuggestionOfWord();//gives suggestion of word
            system("pause");
            return 0;
        case 2:
            cin.ignore();
            MeaningOfWord();//gives meaning of word
            system("pause");
            return 0;
        case 3:
            cin.ignore();
            ExampleOfWord();//gives example of word
            system("pause");
            return 0;
        case 4:
            cin.ignore();
            InformationOfWord();//gives all information of the word
            system("pause");
            return 0;
        case 5:
            cin.ignore();
            UserInsert();//inserts word in dictionary
            system("pause");
            return 0;
        case 6:
            int b;
            do {
                cin.ignore();
                b = EditInformation();//add information to word
            } while (b != 3);
            return 0;
        case 7:
            int c;
            do {
                cin.ignore();
                c = DeleteInformation();//deletes information from word
            } while (c != 3);
            return 0;
        default:
            return a;
    }
}
//----------------------------------------------------------------------//
//----------------------------FILE-READING------------------------------//
//----------------------------------------------------------------------//

void FileReading() {
    ifstream fin;
    string line;
    //file opened for reading
    fin.open("Z:\\words.txt"); // EDIT THE FILE PATH
    int count = 0;
    string field;
    string fields[11];
    //the file is read with the delimiter of table(\t)
    while (getline(fin, line)) {
        istringstream s(line);
        for (int i = 0; i < 11; i++) {
            getline(s, field, '\t');
            fields[i] = field;
        }
        //in the meaning part we separate the meaning with delimiter;
        MeaningList *ml = new MeaningList();
        stringstream mstream(fields[1]);
        while (mstream.good()) {
            string submean;
            getline(mstream, submean, ';');
            ml->InsertValueAtTail(submean);//inserted in meaning list
        }
        //all examples are added to the list until null value appears
        ExampleList *el = new ExampleList();
        bool go = true;
        int j = 2;
        while (go && j <= 10) {
            if (fields[j] != "") { el->InsertValueAtTail(fields[j]); }//inserted in example list
            else { go = false; }
            j++;
        }
        //add the word,meaning and example in the hash table
        transform(fields[0].begin(), fields[0].end(), fields[0].begin(), ::tolower);
        hash1.Insert(fields[0], ml, el);//inserted in hashtable
        InsertTrie(root, fields[0]);//inserted in trie
        count++;
    }
    cout << "\n\n\t\t--------------------Total Number of words are: " << count << "--------------------\n";
    cout << "\t\t-------------------------WELCOME TO OUR LUGAT---------------------------\n\n";
}

int main() {
    FileReading();//reads the file and inserts in data struture
    int a;
    do {
        a = RunnerFunction();//allows user to operate dictionary
    } while (a != 8);
    return 0;
}
