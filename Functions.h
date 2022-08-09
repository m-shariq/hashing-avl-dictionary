#ifndef UNTITLED8_FUNCTIONS_H
#define UNTITLED8_FUNCTIONS_H


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



#endif //UNTITLED8_FUNCTIONS_H
