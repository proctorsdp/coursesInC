//
//  main.cpp
//  Hash_Tables
//
//  Created by Steven Proctor on 10/18/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include "HashTable.h"

using namespace std;

const int LONGESTWORD = 75;

struct Node {
    string word;
    int timesUsed = 0;
    
    string toString() {
        stringstream ss;
        ss << word << " x" << timesUsed;
        return ss.str();
    }
};

ostream& operator << (ostream & ss, Node & gs) {
    ss << gs.toString();
    return ss;
}

int letterScore(string word) {
    int score = 0;
    for (int i = 0; i < word.length(); i++) {
        int letter = word[i] - 'a';
        if (letter == 0 || letter == 4 || letter == 8 || letter == 11 || letter == 13 || letter == 14 || (16 < letter && letter < 21)) {
            score += 1;
        }
        else if (letter == 3 || letter == 6) {
            score += 2;
        }
        else if (letter == 1 || letter == 2 || letter == 12 || letter == 15) {
            score += 3;
        }
        else if (letter == 5 || letter == 7 || letter == 21 || letter == 22 || letter == 24) {
            score += 4;
        }
        else if (letter == 10) {
            score += 5;
        }
        else if (letter == 9 || letter == 23) {
            score += 8;
        }
        else {score += 10;}
    }
    return score;
}

int lengthScore(string word) {
    int score = 0;
    int length = word.length();
    if (length > 7) {score += 6;}
    else if (length < 3) {score += 0;}
    else {score += length - 2;}
    return score;
}

int bonusScore(int timesUsed) {
    int score = 0;
    if (timesUsed == 0) {score += 5;}
    else if (timesUsed < 4) {score += 4;}
    else if (timesUsed < 7) {score += 3;}
    else if (timesUsed < 10) {score += 2;}
    else {score += 1;}
    return score;
}

void emptyArray(int a[]) {
    for (int i = 0; i < LONGESTWORD; i++) {a[i] = 0;}
    return;
}

string printFrequency(int a[]) {
    stringstream ss;
    ss.str("");
    ss << "Length Frequency: \n";
    ss << "-----------------" << endl;
    for (int i = 0; i < LONGESTWORD; i++) {
        if (a[i] != 0) {
            ss << i << " letter words: x" << a[i] << endl;
        }
    }
    return ss.str();
}

string gameResults(HashTable<string, Node> Test, int score, int run, int a[]) {
    stringstream gameText;
    
    gameText << "******** Game " << run << " ********" << endl;
    gameText << Test.toString();
    
    gameText << endl;
    gameText << "Score: " << score << endl;
    gameText << "------------" << endl;
    gameText << "# of Finds: " << Test.getNumFinds() << endl;
    gameText << "# of Probes: " << Test.getNumProbes() << endl;
    gameText << "# of Items: " << Test.getNumItems() << endl;
    gameText << endl;
    
    gameText << printFrequency(a) << endl;
    gameText << endl << endl;
    
    return gameText.str();
}

int main() {
    
    HashTable<string, Node> Test;
    stringstream fileName, outputFile, gameText;
    string newWord;
    
    fstream fin, fout;
    
    outputFile << "gameResults.txt";
    fout.open(outputFile.str());
    if(!fout) {cout << "ERROR\nCannot save to: " << outputFile.str() << ", File Not Found.\n";}
    
    for (int i = 0; i < 5; i++) {
        int score = 0;
        
        int wordLengths[LONGESTWORD];
        emptyArray(wordLengths);
        
        fileName << "game" << i << ".txt";
        fin.open(fileName.str());
        if(!fin) {cout << "ERROR\nCannot open: " << fileName.str() << ", File Not Found.\nQuitting.\n"; return -9;}
    
        while(fin >> newWord) {
            if (!Test.find(newWord)) {
                Node * newNode = new Node;
                newNode->word = newWord;
                newNode->timesUsed++;
                Test.insert(newWord, newNode);
            }
            else {
                Test.find(newWord)->timesUsed++;
            }
            wordLengths[newWord.length()]++;
            score += letterScore(newWord) * lengthScore(newWord) * bonusScore(Test.find(newWord)->timesUsed - 1);
            
        }
        
        cout << gameResults(Test, score, i, wordLengths);
        fout << gameResults(Test, score, i, wordLengths);
        
        fin.close();
        fileName.str("");
        gameText.str("");
        Test.makeEmpty();
    }
    
    fout.close();
    
    return 0;
}
