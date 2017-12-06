//
//  InternationalPiggyBank.h
//  International Piggy Bank - Steven Proctor
//
//  Created by Steven Proctor on 4/1/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#ifndef __International_Piggy_Bank___Steven_Proctor__InternationalPiggyBank__
#define __International_Piggy_Bank___Steven_Proctor__InternationalPiggyBank__

#include <stdio.h>
#include <string>

using namespace std;

enum CurrencyType {
    USD = 1,
    EUR,
    CAD,
    MXN,
    JPY
};

class InternationalPiggyBank {
private:
    bool broken;
    double savings, USDSavings;
    int type;
    string currency;
    const double USDCONVRATE=1.0;
    const double EURCONVRATE=0.92; // 0.92 EUR = 1 US
    const double CADCONVRATE=1.25; // 1.25 CAD = 1 USD
    const double MXNCONVRATE=15.12; // 15.12 MXN = 1 USD
    const double JPYCONVRATE=119.19; // 119.19 JPY = 1 USD
public:
    InternationalPiggyBank();
    InternationalPiggyBank(double);
    ~InternationalPiggyBank();
    
    void depositMoney(double);
    double countSavings();
    void smash();
    string getCurrencyType();
    double convertToUSD();
    double convertToEUR();
    double convertToCAD();
    double convertToMXN();
    double convertToJPY();
    void convertBack();
};


#endif /* defined(__International_Piggy_Bank___Steven_Proctor__InternationalPiggyBank__) */
