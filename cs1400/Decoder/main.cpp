//
//  main.cpp
//  Decoder - Steven Proctor
//
//  Created by Steven Proctor on 2/2/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    
    char letter, translation;
    
    ifstream fin;
    
    ofstream fout;
    
    fout.open("decodedMessage.txt");
    
    fin.open("secretMessage.txt");
    
    while (fin.get(letter)) {
        if (letter > 64 && letter < 78) {
            translation = letter + 13;
        }
        
        else if (letter > 77 && letter < 91) {
            translation = letter - 13;
        }
        
        else if (letter > 96 && letter < 110) {
            translation = letter + 13;
        }
        
        else if (letter > 109 && letter < 123) {
            translation = letter - 13;
        }
        
        else translation = letter;
        
        fout << translation;
    }
    
    fin.close();
    
    fout.close();

    return 0;
}