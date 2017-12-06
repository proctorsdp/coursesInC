#include <iostream>
#include <cstdlib>
#include "bug.h"
#include <vector>

using namespace std;


void printBugs(vector<Bug>);
void sortMass(vector<Bug> &);

//TODO:write a function that prints all the contents of the
//     bug array.  Use Bug::print() for each bug.
void printBugs(vector<Bug> b) {
    for (int i = 0; i < b.size(); i++) {
        b[i].print();
    }
}
//end of TODO

//TODO:write a function to bubble sort the contents of a
//     bug array based on the mass
void sortMass(vector<Bug> &b) {
    Bug temp;
    bool swap = true;
    
    while (swap) {
        swap = false;
        
        for (int i = 0; i < b.size() - 1; i++) {
            
            if (b[i].getMass() > b[i + 1].getMass()){
                temp = b[i];
                b[i] = b[i + 1];
                b[i + 1] = temp;
                swap = true;
            }
        }
    }
}
//end of TODO


int main(){
    const int NUMBUGS=5;
    //TODO: make a vector of NUMBUGS bugs
    vector<Bug> bug(NUMBUGS);
    //end of TODO
    
    printBugs(bug);
    cout <<"====\n";
    
    //TODO: add three more bugs to the vector
    for (int i = 0; i < 3; i++){
        bug.push_back(Bug());
    }
    //end of TODO
    
    printBugs(bug);
    cout <<"====\n";
    
    //sort the bugs
    sortMass(bug);
    
    printBugs(bug);
    cout <<"====\n";
    
    //TODO: get rid of the 5 bugs with the greatest mass
    for (int i = 0; i < 5; i++) {
        bug.pop_back();
    }
    //end of TODO
    
    printBugs(bug);
    cout <<"====\n";
    
    
    return 0;
}
