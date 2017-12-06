//
//  Dictionary.hpp
//  Word Ladder - Steven Proctor
//
//  Created by Steven Proctor on 10/11/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef Dictionary_hpp
#define Dictionary_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dictionary {
    
public:
    
    void isOneAway(vector<string>);     //Generates a list of words one letter different from arguement
    void initializeDictionary(int);     //Creates a dictionary of words based on a given length
    bool checkSolution(vector<string>); //Checks to see if the ladder has been solved
    void printDictionaryVector();       //Prints the entire dictionary vector
    void printDictionaryVector(int);    //Prints a specified amount of the dictionary vector
    bool isInDictionary(string);        //Checks to see if the word can be found in the dictionary
    
    
private:
    
    vector<string> oneAway;         //Stores all words one letter different from a given word
    vector<string> dictionary;      //Stores words of a specified length taken from dictionary
    vector<bool> used;              //Tracks whether a word in the dictionary has been used or not
    
};

#endif /* Dictionary_hpp */
