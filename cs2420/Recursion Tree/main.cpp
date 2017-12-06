//
//  main.cpp
//  Recursion Tree
//
//  Created by Steven Proctor on 9/24/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "assert.h"
#include "PreOrder_Tree.h"

using namespace std;

int main() {
    
    ifstream inf;
    ofstream outf;
    outf.open("prog2Out.txt");
    inf.open("prog2In.txt");
    assert(inf);
    assert(outf);
    const int SIZE = 12;
    Tree t[SIZE];
    
    //Test buildFromPrefix Function
    cout << "****** BUILDING TREES ******\n";
    for (int i = 0; i < SIZE; i++)
        t[i].buildFromPrefix(inf);
    
    
    //Test printTree and fringe Function
    cout << "****** PRINTING TREE ******\n";
    cout << "****** COUNTING FRINGES ******\n";
    for (int i = 0; i < SIZE; i++){
        cout << "Tree" << i << "\n" << t[i].printTree() << endl;
        outf << "Tree" << i << "\n" << t[i].printTree() << endl;
        cout << "FRINGE " <<t[i].fringe() << endl;
        cout << endl << endl;
    }
    cout << endl << endl;
    
    
    //Test findWord Function
    cout << "****** SEARCHING FOR WORDS ******\n";
    if (t[0].findWord("dins") == NULL) cout << "dins not found\n";
    if (t[0].findWord("tone") == NULL) cout << "tone not found\n";
    cout << "****** CAPITALIZING TREE ******\n";
    t[0].upCase();
    cout << t[0].printTree();
    cout << "****** SEARCHING FOR WORDS ******\n";
    if (t[0].findWord("guck") == NULL) cout << "guck not found\n";
    if (t[0].findWord("TONE") == NULL) cout << "TONE not found\n";
    cout << endl << endl;
    
    
    //Test makeEmpty Function
    cout << "****** EMPTYING TREE ******\n";
    t[7].makeEmpty();
    cout << "empty tree fringe " << t[7].fringe() << endl;
    cout << endl << endl;
    
    
    //Test nodesInLevel Function
    cout << "****** COUNTING NODES ON A LEVEL ******\n";
    for (int i = 0; i < SIZE; i++){
        cout << "NodesInLevel 2 of tree" << i << " " << t[i].nodesInLevel(2) << endl;
    }
    cout << endl << endl;
    
    
    //Test clone Function
    cout << "****** PRINTING TREES ******\n";
    cout << " TREE 3\n" <<  t[3].printTree() << endl;
    cout << " TREE 10\n" << t[10].printTree() << endl;
    cout << "****** CLONING TREE ******\n";
    t[3] = t[10].clone();
    cout << "****** CAPITALIZING TREE ******\n";
    t[3].upCase();
    cout << "****** PRINTING TREES ******\n";
    cout << " TREE 3 cloned\n" << t[3].printTree() << endl;
    cout << " TREE 10\n" << t[10].printTree() << endl;
    cout << endl << endl;
    
    
    //Test isIsomorphic Function
    cout << "****** FINDING ISOMORPHIC TREES ******\n";
    for (int i = 0; i < SIZE; i++)
        for (int j = i + 1; j < SIZE; j++)
            if (t[i].isIsomorphic( t[j])) cout << "Two trees are isomorphic Tree:" << i << " Tree:" << j << endl;
    cout << endl << endl;
    
    
    //Test commonAncestor Function
    cout << "****** FINDING COMMON ANCESTORS ******\n";
    cout << "Common Ancestor of lade and gunk " << t[2].commonAncestor("lade", "gunk") << endl;
    cout << "Common Ancestor of luce and gunk " << t[1].commonAncestor("luce", "gunk") << endl;
    cout << "Common Ancestor of lick and dene " << t[1].commonAncestor("lick", "dene") << endl;
    cout << "Common Ancestor of lick and muck " << t[1].commonAncestor("lick", "muck") << endl;
    cout << endl << endl;
    
    
    //Test toPreOrder Function
    cout << "****** PRINTING PREORDER TREES ******\n";
    for (int i = 0; i < SIZE; i++){
        cout << "Tree" << i << ": " << t[i].toPreorder() << endl;
    }
    cout << endl << endl;
    
    
    //type any key to close
    char c;
    cin >> c;
    outf.close();
    
    
    return 0;
}