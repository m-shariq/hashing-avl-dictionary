#ifndef UNTITLED8_AVLTREE_H
#define UNTITLED8_AVLTREE_H

using namespace std;
class HashTable; // FORWARD DECLARATION
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


#endif //UNTITLED8_AVLTREE_H
