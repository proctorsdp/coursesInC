//
//  DoublyLinkedList.h
//  Word Ladder - Steven Proctor
//
//  Created by Steven Proctor on 9/10/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Node {
    vector<string> wordLadder;
    Node * next;
    Node * prev;
};

class DoublyLinkedList {
public:
    DoublyLinkedList();
    void createNode(vector<string>);
    vector<string> removeNode();
    string printList();
    int getSize();
    void isOneAway(vector<string>);
    bool isInDictionary(string);
    void solveLadder(string, string);
    void solveLadder(string);
    void initializeDictionary(int);
    bool checkSolution(vector<string>);
    void printDictionaryVector();
    void printDictionaryVector(int);
    void setFile(string);
    
private:
    Node * head;
    Node * tail;
    int size = 0;
    bool solved;
    bool noSolution;
    vector<string> dictionary;
    vector<bool> used;
    vector<string> oneAway;
    vector<string> solution;
    string firstWord, lastWord;
    string currentWord;
    string fileName;
    bool target;
    bool print = false;
    bool debug = false;
    bool debugPrint = false;
};


#endif /* DoublyLinkedList_h */
