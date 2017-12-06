//
//  main.cpp
//  Sorting Stats
//
//  Created by Steven Proctor on 1/13/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

void initializeVector(vector<int> &);
void swapValues(int &, int &, int &);
int findIndex(vector<int>, int, int &);
void bubbleSort(vector<int> &, int &, int &);
void selectionSort(vector<int> &, int &, int &);
void printVector(vector<int> &);
void countVector(bool, int);

int main() {
    int m_length = 10;
    int m_width = 15;
    int m_selectionSwap, m_selectionCompare, m_bubbleSwap, m_bubbleCompare;
    vector<int> numbers(m_length);
    bool m_swap = true;
    
    //Create and print vector
    cout << "Vector of " << m_length << " random numbers:" << endl << endl;
    initializeVector(numbers);
    printVector(numbers);
    
    //Bubble Sort and print vector
    cout << endl << "----------------" << endl << endl;
    cout << "Ascending Bubble Sort:" << endl << endl;
    bubbleSort(numbers, m_bubbleSwap, m_bubbleCompare);
    printVector(numbers);
    
    //Create and print vector
    cout << endl << "~~~~~~~~~~~~~~~~" << endl << endl;
    cout << "Vector of " << m_length << " random numbers:" << endl << endl;
    initializeVector(numbers);
    printVector(numbers);
    
    //Selection sort vector
    cout << endl << "----------------" << endl << endl;
    cout << "Ascending Selection Sort:" << endl << endl;
    selectionSort(numbers, m_selectionSwap, m_selectionCompare);
    printVector(numbers);
    
    //Count number of swaps
    cout << endl << "~~~~~~~~~~~~~~~~" << endl << endl;
    cout << "Number of Swaps needed per sort:" << endl << endl;
    cout << setw(4) << "Size" << setw(m_width) << "Bubble" << setw(m_width) << "Selection" << endl;
    countVector(m_swap, m_width);
    
    //Count number of compares
    cout << endl << "~~~~~~~~~~~~~~~~" << endl << endl;
    cout << "Number of Compares needed per sort:" << endl << endl;
    cout << setw(4) << "Size" << setw(m_width) << "Bubble" << setw(m_width) << "Selection" << endl;
    m_swap = false;
    countVector(m_swap, m_width);
    
    cout << endl << endl;
    
    return 0;
}

//Fill vector with random numbers
void initializeVector(vector<int> &rRandomVector) {
    for (int i = 0; i < rRandomVector.size(); i++) {
        rRandomVector[i] = rand()%100;
    }
}

//Swap two values
void swapValues(int &ra, int &rb, int &rSwap) {
    int m_temp;
    m_temp = ra;
    ra = rb;
    rb = m_temp;
    rSwap++;
}

//Identify largest number in vector
int findIndex(vector<int> maxVector, int n, int &compareCount) {
    int m_maxValue = 0;
    
    for (int i = 0; i < n; i++) {
        
        if (maxVector[i] > maxVector[m_maxValue]) {
            m_maxValue = i;
        }
        compareCount++;
    }
    
    return m_maxValue;
}

//Bubble sort the vector
void bubbleSort(vector<int> &rBubbleVector, int &rSwapCount, int &rCompareCount) {
    bool m_swap = true;
    int m_numSwaps = 0;
    int m_compare = 0;
    
    while (m_swap) {
        m_swap = false;
        
        for (int i = 0; i < rBubbleVector.size() - 1; i++) {
            
            if(rBubbleVector[i] > rBubbleVector[i + 1]) {
                swapValues(rBubbleVector[i], rBubbleVector[i + 1], m_numSwaps);
                m_swap = true;
            }
            m_compare++;
        }
    }
    
    rSwapCount = m_numSwaps;
    rCompareCount = m_compare;
}

//Selection sort the vector
void selectionSort(vector<int> &rSelectionVector, int &rSwapCount, int &rCompareCount) {
    int m_maxElement;
    int m_swaps = 0;
    int m_compare = 0;
    
    for (int i = 0; i < rSelectionVector.size(); i++) {
        m_maxElement = findIndex(rSelectionVector, (int)rSelectionVector.size() - i, m_compare);
        if (rSelectionVector[m_maxElement] > rSelectionVector[rSelectionVector.size() - i - 1]) {
            swapValues(rSelectionVector[m_maxElement], rSelectionVector[rSelectionVector.size() - i - 1], m_swaps);
        }
    }
    
    rSwapCount = m_swaps;
    rCompareCount = m_compare;
}

//Print the numbers in the vector
void printVector(vector<int> &rPrintVector) {
    for (int i = 0; i < rPrintVector.size(); i++) {
        cout << rPrintVector[i] << endl;
    }
}

//Prints the number of compares and swaps needed to sort the vector
//Incremented by 100
void countVector(bool rSwap, int rWidth) {
    int m_selectionSwap, m_selectionCompare, m_bubbleSwap, m_bubbleCompare;
    
    for (int i = 100; i <= 1000;) {
        int length = i;
        vector<int> numbers(length);
        initializeVector(numbers);
        bubbleSort(numbers, m_bubbleSwap, m_bubbleCompare);
        initializeVector(numbers);
        selectionSort(numbers, m_selectionSwap, m_selectionCompare);
        
        if (rSwap) {
            cout << setw(4) << i << setw(rWidth) << m_bubbleSwap << setw(rWidth) << m_selectionSwap << endl;
        }
        else {
            cout << setw(4) << i << setw(rWidth) << m_bubbleCompare << setw(rWidth) << m_selectionCompare << endl;
        }
        
        i+=100;
    }
}