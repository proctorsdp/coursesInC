//
//  Dictionary.cpp
//  Word Ladder - Steven Proctor
//
//  Created by Steven Proctor on 10/11/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "Dictionary.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/*
//Generates a list of words that are one letter different from the last word on the current ladder
void Dictionary::isOneAway(vector<string> currentLadder) {
    currentWord = currentLadder[currentLadder.size() - 1];
    string temp;
    int deleteSize = int(oneAway.size());
    
    for (int i = 0; i < deleteSize; i++) {
        oneAway.pop_back();
    }
    
    for (int i = 0; i < currentWord.length(); i++) {
        temp = currentWord;
        for (int j = 0; j < 26; j++) {
            temp[i] = j + 97;
            //cout << temp << endl;     //DEBUG
            if (isInDictionary(temp)) {
                oneAway.push_back(temp);
                createNode(currentLadder);
                tail->wordLadder.push_back(oneAway[oneAway.size()-1]);
                //cout << temp << endl;     //DEBUG
            }
        }
    }
    
    //Only runs if ladder has no solution
    if (oneAway.size() == 0 && head == NULL) {
        cout << "There is no solution for this word ladder.\n" << endl << endl;
        fstream fout;
        fout.open(outputFile);
        fout.seekp(0, ios::end);
        fout << "There is no solution for this word ladder.\n" << endl << endl;
        noSolution = true;
        fout.close();
    }
}

//Creates a vector of words from the dictionary that are the same length as the user submitted words
void Dictionary::initializeDictionary(int wordLength) {
    if (dictionary.size() != 0) {
        int dictionaryLength = int(dictionary.size());
        for (int i = 0; i < dictionaryLength; i++) {
            dictionary.pop_back();
            used.pop_back();
        }
        for (Node * t = head; t != NULL; t = t->next) {
            removeNode();
        }
    }
    
    string temp;
    fstream fin;
    
    fin.open(fileName);
    while (fin >> temp) {
        if (temp.length() == wordLength) {
            dictionary.push_back(temp);
            used.push_back(false);
            if (debug) {cout << temp << " - " << temp.length() << endl;}
        }
        else {
            if (debug) {cout << "Discard " << temp << " - " << temp.length() << endl;}
        }
    }
    fin.close();
}

//Prints a specific number of words contained in the dictionary vector
void Dictionary::printDictionaryVector(int length) {
    fstream fin;
    string temp;
    
    cout << "First " << length << " entries of the dictionary: \n";
    fin.open(fileName);
    for (int i = 0; i < length; i++) {
        fin >> temp;
        cout << i + 1 << ": " << temp << endl;
    }
    fin.close();
    cout << endl << endl;
}

//Prints all words contained in the dictionary vector
void Dictionary::printDictionaryVector() {
    for (int i = 0; i < dictionary.size(); i++) {
        cout << i << ": " << dictionary[i] << endl;
    }
    cout << endl << endl;
}

//Checks to see if the words is in the dictionary using a binary search
bool Dictionary::isInDictionary(string word) {
    int first, middle, last;
    first = 0;
    last = int(dictionary.size());
    middle = (first + last) / 2;
    
    while (first <= last) {
        if (debugPrint) {
            cout << word;
            if (word > dictionary[middle]) {
                cout << " > ";
            }
            else {
                cout << " < ";
            }
            cout << dictionary[middle] << endl;
            cout << first << " " << middle << " " << last << endl << endl;
        }
        
        if (dictionary[middle] == word) {
            if (target) {
                target = false;
                return true;
            }
            if (used[middle] == false) {
                used[middle] = true;
                return true;
            }
            return false;
        }
        if (word > dictionary[middle]) {
            first = middle + 1;
        }
        else {
            last = middle - 1;
        }
        middle = (first + last) / 2;
    }
    
    return false;
}
 */
