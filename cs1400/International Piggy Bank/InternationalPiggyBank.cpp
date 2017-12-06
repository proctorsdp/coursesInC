//
//  InternationalPiggyBank.cpp
//  International Piggy Bank - Steven Proctor
//
//  Created by Steven Proctor on 4/1/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include "InternationalPiggyBank.h"
#include <iostream>
#include <string>

using namespace std;

InternationalPiggyBank::InternationalPiggyBank() {
    broken = 0;
    savings = 0;
}

InternationalPiggyBank::InternationalPiggyBank(double d) {
    broken = 0;
    savings += d;
    type = USD;
}

InternationalPiggyBank::~InternationalPiggyBank() {
    if (broken == 1) {
        cout << "Your Piggy Bank was broken!\n";
    }
}

void InternationalPiggyBank::depositMoney(double d) {
    if (broken == 0) {
        if (d > 0){
            savings += d;
            type = USD;
        }
        else {
            cout << endl <<  "You can't withdraw money unless you smash your Piggy Bank!\n" << endl;
        }
    }
    else {
        cout << endl << "Your Piggy Bank is broken! You can't deposit any money!\n" << endl;
    }
}

double InternationalPiggyBank::countSavings() {
    return savings;
}

void InternationalPiggyBank::smash() {
    broken = 1;
    savings = 0;
}

string InternationalPiggyBank::getCurrencyType() {
    switch (type) {
        case 1: currency = "USD";
            break;
        case 2: currency = "EUR";
            break;
        case 3: currency = "CAD";
            break;
        case 4: currency = "MXN";
            break;
        case 5: currency = "JPY";
            break;
        default: cout << "Error!\n";
    }
    return currency;
}

double InternationalPiggyBank::convertToUSD() {
    convertBack();
    savings *= USDCONVRATE;
    type = USD;
    return savings;
}

double InternationalPiggyBank::convertToEUR() {
    convertBack();
    savings *= EURCONVRATE;
    type = EUR;
    return savings;
}

double InternationalPiggyBank::convertToCAD() {
    convertBack();
    savings *= CADCONVRATE;
    type = CAD;
    return savings;
}

double InternationalPiggyBank::convertToMXN() {
    convertBack();
    savings *= MXNCONVRATE;
    type = MXN;
    return savings;
}

double InternationalPiggyBank::convertToJPY() {
    convertBack();
    savings *= JPYCONVRATE;
    type = JPY;
    return savings;
}

void InternationalPiggyBank::convertBack() {
    switch (type) {
        case USD: savings /= USDCONVRATE;
            break;
        case EUR: savings /= EURCONVRATE;
            break;
        case CAD: savings /= CADCONVRATE;
            break;
        case MXN: savings /= MXNCONVRATE;
            break;
        case JPY: savings /= JPYCONVRATE;
            break;
        default: cout << "ERROR!\n";
    }
}