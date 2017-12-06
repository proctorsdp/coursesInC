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

//Constructor
DoublyLinkedList::DoublyLinkedList() {
    head = NULL;
    tail = NULL;
}

//Generates two random words if user only imputs one word
void DoublyLinkedList::solveLadder(string word) {
    initializeDictionary(int(word.length()));
    firstWord = dictionary[rand()%dictionary.size()];
    lastWord = dictionary[rand()%dictionary.size()];
    solveLadder(firstWord, lastWord);
}

//Driving function to solve word ladder
void DoublyLinkedList::solveLadder(string first, string last) {
    solved = false;
    noSolution = false;
    target = true;
    firstWord = first;
    lastWord = last;
    vector<string> word;
    word.push_back(first);
    enqueued = 0;
    dequeued = 0;
    
    fstream fout;
    fout.open(outputFile);
    fout.seekp(0, ios::end);
    
    //Title
    cout << "**************************************************************\n" << endl << endl;
    cout << "Find word ladder from \"" << first << "\" to \"" << last << "\"" << endl;
    //Print to file
    fout << "**************************************************************\n" << endl << endl;
    fout << "Find word ladder from \"" << first << "\" to \"" << last << "\"" << endl;
    
    
    //Checks if the two words are the same length
    if (first.size() != last.size()) {
        cout << "\"" << first << "\"" << " and " << "\"" << last << "\" are not the same length.\n";
        cout << "Please enter two words of the same length.\n" << endl;
        cout << endl;
        //Print to file
        fout << "\"" << first << "\"" << " and " << "\"" << last << "\" are not the same length.\n";
        fout << "Please enter two words of the same length.\n" << endl;
        fout << endl;
        return;
    }
    
    //Creates a vector of all words from the dictionary that have the same length
    initializeDictionary(int(first.length()));
    
    //Checks if the two words are in the dictionary
    if (!isInDictionary(last) || !isInDictionary(first)) {
        if (target) {
            cout << "\"" << last << "\" was not found in the dictionary.\n";
            //print to file
            fout << "\"" << last << "\" was not found in the dictionary.\n";
        }
        if(!isInDictionary(first)) {
            cout << "\"" << first << "\" was not found in the dictionary.\n";
            //print to file
            fout << "\"" << first << "\" was not found in the dictionary.\n";
        }
        cout << endl << endl;
        //print to file
        fout << endl << endl;
        return;
    }
    fout.close();
    
    //Creates the first Node
    createNode(word);
    
    //If print is true, print the word ladder in each node to the screen
    if (print) {cout << printList() << endl;}
    
    //Repeats process until ladder is solved
    while(!solved && !noSolution) {
        outputList();
        checkSolution(removeNode());
        if (print) {cout << printList() << endl;}
    }
    
    //If ladder was solved, output solution
    if (solved) {
        outputSolution();
        cout << "Ladder Solved using Linked List!" << endl;
        cout << "Ladder Size: " << solution.size() << endl;
        cout << "[";
        for (int i = 0; i < solution.size(); i++) {
            cout << solution[i];
            if (i < solution.size() - 1) {
                cout << ",";
            }
        }
        cout << "]\n";
        cout << "Ladders Enqueued: " << enqueued << endl;
        cout << "Ladders Dequeued: " << dequeued << endl;
        cout << endl << endl;
    }
}

//Prints solution to output file
void DoublyLinkedList::outputSolution() {
    fstream fout;
    fout.open(outputFile);
    fout.seekp(0, ios::end);
    
    fout << "Ladder Solved using Linked List!" << endl;
    fout << "Ladder Size: " << solution.size() << endl;
    fout << "[";
    for (int i = 0; i < solution.size(); i++) {
        fout << solution[i];
        if (i < solution.size() - 1) {
            fout << ",";
        }
    }
    fout << "]\n" << endl << endl;
    fout.close();
}

//Creates a new node and inserts on the end of the queue
void DoublyLinkedList::createNode(vector<string> word) {
    Node * newNode = new Node;
    newNode->wordLadder = word;
    newNode->prev = tail;
    newNode->next = NULL;
    size++;
    enqueued++;
    
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    tail->next = newNode;
    tail = newNode;
}

//Removes the first node of the queue and returns the word ladder from the node
vector<string> DoublyLinkedList::removeNode() {
    //Should not execute - FAIL SAFE
    if (head == NULL) {
        cout << "There are no Nodes in the queue that can be removed.\n";
        exit(4);
    }
    
    vector<string> deletedLadder = head->wordLadder;
    Node * temp = head;
    
    head = head->next;
    delete temp;
    size--;
    dequeued++;
    
    if (head == NULL) {tail = NULL;}
    else {head->prev = NULL;}
    
    return deletedLadder;
}

//Checks to see if the ladder has been solved, continues the search if it hasn't
bool DoublyLinkedList::checkSolution(vector<string> currentLadder) {
    if (currentLadder[currentLadder.size() - 1] == lastWord) {
        solution = currentLadder;
        solved = true;
        return true;
    }
    
    isOneAway(currentLadder);
    
    return false;
}

//Prints the word ladder contained in each node
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

//Outputs information to txt file
void DoublyLinkedList::outputList() {
    stringstream ss;
    fstream fout;
    fout.open(outputFile);
    fout.seekp(0, ios::end);
    
    fout << "Ladder Size: " << tail->wordLadder.size() - 1 << endl;

    if (oneAway.size() > 0) {
        fout << "One Away From " << currentWord << ":" << endl;
        for (int i = 0; i < oneAway.size(); i++) {
            fout << oneAway[i] << " ";
        }
        fout << endl;
    }
    
    fout << "Partial Solution:\n";
    
    for (Node * p = head; p != NULL; p = p->next) {
        fout << "[";
        for (int i = 0; i < p->wordLadder.size(); i++) {
            fout << p->wordLadder[i];
            if (i < p->wordLadder.size() - 1) {
                fout << ",";
            }
        }
        fout << "]";
    }
    fout << endl << endl;
    fout.close();
}

//Generates a list of words that are one letter different from the last word on the current ladder
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

//Prints a specific number of words contained in the dictionary vector
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

//Prints all words contained in the dictionary vector
void DoublyLinkedList::printDictionaryVector() {
    for (int i = 0; i < dictionary.size(); i++) {
        cout << i << ": " << dictionary[i] << endl;
    }
    cout << endl << endl;
}

//Checks to see if the words is in the dictionary using a binary search
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

//Returns size of the queue
int DoublyLinkedList::getSize() {
    return size;
}

//Sets the name of the dictionary file
void DoublyLinkedList::setFile(string file) {
    fileName = file;
}

void DoublyLinkedList::setOutput(string out) {
    outputFile = out;
}