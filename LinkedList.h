

#ifndef UNTITLED8_LINKEDLIST_H
#define UNTITLED8_LINKEDLIST_H


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


#endif
