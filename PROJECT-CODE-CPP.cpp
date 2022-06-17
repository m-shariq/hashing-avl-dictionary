#include<iostream>
using namespace std;

template <class T>
class AVLTree {
public:
    int datA;
    AVLTree *leftChild;
    AVLTree *rightChild;
};

template <class T>
class AVL {
public:

    AVLTree<T> *root;
    AVL() {
        root = NULL;
    }

    //TASK 1
    void Insert(int value)
    {
        root= SubInsert(root, value);
    }

    //TASK 2
    void Delete(int value)
    {
        root= SubDelete(root, value);
    }

    //TASK 3
    int CalculateHeight(AVLTree<T> *x) {
        if(x == NULL)
            return -1;
        else
            return max(CalculateHeight(x->leftChild),
                       CalculateHeight(x->rightChild)) + 1;
    }

    //TASK 4
    int BalanceFactor(AVLTree<T> *t) {
        return CalculateHeight(t->leftChild)-CalculateHeight(t->rightChild);
    }

    //TASK 5
    AVLTree<T> *LeftRotate(AVLTree<T> *x) {
        cout<<"Left rotation.... \n";
        AVLTree<T> *nn;
        nn = x->leftChild;
        x->leftChild = nn->rightChild;
        nn->rightChild = x;
        return nn;
    }

    //TASK 6
    AVLTree<T> *RightRotate(AVLTree<T> *x) {
        cout<<"Right rotation.... \n";
        AVLTree<T> *nn;
        nn = x->rightChild;
        x->rightChild = nn->leftChild;
        nn->leftChild = x;
        return nn;
    }

    //TASK 7
    AVLTree<T> *LeftRightRotate(AVLTree<T> *x) {
        cout<<"LeftRight rotation.... \n";
        AVLTree<T> *nn;
        nn = x->leftChild;
        x->leftChild = RightRotate(nn);
        return LeftRotate(x);
    }

    //TASK 8
    AVLTree<T> *RightLeftRotate(AVLTree<T> *x) {
        cout<<"RightLeft rotation.... \n";
        AVLTree<T> *nn;
        nn = x->rightChild;
        x->rightChild = LeftRotate(nn);
        return RightRotate(x);
    }

    //PRINTING FUNCTION//
    void InOrder(AVLTree<T> *node) {
        if (node == NULL)
            return;
        InOrder(node->leftChild);
        cout << node->datA << ", ";
        InOrder(node->rightChild);
    }

    //Function for insertion
    AVLTree<T> *SubInsert(AVLTree<T> *x, int value){
        if (x == NULL){
            x = new AVLTree<T>;
            x->datA = value;
            x->leftChild = NULL;
            x->rightChild = NULL;
            return x;
        }
        else if (value < x->datA){
            x->leftChild = SubInsert(x->leftChild, value);
            x = Rotation(x);
        }
        else if (value >= x->datA){
            x->rightChild = SubInsert(x->rightChild, value);
            x = Rotation(x);
        }
        return x;
    }

    //Function for deletion
    AVLTree<T>* SubDelete(AVLTree<T>* x, int value)
    {
        if (x == NULL)
            return x;
        if (value < x->datA )
            x->leftChild = SubDelete(x->leftChild, value);
        else if(value > x->datA )
            x->rightChild = SubDelete(x->rightChild, value);
        else{
            if((x->leftChild == NULL) ||  (x->rightChild == NULL)){

                AVLTree<T> *current;
                if(current == x->leftChild) current= x->leftChild;
                else current = x->rightChild;

                if (current == NULL){
                    current = x;
                    x = NULL;
                }else *x = *current;
                free(current);
            }
            else{
                AVLTree<T>* temp = x->rightChild;
                while (temp->leftChild != NULL)
                    temp = temp->leftChild;
                x->datA = temp->datA;
                x->rightChild = SubDelete(x->rightChild, temp->datA);
            }
        }
        if (x == NULL) return x;
        x=Rotation(x);
        return x;
    }

    //-//
    AVLTree<T> *Rotation(AVLTree<T> *x) {
        int rotate = BalanceFactor(x);
        if (rotate > 1) {//for left child
            if (BalanceFactor(x->leftChild) > 0)
                x = LeftRotate(x);
            else
                x = LeftRightRotate(x);
        }
        else if (rotate < -1) {//for right child
            if (BalanceFactor(x->rightChild) > 0)
                x = RightLeftRotate(x);
            else
                x = RightRotate(x);
        }
        return x;
    }

    //TASK 9:
    void RunnerFunction(T a,T b,T c,T d,T e,T f,T g){
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Insertion of values:\n"<<
            a<<", "<<b<<", "<<c<<", "<<d<<", "<<e<<", "<<f<<", "<<g<<endl<<endl;

        //Insert Function//
        Insert(a);
        Insert(b);
        Insert(c);
        Insert(d);
        Insert(e);
        Insert(f);
        Insert(g);
        cout<<endl;
        InOrder(root);
        cout<<endl<<"Height of tree: "<<CalculateHeight(root)<<endl;
        cout<<"Balance factor of tree: "<<BalanceFactor(root)<<endl;

        //Delete Function//
        cout<<endl<<"Deleting value: "<<c<<endl;
        Delete(c);
        InOrder(root);
        cout<<endl<<"Height of tree: "<<CalculateHeight(root)<<endl;
        cout<<"Balance factor of tree: "<<BalanceFactor(root)<<endl;
    }
};

//MAIN OF PROGRAM//
int main() {
    AVL<int>* a1=new AVL<int>();
    AVL<int>* a2=new AVL<int>();
    AVL<int>* a3=new AVL<int>();
    AVL<int>* a4=new AVL<int>();
    a1->RunnerFunction(2,67,54,34,87,45,65);
    a2->RunnerFunction(12,97,54,34,7,45,65);
    a3->RunnerFunction(90,70,100,50,80,30,0);
    a4->RunnerFunction(80,60,90,85,120,100,0);
    return 0;
}
