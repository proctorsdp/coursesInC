//
//  PreOrder_Tree.h
//  Recursion Tree
//
//  Created by Steven Proctor on 9/28/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef PreOrder_Tree_h
#define PreOrder_Tree_h

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include "assert.h"

using namespace std;


struct Node {
    string word;        //Contains the word
    int numSubTrees;    //Contains the number of children the node has
    int size = 1;       //Contains the size of the subtree
    int kidsToAdd;      //Tracks how many kids still need to be added
    Node * leftChild;   //Points to the leftmost child
    Node * rightSib;    //Points to the next sibling
    Node * parent;      //Points to the parent
};



class Tree {
public:
    Tree(void) { root = NULL; }
    void makeEmpty() { makeEmpty(root); }
    void makeEmpty(Node *& r);
    string printTree(string, Node *);
    string printTree(string treeStr = ""){ return printTree(treeStr, root); }
    string toPreorder(Node * n);
    string toPreorder() { return toPreorder(root);}
    void buildFromPrefix(ifstream & inf);
    Node * buildNodeFromPrefix(string, int , Node *);
    Node * findWord(string word, Node * r);
    Node * findWord(string word) { return findWord(word, root); }
    void upCase(Node* n);
    void upCase(){ upCase(root); }
    Tree clone();
    Node * clone(Node * n, Node * p);
    int fringe() { return fringe(root); }
    int fringe(Node * n);
    int nodesInLevel(int level){ return nodesInLevel(level, root); };
    int nodesInLevel(int level, Node * r);
    bool isIsomorphic(Tree &t2) { return isIsomorphic(root, t2.root); }
    bool isIsomorphic(Node *r1, Node *r2);
    string commonAncestor(string s1, string s2);
    Node * commonAncestor(Node* n1, Node *n2);
    
private:
    Node * root;                //Points to the root of the tree
    Node * currParent;          //Points to the currentparent of the siblings being added
    bool nodeInserted = false;  //Returns true if a node has been inserted
    bool debugBuild = false;    //If true: prints debug information for the build function
    bool debugClone = false;    //If true: prints debug information for the clone function
};



//Reads in from file, and calls build function
void Tree::buildFromPrefix(ifstream & inf) {
    string line;
    string newWord;
    
    int numTrees;
    int i = 0;
    int j = 0;
    int k = 0;
    
    //grabs one line, or tree, from the file
    getline(inf, line);
    
    //breaks the line into words, sends to build function
    while (line[j] != '\0') {
        i = 0;
        k = j;
        
        while (line[j] != ' ') { j++; i++; }
        
        newWord = line.substr(k, i);
        numTrees = line[++j] - 48;
        
        if (line[j+1] != '\0') { j+=2; }
        else { j++; }
        
        nodeInserted = false;
        root = buildNodeFromPrefix(newWord, numTrees, root);
        //if (root->kidsToAdd == 0) {finishTree = true;}
        
        newWord.clear();
        numTrees = '\0';
    }
    line.clear();
}



//Creates a new Node for given information and stores it in the tree
Node * Tree::buildNodeFromPrefix(string newWord, int numTrees, Node * subroot) {
    //if no node exists, creates and inserts new node
    if (!subroot) {
        //ensures the root gets created
        if (root != NULL) {
            //prevents children from being connected to the wrong parent
            if (currParent->kidsToAdd == 0) {return subroot;}
        }
        //Creates node, sets values
        nodeInserted = true;
        Node * newNode = new Node;
        newNode->size += numTrees;
        newNode->word = newWord;
        newNode->numSubTrees = numTrees;
        newNode->kidsToAdd = numTrees;
        
        //Sets node pointers
        newNode->parent = currParent;
        newNode->leftChild = NULL;
        newNode->rightSib = NULL;
        
        //Increments the number of kids that still need to be added
        if (newNode->parent != NULL) { (newNode->parent)->kidsToAdd--; }
        
        //Prints debugging info for each node if debugBuild is set to true
        if(debugBuild) {
            cout << "New Node Built: \n";
            cout << "Word: " << newNode->word << endl;
            cout << "SubTrees: " << newNode->numSubTrees << endl;
            cout << "Size: " << newNode->size << endl;
            if (newNode->parent != NULL) {cout << "Parent: " << (newNode->parent)->word << endl;}
            cout << endl;
        }
        
        //returns the newest node
        return newNode;
    }
    
    //Traverses left down the tree, increments subtree size
    if (subroot->numSubTrees != 0) {
        subroot->size += numTrees;
        currParent = subroot;
        subroot->leftChild = buildNodeFromPrefix(newWord, numTrees, subroot->leftChild);
    }
    
    //Decrements the size of the subtree
    if (!nodeInserted) {subroot->size -= numTrees;}
    if (subroot == root) {return subroot;}
    
    //Traverses right across the tree
    if ((!nodeInserted) && ((subroot->parent)->numSubTrees > 1)) {
        currParent = subroot->parent;
        subroot->rightSib = buildNodeFromPrefix(newWord, numTrees, subroot->rightSib);
    }
    
    //Corrects subtree size
    if (subroot->size < 0) {subroot->size = 1;}
    
    //returns root of tree
    return subroot;
}



//Prints the tree with indent formatting
string Tree::printTree(string indent, Node * n) {
    stringstream ss;
    
    //base case
    if (!n) {return ss.str();}
    
    //Collect information
    ss << indent << n->word << " [" << n->size << ":" << n->numSubTrees << "]\n";
    
    //Traverse left
    ss << printTree(indent += "  ", n->leftChild);
    
    //remove indent
    indent.pop_back();
    indent.pop_back();
    
    //Traverse right
    ss << printTree(indent, n->rightSib);
    
    //returns the indent formatted tree
    return ss.str();
}



//Prints the preorder list of the tree
string Tree::toPreorder(Node * n) {
    stringstream ss;
    
    //base case
    if (!n) {return "";}
    
    //collect information
    ss << n->word << " " << n->numSubTrees << " ";
    
    //traverse left
    ss << toPreorder(n->leftChild);
    
    //traverse right
    ss << toPreorder(n->rightSib);
    
    //returns the preOrder list
    return ss.str();
}



//delete tree
void Tree::makeEmpty(Node *& r) {
    //base case
    if (!r) {return;}
    
    //traverse left
    makeEmpty(r->leftChild);
    
    //traverse right
    makeEmpty(r->rightSib);
    
    //delete node
    r = NULL;
    delete[] r;
    //Vicki Allan asked me to add the "r = NULL" line before delete after trying to debug the delete function with me
}



//Capitalize every letter in the tree
void Tree::upCase(Node* n) {
    //base case
    if (!n) {return;}
    
    //Capitalize word
    string temp = n->word;
    for (int i = 0; i < (n->word).length(); i++) { temp[i] -= 32; }
    n->word = temp;
    
    //traverse left
    upCase(n->leftChild);
    
    //travers right
    upCase(n->rightSib);
}



//count number of leafs
int Tree::fringe(Node * n) {
    //increment count
    if (!n) {return 1;}
    int count = 0;
    
    //traverse left
    count += fringe(n->leftChild);
    
    //prevents the last right sibling from being counted as two leafs
    if (n->rightSib != NULL) {
        //traverse right
        count += fringe(n->rightSib);
    }
    
    //returns the number of leafs
    return count;
}



//Counts the number of nodes on a given level
int Tree::nodesInLevel(int level, Node * r) {
    //base case
    if (!r) {return 0;}
    
    //increments count
    if (level == 0) { return nodesInLevel(level, r->rightSib) + 1;}
    int numNodes = 0;
    
    //traverse left
    numNodes += nodesInLevel(level-1, r->leftChild);
    
    //traverse right
    numNodes += nodesInLevel(level, r->rightSib);
    
    //returns the number of nodes in the given level
    return numNodes;
}



//Returns a pointer to the node containing a given word
Node * Tree::findWord(string word, Node * r) {
    if (!r) {return NULL;}
    
    //returns pointer to node containing word
    if (word == r->word) {return r;}
    
    //traverse left
    Node * find = findWord(word, r->leftChild);
    if (find) {return find;}
    
    //traverse right
    else return findWord(word, r->rightSib);
}



//returns true if two trees have the same shape
bool Tree::isIsomorphic(Node *r1, Node *r2) {
    //base case if not isomorphic
    if ((!r1 && r2) || (r1 && !r2)) {return false;}
    
    //base case if isomorphic
    if (!r1 && !r2) {return true;}
    
    //traverse left, then right
    if (isIsomorphic(r1->leftChild, r2->leftChild)) {return isIsomorphic(r1->rightSib, r2->rightSib);}
    
    //returns false if not isomorphic
    else return false;
}



//creates a new tree, calls clone, and returns the new tree
Tree Tree::clone() {
    //new tree
    Tree newTree;
    
    //populates new tree
    newTree.root = newTree.clone(root, newTree.root);
    
    //returns new tree
    return newTree;
}



//makes a deep copy of a given tree and fills a new tree
Node * Tree::clone(Node * n, Node * p) {
    //base case
    if (!n) {return NULL;}
    
    //Creates node, populates information
    p = new Node;
    p->word = n->word;
    p->numSubTrees = n->numSubTrees;
    p->size = n->size;
    p->parent = currParent;
    
    //if true, debugs the clone function
    if(debugClone) {
        cout << "New Node Built: \n";
        cout << "Word: " << p->word << endl;
        cout << "SubTrees: " << p->numSubTrees << endl;
        cout << "Size: " << p->size << endl;
        if (p->parent != NULL) {cout << "Parent: " << (p->parent)->word << endl;}
        cout << endl;
    }
    
    //traverse left
    currParent = n;
    p->leftChild = clone(n->leftChild, p->leftChild);
    
    //traverse right
    currParent = n->parent;
    p->rightSib = clone(n->rightSib, p->rightSib);
    
    //return root of new tree
    return p;
}



//determines if the words are in the tree and calls commonAncestor
string Tree::commonAncestor(string s1, string s2) {
    //variables
    stringstream ss;
    Node * first = findWord(s1);
    Node * second = findWord(s2);
    
    //Checks if the words are in the tree
    if (!first) {
        ss << "~ " << s1 << " was not found in the tree\n";
        return ss.str();
    }
    if (!second) {
        ss << "~ " << s2 << " was not found in the tree\n";
        return ss.str();
    }
    
    //locates the common ancestor
    ss << "is: " << (commonAncestor(first, second))->word;
    
    //return the common ancestor
    return ss.str();
}



//returns the pointer to the nearest common ancestor
Node * Tree::commonAncestor(Node* n1, Node *n2) {
    //variables
    const int SIZE = 20;
    int i = 0;
    Node * ancestor1[SIZE], * ancestor2[SIZE];
    
    //empties the node * arrays
    for (int i = 0; i < SIZE; i++) {
        ancestor1[i] = NULL;
        ancestor2[i] = NULL;
    }
    
    //creates an array of each node's ancestors
    while (n1 != NULL && n2 != NULL) {
        if (n1) {
            ancestor1[i] = n1;
            n1 = n1->parent;
        }
        if (n2) {
            ancestor2[i++] = n2;
            n2 = n2->parent;
        }
    }
    
    //compares the ancestors to find the first shared ancestor
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (ancestor1[i] == ancestor2[j]) {
                //return pointer to ancestor
                return ancestor1[i];
            }
        }
    }
    
    //return null if no ancestor
    return NULL;
}


#endif /* PreOrder_Tree_h */
