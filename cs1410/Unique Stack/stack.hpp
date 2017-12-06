//
//  stack.hpp
//  Unique Stack
//
//  Created by Steven Proctor on 4/5/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>

template <class T>
class TUStack {
public:
    TUStack(int num);
    
    void push(T item);
    
    T pop();
    
    int size() {return nSize;}
    
    int position() {return top - 1;}
    
    T & operator[](int i);
    
private:
    T *data;
    int top;
    int nSize;
    int maxSize;
    int zero = 0;
    T temp;
    int index;
    
    bool searchStack(T newItem);
    
    void removeElement();
    
    void printError(int caseNum);
    
};

#endif /* stack_hpp */
