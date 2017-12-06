//
//  main.cpp
//  Raptor Math (Steven Proctor)
//
//  Created by Steven Proctor on 1/17/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    double distance, time;
    
    const int raptor_speed = 25, human_speed = 6;
    
    
    cout << "Welcome to Jurrasic Park! Please enjoy our wide collection of dinosuars!\nBut watch out, some raptors have been reported missing!\n";
    
    cout << endl << endl << "Oh no! An escaped raptor has spotted you! How long do you have to live?\n" << endl;
    
    cout << "Enter how far away you are from the raptor in meters: ";
    
    cin >> distance;
    
    time = distance / (raptor_speed - human_speed);
    
    cout << endl << "If you are " << distance << " meters away from the raptor you have " << time << " seconds to live.\n" << endl;
    
    cout << endl << "Thank you for coming to Jurrasic Park! Please come again!\n";
    
    
    return 0;
}
