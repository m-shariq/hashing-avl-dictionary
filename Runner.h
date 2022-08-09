#ifndef UNTITLED8_RUNNER_H
#define UNTITLED8_RUNNER_H


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
    fin.open("C:\\Users\\shari\\CLionProjects\\untitled8\\word.txt");
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
    cout << "\t\t-------------------------WELCOME TO MY DICTIN---------------------------\n\n";
}


#endif //UNTITLED8_RUNNER_H
