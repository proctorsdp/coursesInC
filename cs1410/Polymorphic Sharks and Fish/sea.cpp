//
//  sea.cpp
//  Ocean
//
//  Created by Steven Proctor on 3/29/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "sea.h"
#include "fish.h"
#include "shark.h"

using namespace std;



//WARNING!!!


//THE HEADER FILE ASSOCIATED WITH THIS CPP FILE MUST INCLUDE THE FOLLOWING INFORMATION IN THE PRIVATE SECTION OF THE CLASS IN ORDER TO COMPILE AND RUN

//Copy and paste this information into the header file

/*
int gestate = 10; //number of days before fish can have a baby
int starve = 8; //number of days before sharks starve
int typeMod = 100; //determines how many creatures will initially populate the ocean. A higher number mean less creatures initially.
int sharkRatio = 5; //determines how many sharks will initially populate the ocean. A higher number means more sharks initially.
int fishRatio = 12; //determines how many fish will initially populate the ocean. A higher number means more fish initially. MUST BE GREATER THAN SHARKRATIO!!!
*/


//WARNING!!! (SEE ABOVE)


//Initialize ocean
Sea::Sea(int row, int columns) :
rows(row),
cols(columns)
{
    
    //allocates rows for the ocean
    pFish = new ProtoFish ** [rows];
    
    //allocates columns for the ocean
    for (int i = 0; i < rows; i++) {
        pFish[i] = new ProtoFish * [cols];
    }
    
    //randomly fills each element of the Ocean with a fish or a shark, or leaves it blank
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            //randomly determines age
            int age = rand() % 100;
            int type = rand() % typeMod;        //IF THIS LINE PREVENTS THE CODE FROM COMPILING, READ THE TOP OF THIS FILE
            
            //randomly determines type of fish
            if (type < sharkRatio) {        //IF THIS LINE PREVENTS THE CODE FROM COMPILING, READ THE TOP OF THIS FILE
                pFish[i][j] = new Shark(starve, starve, gestate, gestate, age);     //IF THIS LINE PREVENTS THE CODE FROM COMPILING, READ THE TOP OF THIS FILE
            }
            else if (type < fishRatio) {        //IF THIS LINE PREVENTS THE CODE FROM COMPILING, READ THE TOP OF THIS FILE
                pFish[i][j] = new Fish(gestate, gestate, age);      //IF THIS LINE PREVENTS THE CODE FROM COMPILING, READ THE TOP OF THIS FILE
            }
            else {
                pFish[i][j] = NULL;
            }
        }
    }
    
    //allocates rows for pMoved
    pMoved = new bool * [rows];
    
    //allocates columns for pMoved
    for (int i = 0; i < rows; i++) {
            pMoved[i] = new bool[cols];
    }
    
    //sets all elements to false
    resetMoved();
}

//delete ocean
Sea::~Sea() {
    
    //deletes fish inside each element
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete pFish[i][j];
        }
    }
    
    //deletes columns
    for (int i = 0; i < rows; i++) {
        delete pFish[i];
    }
    
    //deletes rows
    delete pFish;
}

//Prints ocean
void Sea::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (pFish[i][j] != NULL) {
                cout << pFish[i][j]->toChar() << " ";
            }
            else {
                cout << "." << " ";
            }
        }
        cout << endl;
    }
}

//update each fish
void Sea::timeUpdate() {
    
    //increments through ocean
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (pFish[i][j] != NULL) {
                updateFish(i, j);
            }
        }
    }
    
    //sets all elements to false
    resetMoved();
}

//Workhorse - babies, death, movement, etc.
void Sea::updateFish(int i, int j) {
    
    //Removes dead fish from ocean
    if(pFish[i][j]->isDead()) {
        pFish[i][j] = NULL;
        pMoved[i][j] = true;
    }
    
    //updates fish if they haven't already moved
    if (pMoved[i][j] != true) {
        
        //Make one day pass
        pFish[i][j]->timeUpdate();
        
        //Check to see if baby is ready
        if (pFish[i][j]->haveBaby()) {
            
            int babyI, babyJ;
            bool babyBorn = false;
            
            //find a spot for the baby
            while (!babyBorn) {
                
                //randomnly places baby
                babyI = rand()%(rows);
                babyJ = rand()%(cols);
                
                if (pFish[babyI][babyJ] == NULL) {
                    
                    //randomly assigns age
                    int age = rand() % 80;
                    
                    //if parents were a fish, a fish is born
                    if (pFish[i][j]->whatAmI() == 'F') {
                        pFish[babyI][babyJ] = new Fish(gestate, gestate, age);      //IF THIS LINE PREVENTS THE CODE FROM COMPILING, READ THE TOP OF THIS FILE
                    }
                    
                    //if parents were a shark, a shark is born
                    else if (pFish[i][j]->whatAmI() == 'S') {
                        pFish[babyI][babyJ] = new Shark(starve, starve, gestate, gestate, age);  //IF THIS LINE PREVENTS THE CODE FROM COMPILING, READ THE TOP OF THIS FILE
                    }
                    
                    //breaks while loop
                    babyBorn = true;
                }
            }
        }
        
        //Create a map around a given fish
        setSonarMap(i, j);
            
        //Point fish towards empty spots near fish. Point sharks towards fish.
        pFish[i][j]->point(sonarMap);
        
        //index for current fish
        int moveI, moveJ;
        moveI = i;
        moveJ = j;
        
        //obtains index based on direction the fish is facing
        switch (pFish[i][j]->getDir()) {
            case up: moveI -= 1;
                break;
            case rt: moveJ += 1;
                break;
            case dn: moveI += 1;
                break;
            case lt: moveJ -= 1;
                break;
        }
        
        //ensures the index isn't out of bounds
        if (moveI >= 0 && moveI < rows) {
            if (moveJ >= 0 && moveJ < cols) {
                
                //moves fish into empty spot
                if(pFish[i][j]->whatAmI() == 'F') {
                    if (pFish[moveI][moveJ] == NULL) {
                        pFish[moveI][moveJ] = pFish[i][j];
                        pFish[i][j] = NULL;
                        pMoved[moveI][moveJ] = true;
                    }
                }
                
                //moves shark
                else if (pFish[i][j]->whatAmI() == 'S') {
                    //moves shark to empty spot
                    if (pFish[moveI][moveJ] == NULL) {
                        pFish[moveI][moveJ] = pFish[i][j];
                        pFish[i][j] = NULL;
                        pMoved[moveI][moveJ] = true;
                    }
                    //shark eat fish
                    else if (pFish[moveI][moveJ]->whatAmI() == 'F') {
                        pFish[moveI][moveJ] = pFish[i][j];
                        pFish[i][j] = NULL;
                        pFish[moveI][moveJ]->eat();
                        pMoved[moveI][moveJ] = true;
                    }
                }
            }
        }
    }
}

//creates a personalized sonar map for a fish
void Sea::setSonarMap(int rPos, int cPos) {
    
    //identifies bounds for individual sonar map
    int rStart, rEnd, cStart, cEnd;
    rStart = rPos - 2;
    rEnd = rPos + 2;
    cStart = cPos - 2;
    cEnd = cPos + 2;
    
    //fills sonar map with appropriate characters
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (rStart < 0 || cStart < 0) {
                sonarMap[i][j] = NULL;
            }
            else if (rStart >= rows || cStart >= cols) {
                sonarMap[i][j] = NULL;
            }
            else if (pFish[rStart][cStart] != NULL) {
                sonarMap[i][j] = pFish[rStart][cStart]->toChar();
            }
            else {
                sonarMap[i][j] = '.';
            }
            cStart++;
        }
        cStart = cEnd - 4;
        rStart++;
    }
}

//sets all movement to false
void Sea::resetMoved() {
    
    //increments through each element
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pMoved[i][j] = false;
        }
    }
}