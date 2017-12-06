//
//  DoublyLinkedList.cpp
//  Word Ladder - Steven Proctor
//
//  Created by Steven Proctor on 9/10/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "DoublyLinkedList.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

DoublyLinkedList::DoublyLinkedList() {
    head = NULL;
    tail = NULL;
}

void DoublyLinkedList::solveLadder(string word) {
    initializeDictionary(int(word.length()));
    firstWord = dictionary[rand()%dictionary.size()];
    lastWord = dictionary[rand()%dictionary.size()];
    solveLadder(firstWord, lastWord);
}

void DoublyLinkedList::solveLadder(string first, string last) {
    solved = false;
    noSolution = false;
    target = true;
    firstWord = first;
    lastWord = last;
    vector<string> word;
    word.push_back(first);
    
    cout << "**************************************************************\n" << endl << endl;
    cout << "Find word ladder from \"" << first << "\" to \"" << last << "\"" << endl;
    
    if (first.size() != last.size()) {
        if (first.size() == 0 || last.size() == 0) {
            //Find two random strings that equal the length of the argument
            
            //Set first and last equal to the random strings
            cout << "***** Needs to find two random words to build a ladder for.\n" << endl;
            return;
        }
        
        else {
            cout << "\"" << first << "\"" << " and " << "\"" << last << "\" are not the same length.\n";
            cout << "Please enter two words of the same length.\n" << endl;
            cout << endl;
            return;
        }
    }
    
    initializeDictionary(int(first.length()));
    //printDictionaryVector();
    
    if (!isInDictionary(last) || !isInDictionary(first)) {
        if (target) {
            cout << "\"" << last << "\" was not found in the dictionary.\n";
        }
        if(!isInDictionary(first)) {
            cout << "\"" << first << "\" was not found in the dictionary.\n";
        }
        cout << endl << endl;
        return;
    }
    
    createNode(word);
    if (print) {cout << printList() << endl;}
    while(!solved && !noSolution) {
        checkSolution(removeNode());
        if (print) {cout << printList() << endl;}
    }
    
    if (solved) {
    cout << "Solved!" << endl;
    cout << "Ladder Size: " << solution.size() << endl;
    cout << "[";
    for (int i = 0; i < solution.size(); i++) {
        cout << solution[i];
        if (i < solution.size() - 1) {
            cout << ",";
        }
    }
    cout << "]\n" << endl << endl;
    }
}

void DoublyLinkedList::createNode(vector<string> word) {
    Node * newNode = new Node;
    newNode->wordLadder = word;
    newNode->prev = tail;
    newNode->next = NULL;
    size++;
    
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    tail->next = newNode;
    tail = newNode;
}

vector<string> DoublyLinkedList::removeNode() {
    if (head == NULL) {
        cout << "There are no Nodes in the queue that can be removed.\n";
        exit(4);
    }
    
    vector<string> deletedLadder = head->wordLadder;
    Node * temp = head;
    
    head = head->next;
    delete temp;
    size--;
    
    if (head == NULL) {tail = NULL;}
    else {head->prev = NULL;}
    
    return deletedLadder;
}

bool DoublyLinkedList::checkSolution(vector<string> currentLadder) {
    if (currentLadder[currentLadder.size() - 1] == lastWord) {
        solution = currentLadder;
        solved = true;
        return true;
    }
    
    isOneAway(currentLadder);
    
    return false;
}

string DoublyLinkedList::printList() {
    stringstream ss;
    
    cout << "Ladder Size: " << tail->wordLadder.size() - 1 << endl;
    if (oneAway.size() > 0) {
        cout << "One Away From " << currentWord << ":" << endl;
        for (int i = 0; i < oneAway.size(); i++) {
            cout << oneAway[i] << " ";
        }
        cout << endl;
    }
    ss << "Partial Solution:\n";
    for (Node * p = head; p != NULL; p = p->next) {
        ss << "[";
        for (int i = 0; i < p->wordLadder.size(); i++) {
            ss << p->wordLadder[i];
            if (i < p->wordLadder.size() - 1) {
                ss << ",";
            }
        }
        ss << "]";
    }
    ss << endl;
    
    return ss.str();
}

void DoublyLinkedList::isOneAway(vector<string> currentLadder) {
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
            //cout << temp << endl;
            if (isInDictionary(temp)) {
                oneAway.push_back(temp);
                createNode(currentLadder);
                tail->wordLadder.push_back(oneAway[oneAway.size()-1]);
                //cout << temp << endl;
            }
        }
    }
    
    if (oneAway.size() == 0 && head == NULL) {
        cout << "There is no solution for this word ladder.\n" << endl << endl;
        noSolution = true;
    }
}

void DoublyLinkedList::initializeDictionary(int wordLength) {
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

void DoublyLinkedList::printDictionaryVector(int length) {
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

void DoublyLinkedList::printDictionaryVector() {
    for (int i = 0; i < dictionary.size(); i++) {
        cout << i << ": " << dictionary[i] << endl;
    }
    cout << endl << endl;
}

bool DoublyLinkedList::isInDictionary(string word) {
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

int DoublyLinkedList::getSize() {
    return size;
}

void DoublyLinkedList::setFile(string file) {
    fileName = file;
}