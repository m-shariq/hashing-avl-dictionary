//
// Created by shari on 09/08/2022.
//

#ifndef UNTITLED8_TRIES_H
#define UNTITLED8_TRIES_H


const int MAX = 1700; //SIZE FOR QUEUE
//Creates a QUEUE using an array so that words cn be retrieved from the trie
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


#endif //UNTITLED8_TRIES_H
