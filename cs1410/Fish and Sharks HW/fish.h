//
//  fish.h
//  Fish and Sharks
//
//  Created by Steven Proctor on 2/22/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef FISH_H
#define FISH_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "protofish.h"
#include "dir.h"

using namespace std;

class Fish : public ProtoFish {
public:
    //Constructor
    Fish(int gestationCountdown,
         int gestationPeriod,
         int startingAge) :
            ProtoFish(startingAge),
            gestationCountdown(gestationCountdown),
            gestationPeriod(gestationPeriod){};
    
    //Fish has a baby
    bool haveBaby();
    
    //Override timeUpdate function from protofish
    void timeUpdate();
    
    //Sets the direction the fish is heading in
    void point(char sonarMap[5][5]);
    
    //Finds the closest fish
    void closestFish(int row, int column);
    
protected:
    int gestationCountdown;
    int gestationPeriod;
    int startingAge;
    int closestRow;
    int closestColumn;
    int priority;
};


#endif /* fish_h */
