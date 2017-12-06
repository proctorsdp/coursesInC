//
//  main.cpp
//  Piggy Bank - Steven Proctor
//
//  Created by Steven Proctor on 3/22/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include "PiggyBank.h"
//#include "PiggyBank.cpp"
using namespace std;

int main() {
    char entry;
    double deposit;
  
    PiggyBank piggy;
    
    cout << "Welcome to your Piggy Bank!\n" << endl;
    
    cout << "What would you like to do?" << endl;
    cout << "d - Deposit Money" << endl;
    cout << "c - Check Savings" << endl;
    cout << "s - Smash Piggy Bank" << endl;
    cout << "q - Quit\n" << endl;
    
    cin >> entry;
    
    while (entry != 'q') {
        if (entry == 'd') {
            cout << "How much would you like to deposit? ";
            cin >> deposit;
            piggy.depositMoney(deposit);
        }
        else if (entry == 'c') {
            cout << "You currenty have $" << piggy.countSavings() << " in your Piggy Bank\n" << endl;
        }
        else if (entry == 's') {
            cout << "You smahsed your Piggy Bank! You found $";
            piggy.smash();
            cout << " inside!\n" << endl;
        }
        else {
            cout << "Invalid Entry\n" << endl;
        }
        cin >> entry;
    }
    
    cout << "Thanks for coming!\n";
    
    return 0;
}

/* 
 for (int i = 0; i < 5; i++) {
    cout << "How much would you like to deposit? ";
    cin >> deposit;
    piggy.depositMoney(deposit);
    cout << endl << "You have $" << piggy.countSavings() << " in your Piggy Bank.\n" << endl << endl;
    }
    
    cout << "Time to smash the Piggy Bank!\n" << endl;
    piggy.smash();
    cout << "You smahsed your Piggy Bank and found $" << piggy.countSavings() << " inside.\n" << endl;
*/