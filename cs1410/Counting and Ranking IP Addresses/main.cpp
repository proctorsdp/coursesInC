//
//  main.cpp
//  IP Address Sorter
//
//  Created by Steven Proctor on 1/22/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>

using namespace std;

class IPRecord {
private:
    unsigned int m_IP;      // IP address as a 32-bit unsigned int
    unsigned int m_freq;    // frequency of the IP
    
public:
    IPRecord() { m_IP = 0; m_freq = 0;  }
    
    void setIP(int IP)  { m_IP = IP; }
    void incFrequency() { m_freq++; }
    void resetFrequency() { m_freq = 1; }   //sets frequency to 1
    
    unsigned int getIP()        { return m_IP;}
    unsigned int getFrequency() { return m_freq;}
};

int binarySearch(IPRecord *pTable, int size, unsigned int IP)
{
    // TODO: Task 1 - 5 points.
    // Lookup IPRecord with the given IP
    bool found = false;     //reads true if the IP address is found in the array
    int f, m, l;    //first, middle, and last element of the array.
    f = 0;
    l = size-1;
    m = (f + l) / 2;
    
    //Binary Search
    while (f <= l) {
        if (IP == pTable[m].getIP()) {
            found = true;
            break;
        }
        if (IP > pTable[m].getIP()) {
            f = m + 1;
        }
        else {
            l = m - 1;
        }
        m = (f + l) / 2;
    }
    
    //returns position of IP address if found, and a -1 if not found
    if (found) {
        return m;
    }
    else {
        return -1;
    }
}

int insert(IPRecord *pTable, int& rSize, unsigned int IP) {
    // TODO: Task 2 - 10 points.
    // Create an IPRecord for the given IP and insert it in the proper location
    // to keep array pTable sorted increasingly by IPs.
    int element = rSize-1;
    //compares the current IP value to the IP value of the last element.
    if (element > -1) {
        while (IP < pTable[element].getIP()) {
            pTable[element+1] = pTable[element];    //moves elements back 1 at a time until the new IP is located properly
            element--;
            if (element == -1) {    //allows a new IP to be inserted in the first element of the array
                break;
            }
        }
    }
    //inserts the new IP in the proper location
    pTable[element+1].setIP(IP);
    //sets the frequency to 1
    pTable[element+1].resetFrequency();
    rSize++;
    return 1;
}

int sortFrequency(IPRecord *pTable, int size)
{
    // TODO: Task 3 - 5 points.
    // Sort the IP table by frequency descendingly
    IPRecord temp;
    
    //moves the 'beginning of the array' back one each time, as to sort in descending order
    for (int j = 0; j < size; j++) {
        int bigFreq = j;
        //locates the most frequent IP address
        for (int i = 0 + j; i < size; i++) {
            if (pTable[i].getFrequency() > pTable[bigFreq].getFrequency()) {
                bigFreq = i;
            }
        }
        //puts the most frequent IP address at the front of the array
        if (pTable[bigFreq].getFrequency() > pTable[j].getFrequency()) {
            temp = pTable[j];
            pTable[j] = pTable[bigFreq];
            pTable[bigFreq] = temp;
        }
    }
    
    return 1;
}


int main() {
    IPRecord *myIPTable;    // dynamic array to store all IPRecords
    int maxSize;            // allocated size of myIPTable, i.e. number of distinct IPs
    int size = 0;           // the current size of myIPTable, i.e. number of distinct IPs seen so far
    
    ifstream fi("input.txt"); // open input file
    
    fi >> maxSize;            // read table size;
    
    myIPTable = new IPRecord[maxSize]; // allocate memory
    
    unsigned ip;
    while (fi >> ip) {     // reading IP addresses from input file until the end
        int pos = binarySearch(myIPTable, size, ip);    // looking up this IP in the table
        if (pos >= 0)
            myIPTable[pos].incFrequency();      // if found: increase its frequency
        else
            insert(myIPTable, size, ip);        // if not found: insert as a new IPRecord
    }
    
    fi.close();            // close input file
    
    sortFrequency(myIPTable, size); // sort IPRecords by frequency descendingly
    
    ofstream fo("output.txt"); // open output file
    
    for (int i = 0; i < size; i++) // print each IPRecord in one line
        fo << setw(4) << myIPTable[i].getIP() << ' ' << setw(4) << myIPTable[i].getFrequency() << endl;
    
    fo.close();         // close output file
    
    delete myIPTable; // de-allocate memory;
}
