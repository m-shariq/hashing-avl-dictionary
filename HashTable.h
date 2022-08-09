#ifndef UNTITLED8_HASHTABLE_H
#define UNTITLED8_HASHTABLE_H


const int TABLE_SIZE = 14000; //SIZE FOR HASHTABLE
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


#endif //UNTITLED8_HASHTABLE_H
