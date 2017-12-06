//
//  sharks.cpp
//  Fish and Sharks
//
//  Created by Steven Proctor on 2/22/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "sharks.h"
#include "dir.h"
#include "protofish.h"
#include "fish.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;


//Resets starvation countdown
void Shark::eat() {
    starvationCountdown = starvationPeriod;
}



//Return "u, d, l, or r"
char Shark::toChar() {
    if(dead)return 'X';
    if(dir==up)return 'u';
    if(dir==rt)return 'r';
    if(dir==dn)return 'd';
    if(dir==lt)return 'l';
    exit(1);
}



//Overrides protofish and fish timeUpdate
void Shark::timeUpdate() {
    if(age<100 && starvationCountdown > 1){
            age++;
            gestationCountdown--;
            starvationCountdown--;
    }
    else {dead=true;}
}



//Points shark towards nearest fish
void Shark::point(char sonarMap[5][5]) {
    priority = 5;
    closestColumn = '\0';
    closestRow = '\0';
     for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (sonarMap[i][j] != '.') {
                closestFish(i, j);
            }
        }
    }
    
    if (closestRow < 2) {
        if (closestColumn > 0 && closestColumn < 4) {
            dir = up;
            return;
        }
    }
    if (closestRow > 2) {
        if (closestColumn > 0 && closestColumn < 4) {
            dir = dn;
            return;
        }
    }
    if (closestColumn < 2) {
        if (closestRow > 0 && closestRow < 4) {
            dir = lt;
            return;
        }
    }
    if (closestColumn > 2) {
        if (closestRow > 0 && closestRow < 4) {
            dir = rt;
            return;
        }
    }
    if (closestRow < 2) {
        if (closestColumn == 0 || closestColumn == 4 ) {
            dir = up;
            return;
        }
    }
    if (closestRow > 2) {
        if (closestColumn == 0 || closestColumn == 4 ) {
            dir = dn;
            return;
        }
    }
}