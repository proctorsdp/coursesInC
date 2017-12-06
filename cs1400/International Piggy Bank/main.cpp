//
//  main.cpp
//  International Piggy Bank - Steven Proctor
//
//  Created by Steven Proctor on 4/1/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "InternationalPiggyBank.h"

using namespace std;

int main() {
    //char entry;
    //double deposit;
    
    cout << "Welcome to your Piggy Bank!\n" << endl;
    
    InternationalPiggyBank piggyBank(12.34);
    
    piggyBank.depositMoney(0.26);
    cout<<"The piggy bank has $"<<fixed<<setprecision(2)<<piggyBank.countSavings();
    cout<<" "<<piggyBank.getCurrencyType()<<endl;
    
    piggyBank.convertToCAD();
    cout<<"The piggy bank has $"<<piggyBank.countSavings();
    cout<<" "<<piggyBank.getCurrencyType()<<endl;
    
    piggyBank.convertToEUR();
    cout<<"The piggy bank has $"<<piggyBank.countSavings();
    cout<<" "<<piggyBank.getCurrencyType()<<endl;
    
    piggyBank.convertToMXN();
    cout<<"The piggy bank has $"<<piggyBank.countSavings();
    cout<<" "<<piggyBank.getCurrencyType()<<endl;
    
    piggyBank.convertToJPY();
    cout<<"The piggy bank has $"<<piggyBank.countSavings();
    cout<<" "<<piggyBank.getCurrencyType()<<endl;
    
    piggyBank.convertToUSD();
    cout<<"The piggy bank has $"<<piggyBank.countSavings();
    cout<<" "<<piggyBank.getCurrencyType()<<endl;
    
    piggyBank.smash();
    
    return 0;
}
