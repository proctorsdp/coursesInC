//
//  main.cpp
//  Postfix Logic
//
//  Created by Steven Proctor on 4/11/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string line, answer;
    stack<bool> boolStack;
    
    cout << "Welcome to the Postfix Logic Operator Calculator\n" << endl;
    cout << "Please enter a logic problem" << endl;
    cout << "('T', 'F', '*', '+', '!', 'q')" << endl;
    cout << "# ";
    getline(cin, line);
    
    while(line[0] != 'q') {
        bool A, B, C;
        
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == 'T') {boolStack.push(true); C = true;}
            else if (line[i] == 'F') {boolStack.push(false); C = false;}
            else if (line[i] == '*') {
                B = boolStack.top();
                boolStack.pop();
                A = boolStack.top();
                boolStack.pop();
                C = A and B;
                boolStack.push(C);
            }
            else if (line[i] == '+') {
                B = boolStack.top();
                boolStack.pop();
                A = boolStack.top();
                boolStack.pop();
                C = A or B;
                boolStack.push(C);
            }
            else if (line[i] == '!') {
                C = !boolStack.top();
                boolStack.pop();
                boolStack.push(C);
            }
            else {
                cout << endl << "ERROR: Invalid Entry\n";
                cout << "Appropriate inputs are:\n";
                cout << "'F', 'T', '*', '+', '!'\n";
                cout << "Quitting....\n";
                exit(4);
            }
        }
        if (boolStack.top()) {answer = 'T';}
        else {answer = 'F';}
        while (!boolStack.empty()) {boolStack.pop();}
        cout << answer << endl << endl;
        
        for (int i = 0; i < line.size(); i++) {
            line[i] = NULL;
        }
        
        cout << "# ";
        getline(cin, line);
    }
    
    cout << "q\n";
    cout << endl << "Thanks for Playing!" << endl;
    
    return 0;
}