//
//  main.cpp
//  Word Ladder - Steven Proctor
//
//  Created by Steven Proctor on 9/10/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include "DoublyLinkedList.h"
#include "dictonary.hpp"

using namespace std;

int main() {
    const int randomLadders = 5;
    const int printDictionaryLength = 10;
    DoublyLinkedList ladder;
    
    ladder.setFile("dictionary.txt");
    ladder.printDictionaryVector(printDictionaryLength);
    ladder.solveLadder("this", "those");
    ladder.solveLadder("vicki", "allan");
    ladder.solveLadder("oops", "pops");
    ladder.solveLadder("happily", "angrily");
    ladder.solveLadder("slow", "fast");
    ladder.solveLadder("stone", "money");
    for (int i = 0; i < randomLadders; i++) {
        ladder.solveLadder("flute");
    }
    ladder.solveLadder("seafaring");
    
    
     ladder.solveLadder("dusk", "dawn");
     ladder.solveLadder("chaos", "peace");
     ladder.solveLadder("sad", "mad");
     ladder.solveLadder("order", "chaos");
     ladder.solveLadder("peace", "fight");
    
    
    return 0;
}



//const int RANDOMCT = 1;
//Game g("dictionary.txt");
//g.listWords();  //Lists the first ten words in the dictionary as a test.
//g.play("this", "those");
//g.play("vicki", "allan");
//g.play("oops", "pops");
//g.play("happily", "angrily");
//g.play("slow", "fast");
//g.play("stone", "money");
//for (int i = 0; i < RANDOMCT; i++) g.play("flute");
//if two arguments are not provided, randomly pick both strings.  Use the length of provided argument as length of strings