//
//  main.cpp
//  Shortest Path of the King - Steven Proctor
//
//  Created by Steven Proctor on 2/17/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    char xstart, xfinish;
    int ystart, yfinish, moves = 0, xdirection, ydirection, finish = 0;
   
    cout << "The Shortest Path of the King\n" << endl;
    
    cout << "Where is the King currently ('a-h' & '1-8'): \n";
    cin >> xstart >> ystart;
    
    cout << endl << "Where does the King want to go ('a-h' & '1-8'): \n";
    cin >> xfinish >> yfinish;
    
    while ((xstart > 'h') || (xstart < 'a') || (xfinish > 'h') || (xfinish < 'a') || (ystart > 8) || (ystart < 1) || (yfinish > 8) || (yfinish < 1)) {
        cout << endl << "Not a valid entry. Enter the information again.\n" << endl;
        
        cout << "Where is the King currently ('a-h' & '1-8'): \n";
        cin >> xstart >> ystart;
        
        cout << endl << "Where does the King want to go ('a-h' & '1-8'): \n";
        cin >> xfinish >> yfinish;
    }
    
    cout << endl << endl << "Directions the King moved:\n";
    
    xdirection = xfinish - xstart;
    ydirection = yfinish - ystart;
    
    while (finish == 0) {
        
        if (xdirection > 0) {
            if (ydirection > 0) {
                cout << "RU\n";
                ydirection -= 1;
            }
            else if (ydirection < 0) {
                cout << "RD\n";
                ydirection += 1;
            }
            else if (ydirection == 0) {
                cout << "R\n";
            }
            xdirection -= 1;
            moves++;
        }
        else if (xdirection < 0) {
            if (ydirection > 0) {
                cout << "LU\n";
                ydirection -= 1;
            }
            else if (ydirection < 0) {
                cout << "LD\n";
                ydirection += 1;
            }
            else if (ydirection == 0) {
                cout << "L\n";
            }
            xdirection += 1;
            moves++;
        }
        else if (xdirection == 0) {
            if (ydirection > 0) {
                cout << "U\n";
                ydirection -= 1;
                moves++;
            }
            else if (ydirection < 0) {
                cout << "D\n";
                ydirection += 1;
                moves++;
            }
            else if (ydirection == 0) {
                finish = 1;
            }
        }
    }
    
    cout << "The King made " << moves << " moves.\n" << endl;
    
    cout << endl << "The King has reached his destination!\n";
    
    return 0;
}