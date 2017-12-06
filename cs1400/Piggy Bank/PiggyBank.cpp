//
//  PiggyBank.cpp
//  Piggy Bank - Steven Proctor
//
//  Created by Steven Proctor on 3/22/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include "PiggyBank.h"
#include <iostream>

using namespace std;

PiggyBank::PiggyBank() {
    broken = 0;
    savings = 0;
}

PiggyBank::PiggyBank(double d) {
    broken = 0;
    savings += d;
}

PiggyBank::~PiggyBank() {
    if (broken == 1) {
        cout << "Your Piggy Bank was broken!\n";
    }
}

void PiggyBank::depositMoney(double d) {
    if (broken == 0) {
        if (d > 0){
            savings += d;
            cout << "*Ching!*\n" << endl;
        }
        else {
            cout << endl <<  "You can't withdraw money unless you smash your Piggy Bank!\n" << endl;
        }
    }
    else {
        cout << endl << "Your Piggy Bank is broken! You can't deposit any money!\n" << endl;
    }
}

double PiggyBank::countSavings() {
    return savings;
}

void PiggyBank::smash() {
    broken = 1;
    cout << savings;
    savings = 0;
}