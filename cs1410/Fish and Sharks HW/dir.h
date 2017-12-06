//
//  dir.h
//  Fish and Sharks
//
//  Created by Steven Proctor on 2/22/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef DIR_H
#define DIR_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

//there are four directions
enum Dir{up,rt,dn,lt};

//return a random direction
Dir randDir();

//given a direction, return the next direction in a clockwise fashion
Dir nextDir(Dir currentDir);

#endif