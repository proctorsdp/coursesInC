//
//  main.cpp
//  Word Frequency
//
//  Created by Steven Proctor on 4/18/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include "tree.hpp"

int main() {
    WordTree T;
    WordTree F;
    
    T.load("Input.txt");
    
    T.copyTo(F);
    
    F.save("Results.txt");
    
    
    return 0;
}
