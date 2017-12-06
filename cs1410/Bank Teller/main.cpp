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

const int SIGNATURE_SIZE = 4, HEADER_RESERVED = 24, ACCOUNT_NAME = 20, ACCOUNT_RESERVED = 96;

struct BNKHeader {
    char signature[SIGNATURE_SIZE] = {'B', 'A', 'N', 'K'};
    int numOfAccounts;
    char reserved[HEADER_RESERVED];
};

struct BNKAccount {
    int number;
    char name[ACCOUNT_NAME];
    double balance;
    char reserved[ACCOUNT_RESERVED];
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
        for (int j = 0; j < ACCOUNT_NAME; j++) {
            s[j] = '\0';
        }
        
        getline(fin, s, ',');
        info[i].number = stoi(s);
        index[i].accountNumber = info[i].number;
        index[i].filePosition = indexPos;
        indexPos += 128;
    
        getline(fin, s, ',');
        for (int j = 0; j < ACCOUNT_NAME; j++) {
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

//Finds the position of the account in the binary file
long findAccount(string input, BNKIndex *&newIndex, int numAcc, int &m) {
    int accNum;
    accNum = stoi(input);
    int f = 0, l = numAcc - 1;
    m = ((f+l)/2);
    
    //binary search
    while (accNum != newIndex[m].accountNumber) {
        if (f >= l) {return -1;}
        else if (accNum < newIndex[m].accountNumber) {
            l = m - 1;
            m = ((f+l)/2);
        }
        else if (accNum > newIndex[m].accountNumber) {
            f = m + 1;
            m = ((f+l)/2);
        }
    }
    
    //returns position of account
    return newIndex[m].filePosition;
}

//displays account info
void displayAccount(BNKIndex *&newIndex, int numAcc) {
    string accNum, next;
    long accPos;
    int indexNum;
    
    cout << "\nEnter: [account #]\n";
    cout << "# ";
    
    getline(cin, accNum);
    accPos = findAccount(accNum, *&newIndex, numAcc, indexNum);
    
    //checks to see if the account exists
    if (accPos == -1) {
        cout << "\nAccount does not exist.\n";
        cout << "Press Enter to continue\n";
        getline(cin, next);
        return;
    }
    
    else {
        //Reads in account info from file
        BNKAccount temp;
        fstream AccountInfo("AccountInfo.bnk", ios::in | ios::binary);
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.read(reinterpret_cast<char *>(&temp), sizeof(BNKAccount));
        
        //prints account info
        cout << "\nAccount Number: " << temp.number << endl;
        cout << "Name: " << temp.name << endl;
        cout << "Balance: " << temp.balance << endl;
        
        cout << endl << "Press Enter to continue\n";
        getline(cin, next);
        AccountInfo.close();
    }
    
    
}

void depositMoney(BNKIndex *&newIndex, int numAcc) {
    string accNum, deposit, next;
    long accPos;
    int indexNum;
    
    cout << "\nEnter: [account #] [amount to deposit]\n";
    cout << "# ";
    
    getline(cin, accNum, ' ');
    getline(cin, deposit);
    accPos = findAccount(accNum, *&newIndex, numAcc, indexNum);
    
    //checks to see if the account exists
    if (accPos == -1) {
        cout << "\nAccount does not exist.\n";
        cout << "Press Enter to continue\n";
        getline(cin, next);
        return;
    }
    
    else {
        //reads in account info and adds deposit to balance
        BNKAccount temp;
        fstream AccountInfo("AccountInfo.bnk", ios::in | ios::out | ios::binary);
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.read(reinterpret_cast<char *>(&temp), sizeof(BNKAccount));
        temp.balance += stof(deposit);
        
        //writes new balance to file
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.write((char *)&temp, sizeof(BNKAccount));
        
        //reads in account info
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.read(reinterpret_cast<char *>(&temp), sizeof(BNKAccount));
        
        //displays account info
        cout << "\nAccount Number: " << temp.number << endl;
        cout << "Name: " << temp.name << endl;
        cout << "Balance: " << temp.balance << endl;
        
        cout << endl << "Press enter to continue\n";
        getline(cin, next);
        AccountInfo.close();
    }
    
}

void withdrawMoney(BNKIndex *&newIndex, int numAcc) {
    string accNum, withdraw, next;
    long accPos;
    int indexNum;
    
    cout << "\nEnter: [account #] [amount to withdraw]\n";
    cout << "# ";
    
    getline(cin, accNum, ' ');
    getline(cin, withdraw);
    accPos = findAccount(accNum, *&newIndex, numAcc, indexNum);
    
    //checks to see if the account exists
    if (accPos == -1) {
        cout << "\nAccount does not exist\n";
        cout << "Press Enter to continue\n";
        getline(cin, next);
        return;
    }
    
    else {
        //reads in account info and subtracts withdrawl
        BNKAccount temp;
        fstream AccountInfo("AccountInfo.bnk", ios::in | ios::out | ios::binary);
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.read(reinterpret_cast<char *>(&temp), sizeof(BNKAccount));
        temp.balance -= stof(withdraw);
        
        //writes new balance to file
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.write((char *)&temp, sizeof(BNKAccount));
        
        //reads in account info
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.read(reinterpret_cast<char *>(&temp), sizeof(BNKAccount));
        
        //prints account info
        cout << "\nAccount Number: " << temp.number << endl;
        cout << "Name: " << temp.name << endl;
        cout << "Balance: " << temp.balance << endl;
        
        cout << endl << "Press enter to continue\n";
        getline(cin, next);
        AccountInfo.close();
    }
}

void createAccount(BNKIndex *&newIndex, int &numAcc) {
    string accNum, name, balance, next;
    long accPos;
    int indexNum;
    
    cout << "\nEnter: [account #],[name],[starting balance]\n";
    cout << "# ";
    
    getline(cin, accNum, ',');
    getline(cin, name, ',');
    getline(cin, balance);
    accPos = findAccount(accNum, *&newIndex, numAcc, indexNum);
    
    //checks to see if the account exists
    if (accPos != -1) {
        cout << "\nAn Account with that number already exists.\nPlease enter a different account number\n";
        createAccount(*&newIndex, numAcc);
    }
    
    else {
        //creates new account struct
        BNKAccount addAccount;
        addAccount.number = stoi(accNum);
        for (int i = 0; i < ACCOUNT_NAME; i++) {
            addAccount.name[i] = name[i];
        }
        addAccount.balance = stof(balance);
        
        //writes account info after the last BNK account in the binary file
        fstream AccountInfo("AccountInfo.bnk", ios::in | ios::out | ios::binary);
        AccountInfo.seekp(sizeof(BNKHeader) + (sizeof(BNKAccount) * numAcc), ios::beg);
        AccountInfo.write((char*)&addAccount, sizeof(BNKAccount));
        
        //Creates an index for new account and increments number of accounts
        newIndex[numAcc].accountNumber = stoi(accNum);
        newIndex[numAcc].filePosition = (sizeof(BNKHeader) + (sizeof(BNKAccount) * numAcc));
        numAcc++;
        
        //sorts the updated index
        sortIndex(newIndex, numAcc);
        
        //writes the updated index after the BNK accounts in the binary file
        AccountInfo.seekp(sizeof(BNKHeader) + (sizeof(BNKAccount) * numAcc), ios::beg);
        AccountInfo.write((char*)&newIndex, sizeof(BNKIndex) * numAcc);
        
        cout << "\nNew account created.\nPress Enter to continue\n";
        getline(cin, next);
    }
    
}

void deleteAccount(BNKIndex *&newIndex, int &numAcc) {
    string accNum, next;
    long accPos;
    int indexNum;
    
    cout << "\nEnter: [account #]\n";
    cout << "# ";
    
    getline(cin, accNum);
    accPos = findAccount(accNum, *&newIndex, numAcc, indexNum);
    
    //checks to see if the account exists
    if (accPos == -1) {
        cout << "\nNo Account with that number exists.\nPlease enter a different account number\n";
        deleteAccount(*&newIndex, numAcc);
    }
    
    else {
        //reads in account info to be deleted
        BNKAccount deleteAccount;
        fstream AccountInfo("AccountInfo.bnk", ios::in | ios::out | ios::binary);
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.read(reinterpret_cast<char *>(&deleteAccount), sizeof(BNKAccount));
        
        //deletes data in BNK account
        deleteAccount.number = NULL;
        for (int i = 0; i < ACCOUNT_NAME; i++) {
            deleteAccount.name[i] = NULL;
        }
        deleteAccount.balance = NULL;
        
        //Writes empty data over the account data in the BNK file
        AccountInfo.seekg(accPos, ios::beg);
        AccountInfo.write((char *)&deleteAccount, sizeof(BNKAccount));
        
        //writes over the old index values by shifting all index structs after the deleted index to the left
        for (int i = indexNum; i < numAcc -1; i++) {
            newIndex[indexNum].accountNumber = newIndex[indexNum + 1].accountNumber;
            newIndex[indexNum].filePosition = newIndex[indexNum + 1].filePosition;
        }
        
        //deletes the last index to compensate for deleted account
        newIndex[numAcc].accountNumber = NULL;
        newIndex[numAcc].filePosition = NULL;
        
        //sorts updated index
        sortIndex(newIndex, numAcc);
        
        //writes updated index to the BNK file just after the BNK accounts
        AccountInfo.seekp(sizeof(BNKHeader) + (sizeof(BNKAccount) * numAcc), ios::beg);
        AccountInfo.write((char*)&newIndex, sizeof(BNKIndex) * numAcc);
        
        cout << "\nAccount deleted.\nPress Enter to continue\n";
        getline(cin, next);
        AccountInfo.close();
    }
    
}

void displayMenu(BNKIndex *&newIndex, int &numAcc) {
    string command;
    
    //Prints menu, obtains commamd
    cout << "Welcome to BNK Banking\n\n";
    cout << "Please choose from the following commands\n\n";
    cout << "Display an account     (Enter: display)\n";
    cout << "Deposit money          (Enter: deposit)\n";
    cout << "Withdraw money         (Enter: withdraw)\n";
    cout << "Create an account      (Enter: create)\n";
    cout << "Delete an account      (Enter: delete)\n";
    cout << "Quit program           (Enter: quit)\n\n";
    cout << "# ";
    getline(cin, command);
    
    //calls function according to command
    if (command == "display") {displayAccount(*&newIndex, numAcc);}
    else if (command == "deposit") {depositMoney(*&newIndex, numAcc);}
    else if (command == "withdraw") {withdrawMoney(*&newIndex, numAcc);}
    else if (command == "create") {createAccount(*&newIndex, numAcc);}
    else if (command == "delete") {deleteAccount(*&newIndex, numAcc);}
    else if (command == "quit") {return;}
    else {cout << "\nInvalid Entry\n\n";}
    cout << endl << endl;
    
    //repeats menu driven program until user enters 'quit'
    displayMenu(*&newIndex, numAcc);
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
    header.numOfAccounts = numAccounts;
    //For some reason the above line of code causes the signature in the header struct to include the number 2. When using cout to debug the program, the signature is printed as: BANK2
    //I checked with the tutors and they had no idea what caused this issue. They said that they had seen this occur in everyone's code
    
    //Ouput information to bnk (binary) file
    fstream outfile;
    outfile.open("AccountInfo.bnk", ios::out | ios::binary);
    outfile.seekp(0L, ios::beg);
    outfile.write((char *)&header, sizeof(BNKHeader));
    outfile.seekp(sizeof(BNKHeader), ios::beg);
    outfile.write((char *)info, sizeof(BNKAccount)*numAccounts);
    sortIndex(index, numAccounts);
    outfile.seekp((sizeof(BNKHeader) + (numAccounts * sizeof(BNKAccount))), ios::beg);
    outfile.write((char *)index, sizeof(BNKIndex)*numAccounts);
    
    //Close files
    fin.close();
    outfile.close();
    
    bool BNK = true;
    char ch;
    
    fstream AccountInfo("AccountInfo.bnk", ios::in | ios::binary);
    
    //Check if file exits
    if (AccountInfo.fail()) {
        cout << "Error opening file\n";
        cout << "Exiting...\n";
        exit(3);
    }
    
    //checks if file is a BNK file
    for (int i = 0; i < 4; i++) {
        AccountInfo.seekg(i, ios::beg);
        AccountInfo.get(ch);
        if (ch != header.signature[i]) {BNK = false;}
    }
    
    //exits program if file is not a BNK file
    if (BNK == false) {
        cout << "Not a BNK file\n";
        cout << "Exiting...\n";
        exit(4);
    }
    
    //Obtains number of account contained in BNK file
    AccountInfo.seekg(0L, ios::beg);
    AccountInfo.read(reinterpret_cast<char *>(&header), sizeof(BNKHeader));
    numAccounts = header.numOfAccounts;
    
    //saves index to memory
    BNKIndex *newIndex;
    newIndex = new BNKIndex[sizeof(BNKIndex) * header.numOfAccounts];
    int i = 0;
    while (!AccountInfo.eof()) {
        AccountInfo.seekg((sizeof(BNKHeader) + ((header.numOfAccounts) * sizeof(BNKAccount)) + (i * sizeof(BNKIndex))), ios::beg);
        AccountInfo.read(reinterpret_cast<char *>(index), sizeof(BNKIndex));
        newIndex[i] = index[i];
        i++;
    }
    
    //begins menu drived program
    displayMenu(*&newIndex, header.numOfAccounts);
    
    AccountInfo.close();
    
    return 0;
}