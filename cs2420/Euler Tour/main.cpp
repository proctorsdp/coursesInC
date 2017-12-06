//
//  main.cpp
//  Snowblower Path
//
//  Created by Steven Proctor on 12/7/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include "graph.hpp"
#include <assert.h>

using namespace std;

int main () {
    srand(unsigned (time(0)));
    ofstream fout;
    fout.open("tourOut.txt");
    assert(fout);
    
    Graph g("prog7A.txt",fout);
    g.computeTour(fout); 
    
    Graph g1("prog7B.txt",fout);
    g1.computeTour(fout);
    
    Graph g2("prog7C.txt",cout);
    g2.computeTour(cout);
    
    return 0;
}