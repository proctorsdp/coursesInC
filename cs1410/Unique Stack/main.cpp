//
//  main.cpp
//  Unique Stack
//
//  Created by Steven Proctor on 4/4/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include "stack.hpp"

using namespace std;

template <class T>
TUStack<T>::TUStack(int num) {
    //Error check to see if 'num' is a negative value;
    maxSize = num;
    if (num < 1) {printError(1); return;}
    data = new T[num];
    top = 0;
    nSize = 0;
}

template <class T>
void TUStack<T>::push(T item) {
    temp = item;
    //Error check to see if a duplicate item already exists in the stack
    if(searchStack(item)) {printError(2); return;}
    
    //If the stack is allowed to grow, uncomment the following line.
    //if (top == nSize) {addElement();}
    if (nSize == maxSize) {printError(3); return;}
    data[top] = item;
    top++;
    nSize++;
}

template <class T>
T TUStack<T>::pop() {
    if (top == 0) {printError(4);}// return;}
    //Error check to see if 2nd element is now first, etc.
    T temp;
    temp = data[top-1];
    removeElement();
    return temp;
}


template <class T>
T& TUStack<T>::operator[](int i) {
    index = i;
    //Error check to verify 'i' lies within appropriate bounds
    if (i < 0 || i >= maxSize) {printError(5);}
    if (top <= 0) {printError(6);}// return;}
    return data[i];
}

template <class T>
bool TUStack<T>::searchStack(T newItem) {
    for (int i = 0; i < nSize; i++) {
        if (newItem == data[i]) {return true;}
    }
    return false;
}

template <class T>
void TUStack<T>::removeElement() {
    T *temp = new T[maxSize];
    for (int i = 0; i < nSize; i++) {temp[i] = data[i];}
    if (top == 0) {return;}
    top--;
    nSize--;
    delete [] data;
    data = temp;
}

template <class T>
void TUStack<T>::printError(int caseNum) {
    int display;
    T entry;
    cout << "******************************************************************\n";
    switch (caseNum) {
        case 1: cout << "Cannot initialize stack with a negative value for size.\n";
            display = maxSize;
            break;
        case 2: cout << "Cannot add new item. A duplicate item already exists in the stack.\n";
            entry = temp;
            break;
        case 3: cout << "Cannot add new item. The stack is full.\n";
            entry = temp;
            break;
        case 4: cout << "There is nothing left on the stack to remove.\n";
            break;
        case 5: cout << "That index doesn't lie within the bounds of the stack.\n";
            display = index;
            break;
        case 6: cout << "There is nothing left on the stack.\n";
            break;
        default: cout << "Unknown Error.\n";
            break;
    }
    cout << "Current Stack Size: " << size() << endl;
    cout << "Current Position: " << position() << endl;
    if (caseNum == 1 || caseNum == 5) {
        cout << "You entered: " << display << endl;
    }
    else if (caseNum == 2 || caseNum == 3) {
        cout << "You entered: " << entry << endl;
    }
    //cout << "Quitting...\n";
    cout << "******************************************************************\n";
    //exit(caseNum);
    return;
}


int main() {
    
    cout << "Attempting to initialize with negative value:\n";
    //TEST: INITIALIZE WITH NEGATIVE VALUE
    int maxSize = -5;
    TUStack<int> testStack(maxSize);
    cout << endl;
    
    
    cout << "Attempting to initialize with positive value:\n";
    //Initialize int and string stacks
    maxSize = 5;
    TUStack<int> intStack(maxSize);
    TUStack<string> stringStack(maxSize);
    cout << endl;
    
    
    cout << "------------" << endl;
    cout << "Integer Test" << endl;
    cout << "------------" << endl;
    
    
    cout << "Filling stack with random integers:\n";
    //Fill stack with random integers
    for (int i = 0; i < maxSize - 1; i++) {
        intStack.push(rand()%100);
    }
    intStack.push(42);
    cout << endl;
    
    
    cout << "Attempting to push a new element onto a full stack:\n";
    //TEST: PUSH ELEMENT ONTO A FULL STACK
    intStack.push(rand()%100);
    cout << endl;
    
    
    cout << "Attempting to push a duplicate element onto the stack:\n";
    //TEST: PUSH A DUPLICATE ELEMT ONTO AN ARRAY
    intStack.push(42);
    cout << endl;
    
    
    cout << "Printing using [] operator:\n";
    //Print stack using [] operator
    for (int i = 0; i < maxSize; i++) {
        cout << intStack[i] << endl;
    }
    cout << endl;
    
    
    cout << "Attempting to access element outside of stack bounds:\n";
    //TEST: PRINT BEYOND BOUNDS USING [] OPERATOR
    intStack[-1];
    cout << endl;
    
    
    cout << "Printing using pop function:\n";
    //Prints stack using pop function
    for (int i = 0; i < maxSize; i++) {
        cout << intStack.pop() << endl;
    }
    cout << endl;
    
    
    cout << "Attempting to pop an element off an empty array:\n";
    //TEST: POP AN ELEMENT OFF AN EMPTY FUNCTION
    intStack.pop();
    cout << endl;
    
    
    
    cout << "Verifying the stack is empty:\n";
    //TEST: VERIFY THAT STACK IS EMPTY
    intStack[0];
    cout << endl;
    
    
    
    cout << "Filling stack with random integers:\n";
    //Refilles the stack with random ints
    for (int i = 0; i < maxSize; i++) {
        intStack.push(rand()%100);
    }
    cout << endl;
    
    
    
    cout << "Printing using [] operator:\n";
    //Print the new stack using [] operator
    for (int i = 0; i < maxSize; i++) {
        cout << intStack[i] << endl;
    }
    cout << endl;
    
    
    
    cout << "-----------" << endl;
    cout << "String Test" << endl;
    cout << "-----------" << endl;
    
    
    cout << "Filling stack with random strings:\n";
    //Fill stack with strings
    stringStack.push("Jack Sheppard");
    stringStack.push("John Locke");
    stringStack.push("Kate Austin");
    stringStack.push("Charlie Pace");
    stringStack.push("James Ford");
    cout << endl;
    
    
    
    cout << "Attempting to push a new element onto a full stack:\n";
    //TEST: PUSH ELEMENT ONTO FULL STACK
    stringStack.push("Micheal Faraday");
    cout << endl;
    
    
    cout << "Attempting to push a duplicate element onto the stack:\n";
    //TEST: PUSH A DUPLICATE ELEMENT ONTO STACK
    stringStack.push("John Locke");
    cout << endl;
    
    
    cout << "Printing using [] operator:\n";
    //Print the stack using [] operator
    for (int i = 0; i < maxSize; i++) {
        cout << stringStack[i] << endl;
    }
    cout << endl;
    
    
    cout << "Attempting to access element outside of stack bounds:\n";
    //TEST: ACCESS ELEMENTS OUTSIDE OF STACK
    stringStack[6];
    cout << endl;
    
    
    cout << "Printing using pop function:\n";
    //Print stack using pop function
    for (int i = 0; i < maxSize; i++) {
        cout << stringStack.pop() << endl;
    }
    cout << endl;
    
    
    cout << "Attempting to pop an element off an empty array:\n";
    //TEST: POP AN ELEMENT OFF AN EMPTY FUNCTION
    stringStack.pop();
    cout << endl;
    
    
    cout << "Verifying the stack is empty:\n";
    //TEST: VERIFY THAT STACK IS EMPTY
    stringStack[0];
    cout << endl;
    

    
    cout << "Filling stack with random strings:\n";
    //Refilles the stack with random ints
    stringStack.push("Chuck Bartowski");
    stringStack.push("John Casey");
    stringStack.push("Sarah");
    stringStack.push("Morgan");
    stringStack.push("Captain Awesome");
    cout << endl;
    
    
    
    cout << "Printing using [] operator:\n";
    //Print the new stack using [] operator
    for (int i = 0; i < maxSize; i++) {
        cout << stringStack[i] << endl;
    }
    cout << endl;
    

    cout << endl << "TEST COMPLETE" << endl << endl;;
    
    return 0;
}
