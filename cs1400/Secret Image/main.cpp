//
//  main.cpp
//  Secret Image Test
//
//  Created by Steven Proctor on 2/27/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void correctBronze(int &, int &, int &);
void correctSilver(int &, int &, int &);
void correctGold(int &, int &, int &);

int main() {
    
    int color, r, g, b;
    char letter, decoder;
    string encodedfile, decodedfile;
    ifstream fin;
    ofstream fout;
    
    cout << "Enter the name of your encoded image file: ";
    getline(cin, encodedfile);
    cout << endl;
    
    cout << "Enter the name of your decoded image file: ";
    getline(cin, decodedfile);
    cout << endl;
    
    cout << "Which decoder would you like to use?\nb - Bronze\ns - Silver\ng - Gold\n" << endl;
    cin >> decoder;
    
    while (decoder != 'b' && decoder != 's' && decoder != 'g') {
        cout << "Invalid choice, Please enter 'b', 's', or 'g': ";
        cin >> decoder;
    }
    
    fin.open(encodedfile);
    fout.open(decodedfile);
    
    fin >> letter;
    fout << letter;
    fin >> color;
    fout << color << endl;
    
    fin >> color;
    fout << color << "\t";
    fin >> color;
    fout << color << endl;;
    
    fin >> color;
    fout << color << endl;
    
    switch (decoder) {
        case 'b':
            while (!fin.eof()) {
                fin >> r >> g >> b;
                correctBronze(r, g, b);
                fout << r << " " << g << " " << b << " ";
            }
            break;
        case 's':
            while (!fin.eof()) {
                fin >> r >> g >> b;
                correctSilver(r, g, b);
                fout << r << " " << g << " " << b << " ";
            }
            break;
        case 'g':
            while (!fin.eof()) {
                fin >> r >> g >> b;
                correctGold(r, g, b);
                fout << r << " " << g << " " << b << " ";
            }
    }
    
    fin.close();
    fout.close();
    
    cout << endl << "Your file: " << decodedfile << " has been created." << endl;
    
    return 0;
}

void correctBronze(int & r, int & g, int & b) {
    
    r *= 10;
    g = 0;
    b = 0;
    
}

void correctSilver(int & r, int & g, int & b) {
   
    r = 0;
    g *= 20;
    b *= 20;
    
}

void correctGold(int & r, int & g, int & b) {
    
    b = r % 1000;
    g = (r / 1000) % 1000;
    r = r / 1000000;
    
}
