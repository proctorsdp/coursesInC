//
//  main.cpp
//  Fish and Sharks
//
//  Created by Steven Proctor on 2/22/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "dir.h"
#include "protofish.h"
//TODO: uncomment to test fish and sharks
#include "fish.h"
#include "sharks.h"


using namespace std;

void printMap(ProtoFish f, char smap[5][5]){
    smap[2][2]=f.toChar();
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){
            cout<<smap[i][j];
        }
        cout<<endl;
    }
}

//TODO: uncomment for the shark tests
 void printMap(Shark s, char smap[5][5]){
	smap[2][2]=s.toChar();
	for(int i=0;i<5;++i){
 for(int j=0;j<5;++j){
 cout<<smap[i][j];
 }
 cout<<endl;
	}
 }


int main(){
    cout<<"\nProtoFish Tests\n";
    ProtoFish nemo(96);
    char line[1024];
    char sonarMap1[5][5]={
        '.','.','.','.','.',
        '.','.','.','.','.',
        '.','.','.','.','.',
        '.','.','.','.','.',
        '.','.','.','.','.',
    };
    
    for(int i=0;i<5;++i){
        nemo.point();
        nemo.timeUpdate();
        printMap(nemo,sonarMap1);
        if(i==4) cout<<"expected output: X\n";
        cout<<"====="<<endl;
    }
    
    //TODO: uncomment to include fish tests

     cout<<"\nFish Tests\n";
     Fish guppy(2,5,90);
     
     char sonarMap2[5][5]={
     '.','.','.','.','.',
     '.','.','.','.','.',
     '^','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     };
     guppy.point(sonarMap2);
     guppy.timeUpdate();
     printMap(guppy,sonarMap2);
     if(guppy.haveBaby())cout<<"baby time.\n";
     cout<<"expected output: <\n";
     cout<<"====="<<endl;
     
     char sonarMap3[5][5]={
     '.','<','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     };
     guppy.point(sonarMap3);
     guppy.timeUpdate();
     printMap(guppy,sonarMap3);
     if(guppy.haveBaby())cout<<"baby time.\n";
     cout<<"expected output: ^ and baby time\n";
     cout<<"====="<<endl;
     
     char sonarMap4[5][5]={
     '.','<','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','v',
     '.','.','.','.','.',
     };
     guppy.point(sonarMap4);
     guppy.timeUpdate();
     printMap(guppy,sonarMap4);
     if(guppy.haveBaby())cout<<"baby time.\n";
     cout<<"expected output: ^ or >\n";
     cout<<"====="<<endl;
    
    
    
    
    //TODO: uncomment to include shark tests
     cout<<"\nShark Tests\n";
     Shark mako(3,6,2,5,90);
     
     char sonarMap5[5][5]={
     '.','.','.','.','.',
     '.','.','.','.','.',
     '^','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     };
     mako.point(sonarMap5);
     mako.timeUpdate();
     printMap(mako,sonarMap5);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: l\n";
     cout<<"====="<<endl;
     
     char sonarMap6[5][5]={
     '.','.','>','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     };
     mako.point(sonarMap6);
     mako.timeUpdate();
     printMap(mako,sonarMap6);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: u and baby time\n";
     cout<<"====="<<endl;
     
     char sonarMap7[5][5]={
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','^',
     '.','.','.','.','.',
     '.','.','.','.','.',
     };
     mako.eat();
     mako.point(sonarMap7);
     mako.timeUpdate();
     printMap(mako,sonarMap7);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: r\n";
     cout<<"====="<<endl;
     
     char sonarMap8[5][5]={
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','.','.','.',
     '.','.','^','.','.',
     };
     mako.point(sonarMap8);
     mako.timeUpdate();
     printMap(mako,sonarMap8);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: d\n";
     cout<<"====="<<endl;
     
     char sonarMap9[5][5]={
     '>','.','.','.','.',
     '.','.','>','.','.',
     '.','.','.','.','.',
     '.','>','.','.','.',
     '.','.','^','>','.',
     };
     mako.point(sonarMap9);
     mako.timeUpdate();
     printMap(mako,sonarMap9);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: u\n";
     cout<<"====="<<endl;
     
     mako.point(sonarMap9);
     mako.timeUpdate();
     printMap(mako,sonarMap9);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: u\n";
     cout<<"====="<<endl;
     
     mako.point(sonarMap9);
     mako.timeUpdate();
     printMap(mako,sonarMap9);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: u and baby time\n";
     cout<<"====="<<endl;
     
     mako.point(sonarMap9);
     mako.timeUpdate();
     printMap(mako,sonarMap9);
     if(mako.haveBaby())cout<<"baby time.\n";
     if(mako.isDead())cout<<"dead.\n";
     cout<<"expected output: X and dead\n";
     cout<<"====="<<endl;
    
    
    return 0;
}
