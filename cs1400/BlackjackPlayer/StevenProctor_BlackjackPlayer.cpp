#include "StevenProctor_BlackjackPlayer.h"
#include "Card.h"
#include "Hand.h"
#include "Scoreboard.h"

StevenProctor_BlackjackPlayer::StevenProctor_BlackjackPlayer() {
}

/**
 * This function is called when it's your turn and you need to
 * choose whether to hit (return true) or stand (return false).
 *
 * The hand parameter tells you what's in your hand. You can call
 * getSuit(), getRank(), getLowValue(), and getHighValue() on each of
 * the cards it contains.
 *
 * The dealerUpCard parameter works the same way, and tells you what the
 * dealer up card is.
 *
 * You must return a value from this function indicating whether you want
 * to hit or stand. Return true if you want to hit and false if you want to stand.
 */
bool StevenProctor_BlackjackPlayer::hit(vector<Card> hand, Card dealerUpCard) {
    int value = 0, numAces = 0;
    bool hit = false, ace = false, soft = true;
    //Obtain high value for hand & determine how many aces in hand.
    for (int i = 0; i < hand.size(); i++) {
        value += hand[i].getHighValue();
        if (hand[i].getHighValue() == 11) {
            ace = true;
            numAces++;
        }
    }
    //Alters value for hand if over 21 and has aces.
    if (ace == true) {
        while ((value > 21) && (numAces > 0)) {
            value -= 10;
            numAces--;
        }
        if (numAces == 0) {
            soft = false;
        }
    }
    //Soft Hits
    if ((ace == true) && (soft == true)) {
        if (value > 18) {
            
        }
        else if (value > 17) {
            if ((dealerUpCard.getHighValue() > 8) && (dealerUpCard.getHighValue() < 12)) {
                hit = true;
            }
        }
        else {
            hit = true;
        }
    }
    //Hard hits
    else {
        if (value > 16) {
            
        }
        else if (value > 12) {
            if ((dealerUpCard.getHighValue() > 6) && (dealerUpCard.getHighValue() < 12)) {
                hit = true;
            }
        }
        else if (value > 11) {
            if ((dealerUpCard.getHighValue() > 1) && (dealerUpCard.getHighValue() < 4)) {
                hit = true;
            }
            else if ((dealerUpCard.getHighValue() > 6) && (dealerUpCard.getHighValue() < 12)) {
                hit = true;
            }
        }
        else {
            hit = true;
        }
    }
    return hit;
}

/**
 * This function is called when it's your turn and you need to
 * choose to double down or not. If you choose to double down, you
 * will double your initial bet and receive one more card, then your
 * turn is over. Typically you would only double down if you think you
 * have a really good chance of beating the dealer base on your own hand
 * and the dealer's visible card.
 *
 * The hand parameter tells you what's in your hand. You can call
 * getSuit(), getRank(), getLowValue(), and getHighValue() on each of
 * the cards it contains.
 *
 * The dealerUpCard parameter works the same way, and tells you what the
 * dealer up card is.
 *
 * You must return a value from this function indicating whether you want
 * to double down or not. Return true if you want to double down and false
 * if you do not.
 */
bool StevenProctor_BlackjackPlayer::doubleDown(vector<Card> hand, Card dealerUpCard) {
    int value = 0, numAces = 0;
    bool doubleDown = false, ace = false, soft = true;
    //Obtain high value for hand & determine how many aces in hand.
    for (int i = 0; i < hand.size(); i++) {
        value += hand[i].getHighValue();
        if (hand[i].getHighValue() == 11) {
            ace = true;
            numAces++;
        }
    }
    //Alters value for hand if over 21 and has aces.
    if (ace == true) {
        while ((value > 21) && (numAces > 0)) {
            value -= 10;
            numAces--;
        }
        if (numAces == 0) {
            soft = false;
        }
    }
    //Soft double downs
    if ((ace == true) && (soft == true)) {
        if (value > 18) {
            
        }
        else if (value > 16 ) { // Changed 17 to 16
            if ((dealerUpCard.getHighValue() > 2) && (dealerUpCard.getHighValue() < 7)) { //Changed Low from 1 to 2
                doubleDown = true;
            }
        }
        else if (value > 14) {
            if ((dealerUpCard.getHighValue() > 3) && (dealerUpCard.getHighValue() < 7)) {
                doubleDown = true;
            }
        }
        else if (value > 12) {
            if ((dealerUpCard.getHighValue() > 4) && (dealerUpCard.getHighValue() < 7)) {
                doubleDown = true;
            }
        }
    }
    //Hard double downs
    else {
        if (value == 9) {
            if ((dealerUpCard.getHighValue() > 2) && (dealerUpCard.getHighValue() < 7)) {
                doubleDown = true;
            }
        }
        else if (value == 10) {
            if ((dealerUpCard.getHighValue() > 1) && (dealerUpCard.getHighValue() < 10)) {
                doubleDown = true;
            }
        }
        else if (value == 11) {
            if ((dealerUpCard.getHighValue() > 1) && (dealerUpCard.getHighValue() < 11)) {
                doubleDown = true;
            }
        }
    }
    return doubleDown;
}

/**
 * This function is called to determine what your initial bet will be.
 * The function must return an integer between the values of 10 and 100.
 * The lowest bet you can make is 10 and the highest is 100. If you are
 * thinking of cheating and entering a number that is not in that range,
 * know that the game code checks to make sure a valid value is returned
 * and if it is not, your initialBet will default to 10.
 */
int StevenProctor_BlackjackPlayer::initialBet() {
    return 100;
}