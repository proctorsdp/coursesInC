//
//  main.cpp
//  Gum Machine - Steven Proctor
//
//  Created by Steven Proctor on 2/8/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    
    double money, cost;
    int stride, five, trident, juicy;
    char entry;
    
    money = 16.50;
    cost = .75;
    stride = 6;
    five = 3;
    trident = 8;
    juicy = 10;
    
    cout << "Welcome to the gum machine! Please read the menu below and enter your selection:\n" << endl;
    cout << "s - Report the machine's status\n";
    cout << "d - Drop in a quarter\n";
    cout << "1 - Pull the first tab\n";
    cout << "2 - Pull the second tab\n";
    cout << "3 - Pull the third tab\n";
    cout << "4 - Pull the fourth tab\n";
    cout << "r - Restock the machine\n";
    cout << "q - Quit\n";
    
    while (entry != 'q' && entry != 'Q') {
        cout << endl;
        cin >> entry;
        cout << endl;
        
        //Using If/Else as Primary:
        
        if (entry == 's' || entry == 'S'){
            cout << "1: " << stride << " packs of Stride\n";
            cout << "2: " << five << " packs of Five Gum\n";
            cout << "3: " << trident << " packs of Trident\n";
            cout << "4: " << juicy << " packs of Juicy Fruit\n";
            cout << setprecision(2) << fixed;
            cout << "There is $" << money << " in the vending machine\n";
        }
         
        else if (entry == 'd' || entry == 'D') {
            money += .25;
            cost -= .25;
            cout << "*Ching!*\n";
        }
         
        else if ((cost <= 0) && ((entry >= '1') && (entry <= '4'))) {
            switch (entry) {
                case '1':
                    if (stride > 0) {
                        cout << "A pack of Stride Gum slides out of the machine.\n";
                        stride -= 1;
                    }
                    else {
                        cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    }
                    break;
                case '2':
                    if (five > 0) {
                        cout << "A pack of Five Gum slides out of the machine.\n";
                        five -= 1;
                    }
                    else {
                        cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    }
                    break;
                case '3':
                    if (trident > 0) {
                        cout << "A pack of Trident Gum slides out of the machine.\n";
                        trident -= 1;
                    }
                    else {
                        cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    }
                    break;
                case '4':
                    if (juicy > 0) {
                        cout << "A pack of Juicy Fruit Gum slides out of the machine.\n";
                        juicy -= 1;
                    }
                    else {
                        cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    }
                    break;
                default: cout << "Program Error\n";
            }
            cost = .75;
         }
         
         else if ((cost > 0) && ((entry >= '1') && (entry <= '4'))) {
             cout << "(nothing happens)\n";
         }
         
         else if (entry == 'r' || entry == 'R') {
             money = 0;
             cost = .75;
             stride = 10;
             five = 10;
             trident = 10;
             juicy = 10;
             cout << "A slow old man meanders over, opens the back of the machine, and restocks the gum.\n";
         }
         
         else if (entry == 'q') {
             cout << "Please come back soon!\n";
         }
         
         else {
             cout << "I do not understand.\n";
         }
    
        //Using Switch as Primary:
        
        /*switch (entry) {
            case 's':
                cout << "1: " << stride << " packs of Stride\n";
                cout << "2: " << five << " packs of Five Gum\n";
                cout << "3: " << trident << " packs of Trident\n";
                cout << "4: " << juicy << " packs of Juicy Fruit\n";
                cout << setprecision(2) << fixed;
                cout << "There is $" << money << " in the vending machine\n";
                break;
            case 'd':
                money += .25;
                cost -= .25;
                cout << "*Ching!*\n";
                break;
            case '1':
                if ((stride > 0) && (cost <= 0)) {
                    cout << "A pack of Stride Gum slides out of the machine.\n";
                    stride -= 1;
                    cost = .75;
                }
                else if ((stride < 1 ) && (cost <= 0)) {
                    cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    cost = .75;
                }
                else {
                    cout << "(nothing happens)\n";
                }
                break;
            case '2':
                if ((five > 0) && (cost <= 0)) {
                    cout << "A pack of Five Gum slides out of the machine.\n";
                    five -= 1;
                    cost = .75;
                }
                else if ((five < 1 ) && (cost <= 0)){
                    cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    cost = .75;
                }
                else {
                    cout << "(nothing happens)\n";
                }
                break;
            case '3':
                if ((trident > 0) && (cost <= 0)) {
                    cout << "A pack of Trident Gum slides out of the machine.\n";
                    trident -= 1;
                    cost = .75;
                }
                else if ((trident < 1 ) && (cost <= 0)){
                    cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    cost = .75;
                }
                else {
                    cout << "(nothing happens)\n";
                }
                break;
            case '4':
                if ((juicy > 0) && (cost <= 0)) {
                    cout << "A pack of Juicy Fruit Gum slides out of the machine.\n";
                    juicy -= 1;
                    cost = .75;
                }
                else if ((juicy < 1 ) && (cost <= 0)){
                    cout << "The machine responds with clanging noises, but no gum is dispensed.\n";
                    cost = .75;
                }
                else {
                    cout << "(nothing happens)\n";
                }
                break;
            case 'r':
                money = 0;
                cost = .75;
                stride = 10;
                five = 10;
                trident = 10;
                juicy = 10;
                cout << "A slow old man meanders over, opens the back of the machine, and restocks the gum.\n";
                break;
            case 'q':
                cout << "Please come back soon!\n";
                break;
            default: cout << "I do not understand.\n";
         }*/
    
    }
    
    return 0;
}



