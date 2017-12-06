//
//  tree.cpp
//  Word Frequency
//
//  Created by Steven Proctor on 4/18/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "tree.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;


WordTree::WordTree() {
    root = NULL;
}


void WordTree::insert(string newWord) {
    root = rInsert(root, newWord);
}

void WordTree::insert(string word, int frequency) {
    root = rInsert(root, word, frequency);
}


void WordTree::Delete(string target) {
    root = rDelete(root, target);
}


void WordTree::print() {
    rPrint(root);
}


void WordTree::preOrderPrint(){
    preRPrint(root);
}


void WordTree::postOrderPrint(){
    postRPrint(root);
}


int WordTree::size(){
    return rSize(root);
}


int WordTree::Height(){
    return rHeight(root);
}


bool WordTree::isInTree(string t){
    return rIsInTree(root, t);
}


WordNode * WordTree::rMinNode(WordNode * subRoot) {
    if(!subRoot) return 0;
    if(!subRoot->left) return subRoot;
    return rMinNode(subRoot->left);
}



void WordTree::rPrint(WordNode * subRoot) {
    if (!subRoot) {return;}
    rPrint(subRoot->left);
    cout << subRoot->frequency << " " << subRoot->word << endl;
    rPrint(subRoot->right);
}



void WordTree::preRPrint(WordNode * subRoot) {
    if (!subRoot) {return;}
    cout << subRoot->word << endl;
    preRPrint(subRoot->left);
    preRPrint(subRoot->right);
}



void WordTree::postRPrint(WordNode * subRoot) {
    if (!subRoot) {return;}
    postRPrint(subRoot->left);
    postRPrint(subRoot->right);
    cout << subRoot->word << endl;
}



void WordTree::load(string file) {
    fstream fin;
    string input;
    fin.open(file);
    bool skip;
    
    while (fin >> input) {
        skip = false;
        
        for (int i = 0; i < input.size(); i++) {
            while (input[i] < 65 || input[i] > 122) {
                if(input[i] == NULL) {break;}
                input.erase(i, 1);
            }
            while (input[i] > 90 && input [i] < 97) {
                if(input[i] == NULL) {break;}
                input.erase(i, 1);
            }
        }
        
        for (int i = 0; i < input.size(); i++) {
            if (input[i] > 64 && input[i] < 91) {
                input[i]+= 32;
            }
        }
        
        if (input[0] == NULL) {skip = true;}
        
        if (!skip) { insert(input); }
    }
    
    fin.close();
}



void WordTree::save(string file) {
    rSave(root, file);
}



void WordTree::rSave(WordNode * subRoot, string file) {
    if (!subRoot) {return;}
    rSave(subRoot->left, file);
    printToFile(subRoot, file);
    rSave(subRoot->right, file);
}



void WordTree::printToFile(WordNode * subRoot, string file) {
    fstream fout;
    fout.open(file);
    fout.seekp(0, ios::end);
    
    fout << subRoot->frequency;
    fout << ": ";
    fout << subRoot->word;
    fout << endl;
    
    fout.close();
}



void WordTree::copyTo(WordTree & newTree) {
    rCopy(root, newTree);
}



void WordTree::rCopy(WordNode * subRoot, WordTree & newTree) {
    if(!subRoot) {return;}
    rCopy(subRoot->left, newTree);
    newTree.insert(subRoot->word, subRoot->frequency);
    rCopy(subRoot->right, newTree);
}



WordNode * WordTree::rInsert(WordNode * subRoot, string newWord) {
    if (isInTree(newWord)) {return subRoot;}
    
    if (!subRoot) {
        WordNode * newNode = new WordNode;
        newNode->word = newWord;
        newNode->left = 0;
        newNode->right = 0;
        return newNode;
    }
    
    if(newWord < subRoot->word) { subRoot->left = rInsert(subRoot->left, newWord); }
    
    else { subRoot->right = rInsert(subRoot->right, newWord); }
    
    return subRoot;
}



WordNode * WordTree::rInsert(WordNode * subRoot, string newWord, int frequency) {
    if (!subRoot) {
        WordNode * newNode = new WordNode;
        newNode->word = newWord;
        newNode->frequency = frequency;
        newNode->left = 0;
        newNode->right = 0;
        return newNode;
    }
    
    if(frequency > subRoot->frequency) { subRoot->left = rInsert(subRoot->left, newWord, frequency); }
    
    else if (frequency < subRoot->frequency) { subRoot->right = rInsert(subRoot->right, newWord, frequency); }
    
    else {
        if(newWord < subRoot->word) { subRoot->left = rInsert(subRoot->left, newWord, frequency); }
        
        else { subRoot->right = rInsert(subRoot->right, newWord, frequency); }
    }
    
    return subRoot;
}



WordNode * WordTree::rDelete(WordNode * subRoot, string target) {
    if (!subRoot) return subRoot;
    if (target == subRoot->word) {
        subRoot = deleteNode(subRoot);
        return subRoot;
    }
    if (target < subRoot->word) {
        subRoot->left = rDelete(subRoot->left, target);
    }
    else {
        subRoot->right = rDelete(subRoot->right, target);
    }
    return subRoot;
}



WordNode * WordTree::deleteNode(WordNode * subRoot) {
    //Case I: No Children
    if (!subRoot->left && !subRoot->right) {
        delete subRoot;
        return 0;
    }
    
    //Case II: One Child
    if(!subRoot->left) {
        WordNode * returnNode = subRoot->right;
        delete subRoot;
        return returnNode;
    }
    if(!subRoot->right) {
        WordNode * returnNode = subRoot->left;
        delete subRoot;
        return returnNode;
    }
    
    //Case II: Two Children
    WordNode * returnNode = subRoot->right;
    rMinNode(subRoot->right)->left = subRoot->left;
    delete subRoot;
    return returnNode;
}



int WordTree::rSize(WordNode * subRoot) {
    if(!subRoot) {return 0;}
    return rSize(subRoot->left)+1+rSize(subRoot->right);
}



int WordTree::rHeight(WordNode * subRoot) {
    if(!subRoot) {return 0;}
    int r = rHeight(subRoot->right);
    int l = rHeight(subRoot->left);
    if (r > l) { return r + 1; }
    else { return l + 1; }
}



bool WordTree::rIsInTree(WordNode * subRoot, string target) {
    if(!subRoot) {return false;}
    if(subRoot->word == target) {subRoot->frequency++; return true;}
    else if(target < subRoot->word) {return rIsInTree(subRoot->left, target);}
    return rIsInTree(subRoot->right, target);
}