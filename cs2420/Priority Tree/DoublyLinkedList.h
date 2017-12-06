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
#include <fstream>
#include "avlTreeTemplate.h"

using namespace std;

struct Node {
    vector<string> wordLadder;      //Stores the word ladder
    Node * next;                    //Points to next Node
    Node * prev;                    //Points to previous Node
};

class DoublyLinkedList {
public:
    DoublyLinkedList();                 //Constructor
    void createNode(vector<string>);    //Create new node - add to queue
    vector<string> removeNode();        //Delete the head of the queue - return word ladder
    string printList();                 //Prints the word ladder contained in each node
    int getSize();                      //Returns size of queue
    void isOneAway(vector<string>);     //Generates a list of words one letter different from arguement
    bool isInDictionary(string);        //Checks to see if the word can be found in the dictionary
    void solveLadder(string, string);   //Driving function to find ladder between two words
    void solveLadder(string);           //Generates two random words of a given length
    void initializeDictionary(int);     //Creates a dictionary of words based on a given length
    bool checkSolution(vector<string>); //Checks to see if the ladder has been solved
    void printDictionaryVector();       //Prints the entire dictionary vector
    void printDictionaryVector(int);    //Prints a specified amount of the dictionary vector
    void setFile(string);               //Sets the name of the dictionary file
    void outputList();                  //Outputs the words ladders in each node to a file
    void setOutput(string);             //Sets output file name
    void outputSolution();              //Prints solution to file
    bool checkHead();                   //Returns false if head equals NULL
    
private:
    Node * head;                    //Points to front of queue
    Node * tail;                    //Points to end of queue
    int size = 0;                   //Tracks size of queue
    int enqueued;
    int dequeued;
    bool solved;                    //True if ladder is solved
    bool noSolution;                //True if ladder has no solution
    vector<string> dictionary;      //Stores words of a specified length taken from dictionary
    vector<bool> used;              //Tracks whether a word in the dictionary has been used or not
    vector<string> oneAway;         //Stores all words one letter different from a given word
    vector<string> solution;        //Stores the solution to the ladder
    string firstWord, lastWord;     //First word of the ladder & last word of the ladder
    string currentWord;             //The last word of a given ladder
    string fileName;                //Name of dictionary file
    string outputFile;              //Name of txt output file
    bool target;                    //Prevents the last word from being marked 'used' intially
    bool print = false;             //Change to true to print the word ladder contained in each node
    bool debug = false;             //Change to true to debug the dictionary
    bool debugPrint = false;        //Change to true to debug the print function
};

#endif /* DoublyLinkedList_h */
