//
//  Blackjack.cpp
//  Blackjack
//
//  Created by Steven Proctor on 4/11/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#include "Blackjack.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


void Blackjack::resolveWinner() {
    if (getPlayerScore() < 22) {
        if (getDealerScore() > 21) {
            status = PLAYER_WIN;
        }
        else if (getPlayerScore() > getDealerScore()) {
            status = PLAYER_WIN;
        }
        else {
            status = DEALER_WIN;
        }
    }
    else {
        status = DEALER_WIN;
    }
    //Looks to see who won, and updates status
}

Blackjack::Blackjack() {
    reset();
}

void Blackjack::reset() {
    unsigned seed;
    seed = time(0);
    srand(seed);
    deck[0] = 0;
    for (int i = 1; i < 15; i++) {
        deck[i] = 4;
    }
    
    playerHand.clear();
    dealerHand.clear();
    
    for (int i = 0; i < 2; i++) {
        playerHand.push_back(rand() % 13 + 1);
        deck[playerHand[i]] -= 1;
        dealerHand.push_back(rand() % 13 + 1);
        deck[dealerHand[i]] -= 1;
    }
    status = PLAYER_TURN;
    //resets deck, empties hands, deals two cards each, starting with player
}

Status Blackjack::getStatus() {
    return status;
}

int Blackjack::getPlayerScore() {
    int l = 0;
    int handSize = playerHand.size();
    playerScore = 0;
    for (int i = 0; i < handSize; i++) {
        if (playerHand[i] < 2) {
            playerScore += 11;
        }
        else if (playerHand[i] < 11) {
            playerScore += (playerHand[i]);
        }
        else {
            playerScore += 10;
        }
    }
    while ((playerScore > 21) && (l < playerHand.size())) {
        if (playerHand[l] == 1) {
            playerScore -= 10;
        }
        l++;
    }
    return playerScore;
    //return players score
}

void Blackjack::displayPlayerHand() {
    int handSize = playerHand.size();
    cout << "Your Hand: ";
    for (int i = 0; i < handSize; i++) {
        if (playerHand[i] == 1) {
            cout << "A ";
        }
        else if (playerHand[i] >= 11) {
            switch (playerHand[i]) {
                case 11: cout << "J ";
                    break;
                case 12: cout << "Q ";
                    break;
                case 13: cout << "K ";
                    break;
                default: cout << "ERROR" << endl;
                    break;
            }
        }
        else {
            cout << playerHand[i] << " ";
        }
    }
    cout << endl;
    //displays players hand
}

int Blackjack::getDealerScore() {
    int l = 0;
    int handSize = dealerHand.size();
    dealerScore = 0;
    for (int i = 0; i < handSize; i++) {
        if (dealerHand[i] < 2) {
            dealerScore += 11;
        }
        else if (dealerHand[i] < 11) {
            dealerScore += (dealerHand[i]);
        }
        else {
            dealerScore += 10;
        }
    }
    if ((status == PLAYER_TURN) && (dealerScore != 21)) {
        if (dealerHand[1] < 2) {
            dealerScore -= 11;
        }
        else if (dealerHand[1] < 11) {
            dealerScore -= (dealerHand[1]);
        }
        else {
            dealerScore -= 10;
        }
    }
    while ((dealerScore > 21) && (l < dealerHand.size())) {
        if (dealerHand[l] == 1) {
            dealerScore -= 10;
        }
        l++;
    }
    return dealerScore;
    //return dealers score
}

void Blackjack::displayDealerHand() {
    int handSize = dealerHand.size();
    cout << "Dealer's Hand: ";
    for (int i = 0; i < handSize; i++) {
        if (getDealerScore() == 21) {
            if (dealerHand[i] == 1) {
                cout << "A ";
            }
            else if (dealerHand[i] > 10) {
                switch (dealerHand[i]) {
                    case 11: cout << "J ";
                        break;
                    case 12: cout << "Q ";
                        break;
                    case 13: cout << "K ";
                        break;
                    default: cout << "ERROR" << endl;
                        break;
                }
            }
            else {
                cout << dealerHand[i] << " ";
            }
            resolveWinner();
        }
        else {
            if ((status == PLAYER_TURN) && (i == 1)) {
                cout << "H ";
            }
            else if (dealerHand[i] == 1) {
                cout << "A ";
            }
            else if (dealerHand[i] > 10) {
                switch (dealerHand[i]) {
                    case 11: cout << "J ";
                        break;
                    case 12: cout << "Q ";
                        break;
                    case 13: cout << "K ";
                        break;
                    default: cout << "ERROR" << endl;
                        break;
                }
            }
            else {
                cout << dealerHand[i] << " ";
            }
        }
    }
    cout << endl;
    //displays dealers hand
}

void Blackjack::makeMove(Move move) {
    switch (move) {
        case HIT: hit();
            break;
        case PASS: pass();
            break;
        default: cout << "Error" << endl;
            break;
    }
    //calls hit or pass
}

void Blackjack::hit() {
    unsigned seed;
    seed = time(0);
    if (j > 0) {
        seed += j;
    }
    srand(seed);
    int deal;
    
    deal = rand() % 13 + 1;
    
    while (deck[deal] == 0) {
        deal = rand() % 13 + 1;
    }
    deck[deal] -= 1;
    switch (status) {
        case PLAYER_TURN:
            playerHand.push_back(deal);
            break;
        case DEALER_TURN:
            dealerHand.push_back(deal);
            break;
        default: cout << "ERROR" << endl;
            break;
    }
    if ((getPlayerScore() > 21) || (getDealerScore() > 21)) {
        resolveWinner();
    }
    j++;
    //deals one card based on status.
    //deals random card from deck, card must still be in deck
    //if a player busts, end game, call resolveWinner
}

void Blackjack::pass() {
    switch (status) {
        case PLAYER_TURN:
            status = DEALER_TURN;
            break;
        case DEALER_TURN:
            resolveWinner();
            break;
        default: cout << "ERROR" << endl;
            break;
    }
    //if players turn, change status to dealersturn
    //if dealers turn, end game, call resolveWinner
}

void Blackjack::displayInstructions() {
    cout << "Welcome to Blackjack! Click the flashing ad to play for real money. Trust me, it's not a scam at all...\n";
    cout << "You will play first, followed by the dealer. You may choose to hit (h) or pass (p).\n" << endl;
}

void Blackjack::dealerStrategy() {
    if (getPlayerScore() == 21) {
        while (getDealerScore() < 21) {
            cout << "Dealer hits." << endl << endl;
            hit();
            displayDealerHand();
            if (getDealerScore() < 21) {
                cout << "Dealer currently has a score of: " << getDealerScore() << endl << endl;
            }
            else if (getDealerScore() == 21) {
                cout << "Dealer currently has a score of: " << getDealerScore() << ", Blackjack!" << endl << endl;
            }
            else {
                cout << "Dealer busts!" << endl << endl;
            }
        }
    }
    
    else if (getPlayerScore() > getDealerScore()) {
        while (getDealerScore() < getPlayerScore()) {
            cout << "Dealer hits." << endl << endl;
            hit();
            displayDealerHand();
            if (getDealerScore() < 21) {
                cout << "Dealer currently has a score of: " << getDealerScore() << endl << endl;
            }
            else if (getDealerScore() == 21) {
                cout << "Dealer currently has a score of: " << getDealerScore() << ", Blackjack!" << endl << endl;
            }
            else {
                cout << "Dealer busts!" << endl << endl;
            }
        }
    }
    
    else {
        cout << "Dealer passes.\n" << endl;
        pass();
        resolveWinner();
    }
    
}