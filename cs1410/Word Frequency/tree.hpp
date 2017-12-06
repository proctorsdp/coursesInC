//
//  tree.hpp
//  Word Frequency
//
//  Created by Steven Proctor on 4/18/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;


struct WordNode {
    string word;
    int frequency = 1;
    WordNode *left = NULL;
    WordNode *right = NULL;
};


class WordTree {
public:
    
    WordTree();
    
    void insert(string newWord);
    
    void insert(string word, int frequency);
    
    void copyTo(WordTree & tree);
    
    void save(string file);
    
    void Delete(string target);
    
    void print();
    
    void preOrderPrint();
    
    void postOrderPrint();
    
    int size();
    
    int Height();
    
    bool isInTree(string t);
    
    void load(string file);
    
    
private:
    
    WordNode * root;
    
    WordNode * rMinNode(WordNode * subRoot);
    
    void rPrint(WordNode * subRoot);
    
    void preRPrint(WordNode * subRoot);
    
    void postRPrint(WordNode * subRoot);
    
    void rCopy(WordNode * subRoot, WordTree & tree);
    
    void rSave(WordNode * subRoot, string file);
    
    void printToFile(WordNode * subRoot, string file);
    
    WordNode * rInsert(WordNode * subRoot, string newWord);
    
    WordNode * rInsert(WordNode * subRoot, string newWord, int frequency);
    
    WordNode * rDelete(WordNode * subRoot, string target);
    
    WordNode * deleteNode(WordNode * subRoot);
    
    int rSize(WordNode * subRoot);
    
    int rHeight(WordNode * subRoot);
    
    bool rIsInTree(WordNode * subRoot, string target);
    
};

#endif /* tree_hpp */
