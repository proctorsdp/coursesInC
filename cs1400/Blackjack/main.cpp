//
//  main.cpp
//  Blackjack
//
//  Created by Steven Proctor on 4/11/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <string>
#include "Blackjack.h"

using namespace std;

int main() {
    
    string choice, playAgain = "y";
    
    while (playAgain != "n") {
        
        Blackjack game;
    
        Blackjack();
    
        game.displayInstructions();
    
        cout << "Dealing Cards...\n" << endl;
    
        game.displayPlayerHand();
    
        if (game.getPlayerScore() != 21) {
            cout << "You currently have a score of: " << game.getPlayerScore() << endl << endl;
        }
        else {
            cout << "You currently have a score of: " << game.getPlayerScore() << ", Blackjack!" << endl << endl;
        }
    
        game.displayDealerHand();
        
        if (game.getDealerScore() != 21) {
            cout << "Dealer currently has a score of: " << game.getDealerScore() << endl << endl;
        }
        else {
             cout << "Dealer currently has a score of: " << game.getDealerScore() << ", Blackjack!" << endl << endl;
        }
    
        if (game.getDealerScore() != 21) {
            cout << "Enter Move: ";
            cin >> choice;
        }
    
        while (game.getStatus() == PLAYER_TURN) {
            while (((choice != "h") && (choice != "p")) || (choice.length() != 1)) {
                cout << endl << "Invalid Entry. Enter 'h' to hit, and 'p' to pass.\n" << endl;
                cout << "Enter Move: ";
                cin >> choice;
            }
    
            if (choice == "h") {
                game.makeMove(HIT);
                cout << endl;
                game.displayPlayerHand();
                if (game.getPlayerScore() < 22) {
                    if (game.getPlayerScore() == 21) {
                        cout << "You currently have a score of: " << game.getPlayerScore() << ", Blackjack!" << endl << endl;
                    }
                    else {
                        cout << "You currently have a score of: " << game.getPlayerScore() << endl << endl;
                    }
                    cout << "Enter Move: ";
                    cin >> choice;
                }
                else {
                    cout << "You busted!" << endl;
                }
            }
            else if (choice == "p") {
                game.makeMove(PASS);
            }
        }
    
        if (game.getDealerScore() != 21) {
            cout << endl;
            game.displayDealerHand();
            cout << "Dealer currently has a score of: " << game.getDealerScore() << endl << endl;
        }
    
        while (game.getStatus() == DEALER_TURN) {
            game.dealerStrategy();
        }
    
        switch (game.getStatus()) {
            case PLAYER_WIN: cout << "You win! With " << game.getPlayerScore() << ", to the Dealer's " << game.getDealerScore() << endl << endl;
            break;
            case DEALER_WIN: cout << "Dealer wins! With " << game.getDealerScore() << ", to your " << game.getPlayerScore() << endl << endl;
                break;
            default: cout << "ERROR" << endl;
                break;
        }
        
        cout << endl << "Would you like to play again? ";
        cin >> playAgain;
        while (((playAgain != "y") && (playAgain != "n")) || (playAgain.length() != 1)) {
            cout << endl << "Invalid Entry. Please enter 'y' or 'n'.\n" << endl;
            cout << "Would you like to play again? ";
            cin >> playAgain;
        }
        cout << endl << endl << endl;
    }
    
    cout << "Thanks for playing!\n";
    
    return 0;
}
