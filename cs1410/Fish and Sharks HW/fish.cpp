//
//  fish.cpp
//  Fish and Sharks
//
//  Created by Steven Proctor on 2/22/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "dir.h"
#include "protofish.h"
#include "fish.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

// Resets gestation countdown
bool Fish::haveBaby() {
    if (gestationCountdown == 0) {
        gestationCountdown = gestationPeriod;
        return true;
    }
    else {return false;}
}


// Ages fish and counts down to haveBaby
void Fish::timeUpdate() {
    if(age<100){
        age++;
        gestationCountdown--;
    }
    else {dead=true;}
}


// Points the fish to an empty space that is near a fish
void Fish::point(char sonarMap[5][5]) {
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
    
    if (priority == 1) {
        if (closestRow == 2) {
            if (sonarMap[2][3] == '.') {
                dir = rt;
                return;
            }
            else if (sonarMap[2][1] == '.') {
                dir = lt;
                return;
            }
        }
        else if (closestColumn == 2) {
            if (sonarMap[3][2] == '.') {
                dir = dn;
                return;
            }
            else if (sonarMap[1][2] == '.') {
                dir = up;
                return;
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


void Fish::closestFish(int row, int column) {
    if (row == 2) {
        if (column == 1 || column == 3) {
            closestRow = row;
            closestColumn = column;
            priority = 1;
        }
    }
    if (column == 2) {
        if (row == 1 || row == 3) {
            closestRow = row;
            closestColumn = column;
            priority = 1;
        }
    }
    if (row > 0 && row < 4) {
        if (column > 0 && column < 4) {
            if (priority > 1) {
                closestRow = row;
                closestColumn = column;
                priority = 2;
            }
        }
        else if (column == 0 || column == 4) {
            if (priority > 2) {
                closestRow = row;
                closestColumn = column;
                priority = 3;
            }
        }
    }
    if (column > 0 && column < 4) {
        if (row > 0 && row < 4) {
            if (priority > 1) {
                closestRow = row;
                closestColumn = column;
                priority = 2;
            }
        }
        else if (row == 0 || row == 4) {
            if (priority > 2) {
                closestRow = row;
                closestColumn = column;
                priority = 3;
            }
        }
    }
    if (row == 0 || row == 4) {
        if (column == 0 || column == 4) {
            if (priority > 3) {
                closestColumn = column;
                closestRow = row;
                priority = 4;
            }
        }
    }
}