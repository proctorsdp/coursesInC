//
//  sharks.h
//  Fish and Sharks
//
//  Created by Steven Proctor on 2/22/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef SHARKS_H
#define SHARKS_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "protofish.h"
#include "dir.h"
#include "fish.h"

using namespace std;

class Shark : public Fish {
public:
    //Constructor
    Shark(int starvationCountdown,
          int starvationPeriod,
          int gestationCountdown,
          int gestationPeriod,
          int startingAge) :
            Fish(gestationCountdown, gestationPeriod, startingAge),
            starvationCountdown(starvationCountdown),
            starvationPeriod(starvationPeriod){};
    
    //Resets starvation countdown
    void eat();
    
    //Return "u, d, l, or r"
    char toChar();
    
    //Overrides protofish and fish timeUpdate
    void timeUpdate();
    
    //Points shark towards nearest fish
    void point(char sonarMap[5][5]);
    
    
protected:
    int starvationCountdown;
    int starvationPeriod;
};

#endif /* sharks_h */
