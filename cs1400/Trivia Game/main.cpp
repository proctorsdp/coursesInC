//
//  main.cpp
//  Trivia Game - Steven Proctor
//
//  Created by Steven Proctor on 3/16/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string type, question, entry, answer, name1, name2, name3;
    int score = 0, numquestions, highscore1, highscore2, highscore3;
    double finalscore;
    ifstream finQ, finA, finH;
    ofstream foutH;
    
    finQ.open("triviaQuestions.txt");
    finA.open("triviaAnswers.txt");
    finQ >> numquestions;
    getline(finQ, type);
    
    cout << "Welcome to the" << type << " trivia game!\n" << endl;
    cout << "Note: All words MUST begin with a capital letter. If the answer is the name of a person enter their first AND last name, if they have one.\n" << endl << endl;
    
    for (int i = 1; i <= numquestions; i++) {
        cout << "Question " << i << ":" << endl << endl;
        getline(finQ, question);
        cout << question << endl << endl;
        getline(cin, entry);
        
        getline(finA, answer);
        if (entry == answer) {
            score += 1;
            cout << endl << "Correct! You currently have " << score << " point(s)!\n" << endl << endl;
        }
        
        else {
            cout << endl << "Wrong! You currently have " << score << " point(s)!\n" << endl << endl;
        }
    }
    
    finQ.close();
    finA.close();
    
    finalscore = (double(score) / 10) * 100;
    cout << "Final Score: " << finalscore << "% (" << score << "/10 correct questions)\n" << endl << endl;
   
    finH.open("highScores.txt");
    finH >> highscore1;
    getline(finH, name1);
    finH >> highscore2;
    getline(finH, name2);
    finH >> highscore3;
    getline(finH, name3);
    finH.close();
    
    if (score >= highscore1) {
        highscore3 = highscore2;
        name3 = name2;
        highscore2 = highscore1;
        name2 = name1;
        cout << "Congratulations! You earned the high score!\n" << endl;
        cout << "Please enter your name: ";
        getline(cin, entry);
        name1 = " " + entry;
        highscore1 = score;
    }
    
    else if (score >= highscore2) {
        highscore3 = highscore2;
        name3 = name2;
        cout << "Congratulations! You earned the 2nd highest score!\n" << endl;
        cout << "Please enter your name: ";
        getline(cin, entry);
        name2 = " " + entry;
        highscore2 = score;
    }
    
    else if (score >= highscore3) {
        cout << "Congratulations! You earned the 3rd highest score!\n" << endl;
        cout << "Please enter your name: ";
        getline(cin, entry);
        name3 = " " + entry;
        highscore3 = score;
    }
    
    else {
        cout << "You did not earn a high score." << endl;
    }
    
    foutH.open("highScores.txt");
    foutH << highscore1 << name1 << endl;
    foutH << highscore2 << name2 << endl;
    foutH << highscore3 << name3 << endl;
    foutH.close();
    
    cout << endl << endl << "Current High Scores:\n" << endl;
    
    cout << highscore1 << name1 << endl;
    cout << highscore2 << name2 << endl;
    cout << highscore3 << name3 << endl;

    return 0;
}