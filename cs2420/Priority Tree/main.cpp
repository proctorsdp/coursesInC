//
//  main.cpp
//  Word Ladder - Steven Proctor
//
//  Created by Steven Proctor on 9/10/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <string>
#include "DoublyLinkedList.h"
#include "avlTreeTemplate.h"

using namespace std;

//CHECK THE HEADER FILE TO ALTER WHAT INFORMATION GET PRINTED TO THE SCREEN
    //If print = true, the word ladder for every node will be printed to the screen

ostream& operator << (ostream & ss, const AvlTree<vector<string>> & gs)
{
    ss << gs.toString("") << endl;
    return ss;
}

int main() {
    
    
    DoublyLinkedList ladder;
    AvlTree<vector<string>> wordTree;
    
    ladder.setFile("dictionary.txt");
    wordTree.setFile("dictionary.txt");
    
    
    ladder.solveLadder("kiss", "woof");
    wordTree.aStarSolution("kiss", "woof");
    ladder.solveLadder("cock", "numb");
    wordTree.aStarSolution("cock", "numb");
    ladder.solveLadder("jura", "such");
    wordTree.aStarSolution("jura", "such");
    ladder.solveLadder("stet", "whey");
    wordTree.aStarSolution("stet", "whey");
    ladder.solveLadder("chaos", "order");
    wordTree.aStarSolution("chaos", "order");
    
    
    
    return 0;
}

//const int randomLadders = 2;            //Specify the number of random ladders you want to generate
//const int printDictionaryLength = 10;   //Specify how many entries of the dictionary you want to print

//DoublyLinkedList ladder;    //LinkedList

//ladder.setFile("dictionary.txt");                       //Set dictionary file name
//ladder.setOutput("LadderList.txt");                     //Set output file name

//ladder.printDictionaryVector(printDictionaryLength);    //Print first 'n' entries of dictionary
//ladder.solveLadder("this", "those");                    //Test words of different lengths
//ladder.solveLadder("vicki", "allan");                   //Test words not found in dictionary
//ladder.solveLadder("oops", "pops");                     //Test simple ladder
//ladder.solveLadder("happily", "angrily");               //Test a ladder with no solution
//ladder.solveLadder("slow", "fast");                     //Test ladder
//ladder.solveLadder("stone", "money");                   //Test ladder
//for (int i = 0; i < randomLadders; i++) {               //Test Random Ladder Generator
//  ladder.solveLadder("flute");
//}


/*
 AvlTree<vector<string>> stringTree;
 
 stringTree.setFile("dictionary.txt");
 stringTree.aStarSolution("oops", "pops");
 //stringTree.toString("oops to pops");
 stringTree.aStarSolution("slow", "fast");
 stringTree.aStarSolution("cock", "numb");
 */


//Personal tests - for fun!

//ladder.solveLadder("seafaring");
//ladder.solveLadder("dusk", "dawn");
//ladder.solveLadder("chaos", "peace");
//ladder.solveLadder("sad", "mad");
//ladder.solveLadder("order", "chaos");
//ladder.solveLadder("peace", "fight");



/*
 AvlTree<int> intTree;
 
 int intArray[] = {1, 3, 5, 7, 9, 9, 9, 11, 2, 9, 4, 8};
 int intArray2[] = {30, 50, 30, 30, 15, 18};
 string formattedTree = "Tree of Integers\n";
 
 
 for (int i = 0; i < (sizeof(intArray)/sizeof(intArray[0])); i++) {
 intTree.insert(intArray[i]);
 }
 cout << intTree.toString(formattedTree) << endl;
 cout << intTree.toString2(formattedTree) << endl;
 
 intTree.remove(7);
 intTree.remove(9);
 cout << intTree.toString(formattedTree) << endl;
 cout << intTree.toString2(formattedTree) << endl;
 
 for (int i = 0; i < (sizeof(intArray2)/sizeof(intArray2[0])); i++) {
 intTree.insert(intArray2[i]);
 }
 cout << intTree.toString(formattedTree) << endl;
 cout << intTree.toString2(formattedTree) << endl;
 
 intTree.removeMin();
 cout << intTree.toString(formattedTree) << endl;
 cout << intTree.toString2(formattedTree) << endl;
 intTree.removeMin();
 cout << intTree.toString(formattedTree) << endl;
 cout << intTree.toString2(formattedTree) << endl;
 intTree.removeMin();
 cout << intTree.toString(formattedTree) << endl;
 cout << intTree.toString2(formattedTree) << endl;
 
 intTree.insert(17);
 cout << intTree.toString(formattedTree) << endl;
 cout << intTree.toString2(formattedTree) << endl;
 */