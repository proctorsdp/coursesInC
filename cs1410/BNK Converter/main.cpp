//
//  main.cpp
//  Bank File Converter
//
//  Created by Steven Proctor on 3/4/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

struct BNKHeader {
    char signature[4] = {'B', 'A', 'N', 'K'};
    int numOfAccounts;
    char reserved[24];
};

struct BNKAccount {
    int number;
    char name[20];
    double balance;
    char reserved[96];
};

struct BNKIndex {
    int accountNumber;
    long filePosition;
};

void readFile(ifstream &fin, BNKAccount *&info, int &numAccounts, BNKIndex *&index) {
    string s;
    int indexPos = 32;
    
    //Identify number of accounts
    while (!fin.eof()) {
        getline(fin, s);
        numAccounts++;
    }
    
    numAccounts -= 1;
    
    //Allocate memory for Account Information and Index List
    index = new BNKIndex[numAccounts];
    info = new BNKAccount[numAccounts];
   
    fin.clear();
    fin.seekg(0L, ios::beg);       //get pointer
    
    getline(fin, s);    //Eliminate first line
    
    //Read in each line, and store data in appropriate variable
    for (int i = 0; i < numAccounts; i++) {
        getline(fin, s, ',');
       
        info[i].number = stoi(s);
        index[i].accountNumber = info[i].number;
        index[i].filePosition = indexPos;
        indexPos += 128;
    
        getline(fin, s, ',');
        for (int j = 0; j < sizeof(s); j++) {
            info[i].name[j] = s[j];
        }
        
        getline(fin, s);
        info[i].balance = stof(s);
    }
}

//Sort Index list, ascending order
void sortIndex(BNKIndex *&index, int numAccounts) {
    BNKIndex temp;
    bool swap = true;
    
        while (swap) {
            swap = false;
    
        for (int i = 0; i < numAccounts - 1; i++) {
            if (index[i].accountNumber > index[i+1].accountNumber) {
                temp = index[i+1];
                index[i+1] = index[i];
                index[i] = temp;
                swap = true;
            }
        }
    }
}


int main() {
    
    ifstream fin;
    int numAccounts;
    BNKHeader header;
    BNKAccount *info;
    BNKIndex *index;
    
    //Open CSV file
    fin.open("data.txt");
    
    //Error Check
    if (fin.fail()) {
        cout << "Error opening file\n";
        cout << "Exiting...\n";
        exit(2);
    }
    
    //Read in information
    readFile(fin, info, numAccounts, index);
    header.numOfAccounts = (numAccounts);
    //For some reason the above line of code causes the signature in the header struct to include the number 2. When using cout to debug the program, the signature is printed as: BANK2
    //I checked with the tutors and they had no idea what caused this issue. They said that they had seen this occur in everyone's code
    
    //Ouput information to bnk (binary) file
    fstream outfile;
    outfile.open("AccountInfo.bnk", ios::out | ios::binary);
    outfile.write((char *)&header, sizeof(BNKIndex));
    outfile.write((char *)info, sizeof(BNKAccount)*numAccounts);
    sortIndex(index, numAccounts);
    outfile.write((char *)index, sizeof(BNKIndex)*numAccounts);
    
    //Close files
    fin.close();
    outfile.close();
    
    
    
    
    //Debug using cout
    /*
    cout << header.signature << " " << header.numOfAccounts << endl;
    
    cout << "----------------------------" << endl;
    
    for (int i = 0; i < numAccounts; i++) {
        cout << info[i].number << " " << info[i].name << " " << info[i].balance << endl;
    }
    
    cout << "----------------------------" << endl;
    
    for (int i = 0; i < numAccounts; i++) {
        cout << index[i].accountNumber << " " << index[i].filePosition << endl;
    }
    */
     
     
     
    return 0;
}