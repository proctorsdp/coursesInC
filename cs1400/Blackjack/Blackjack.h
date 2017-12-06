//
//  Blackjack.h
//  Blackjack
//
//  Created by Steven Proctor on 4/11/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#ifndef __Blackjack__Blackjack__
#define __Blackjack__Blackjack__

#include <stdio.h>
#include <vector>

using namespace std;

enum Status {
    PLAYER_TURN,
    DEALER_TURN,
    PLAYER_WIN,
    DEALER_WIN
};

enum Move {
    HIT,
    PASS
};

class Blackjack {
private:
    vector<int> playerHand;
    vector<int> dealerHand;
    bool showHole();
    int deck[14];
    Status status;
    void resolveWinner();
    void hit();
    void pass();
    int dealerScore = 0;
    int playerScore = 0;
    int j = 0;
public:
    Blackjack();
    void reset();
    Status getStatus();
    int getPlayerScore();
    void displayPlayerHand();
    int getDealerScore();
    void displayDealerHand();
    void makeMove(Move move);
    void displayInstructions();
    void dealerStrategy();
};
#endif /* defined(__Blackjack__Blackjack__) */
