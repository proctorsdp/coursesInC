//
//  main.cpp
//  Connect Four
//
//  Created by Steven Proctor on 2/1/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

/**
 * @brief Check if a winner exists
 *
 * @param pBoard The board
 * @param colSize The column size
 * @param rowSize The row size
 *
 * @return The character of the winner, 0 for no winner, and 't' for a tie
 */
char checkWinner(char** pBoard, int numOfCols, int numOfRows, int winSize)
{
    // TODO
    int pInARow = 0;
    int cInARow = 0;
    int draw = 0;
    
    //Horizontal Check
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < numOfCols; j++) {
            if (pBoard[i][j] == 'p') {
                pInARow++;
                cInARow = 0;
            }
            else if (pBoard[i][j] == 'c') {
                cInARow++;
                pInARow = 0;
            }
            else {
                cInARow = 0;
                pInARow = 0;
            }
            if (pInARow == winSize) {
                return 'p';
            }
            else if (cInARow == winSize) {
                return 'c';
            }
        }
        pInARow = 0;
        cInARow = 0;
    }
    
    //Vertical Check
    for (int j = 0; j < numOfCols; j++) {
        for (int i = 0; i < numOfRows; i++) {
            if (pBoard[i][j] == 'p') {
                pInARow++;
                cInARow = 0;
            }
            else if (pBoard[i][j] == 'c') {
                cInARow++;
                pInARow = 0;
            }
            else {
                cInARow = 0;
                pInARow = 0;
            }
            if (pInARow == winSize) {
                return 'p';
            }
            else if (cInARow == winSize) {
                return 'c';
            }
        }
        pInARow = 0;
        cInARow = 0;
    }
    
    //Diagnal from top left
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j <= i; j++) {
            if (pBoard[i-j][j] == 'p') {
                pInARow++;
                cInARow = 0;
            }
            else if (pBoard[i-j][j] == 'c') {
                cInARow++;
                pInARow = 0;
            }
            else {
                cInARow = 0;
                pInARow = 0;
            }
            if (pInARow == winSize) {
                return 'p';
            }
            else if (cInARow == winSize) {
                return 'c';
            }
        }
        pInARow = 0;
        cInARow = 0;
    }
    
    //Diagonal from top right
    int k = numOfCols;
    for (int i = 0; i < i + k; i++) {
        for (int j = 0; j < i; j++) {
            if (pBoard[j][j+k] == 'p') {
                pInARow++;
                cInARow = 0;
            }
            else if (pBoard[j][j+k] == 'c') {
                cInARow++;
                pInARow = 0;
            }
            else {
                cInARow = 0;
                pInARow = 0;
            }
            if (pInARow == winSize) {
                return 'p';
            }
            else if (cInARow == winSize) {
                return 'c';
            }
        }
        pInARow = 0;
        cInARow = 0;
        k--;
    }
    
    //Diagonal from bottom left
    k = 0;
    for (int i = 0; i < numOfRows; i++) {
        for (int j = numOfRows - 1; j >= i; j--) {
            if (pBoard[j][j-k] == 'p') {
                pInARow++;
                cInARow = 0;
            }
            else if (pBoard[j][j-k] == 'c') {
                cInARow++;
                pInARow = 0;
            }
            else {
                cInARow = 0;
                pInARow = 0;
            }
            if (pInARow == winSize) {
                return 'p';
            }
            else if (cInARow == winSize) {
                return 'c';
            }
        }
        pInARow = 0;
        cInARow = 0;
        k++;
    }
    
    //Diagonal from bottom right
    for (int i = 0; i < numOfCols; i++) {
        int k = 0;
        for (int j = numOfCols - 1; j > i; j--) {
            if (pBoard[k+i][j] == 'p') {
                pInARow++;
                cInARow = 0;
            }
            else if (pBoard[k+i][j] == 'c') {
                cInARow++;
                pInARow = 0;
            }
            else {
                cInARow = 0;
                pInARow = 0;
            }
            if (pInARow == winSize) {
                return 'p';
            }
            else if (cInARow == winSize) {
                return 'c';
            }
            k++;
        }
        pInARow = 0;
        cInARow = 0;
    }
    
    //Calls a draw
    for (int i = 0; i < numOfCols; i++) {
        if (pBoard[0][i] == 'c' || pBoard[0][i] ==  'p') {
            draw++;
        }
        else {
            draw = 0;
        }
        if (draw == numOfCols) {
            return 't';
        }
    }
    
    return 0;
}

/**
 * @brief Place a piece onto the board
 *
 * @param pBoard The game board
 * @param colSize The column size
 * @param rowSize the row size
 * @param columnSelection The column selection
 * @param player The players character
 *
 * @return True if the piece was placed, else false
 */
bool placePiece(char** pBoard, int numOfCols, int numOfRows, int columnSelection, char player)
{
    // TODO
    //Will place a piece if nothing else is in that spot
    for (int i = numOfRows - 1; i > -1; i--) {
        if (pBoard[i][columnSelection] == ' ') {
            pBoard[i][columnSelection] = player;
            break;
        }
        else if (pBoard[0][columnSelection] != ' ') {
            return false;
        }
    }
    return true;
}

/**
 * @brief Print out the game board
 *
 * @param pBoard The game board
 * @param colSize The column size
 * @param rowSize The row size
 */
void printBoard(char** pBoard, int numOfCols, int numOfRows)
{
    // TODO
    //prints column label
    std::cout << std::endl;
    for (int i = 0; i < numOfCols; i++) {
        std::cout << "|" << i;
    }
    std::cout << "|" << std::endl;
    
    //prints gameboard
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < numOfCols; j++) {
            std::cout << "|" << pBoard[i][j];
        }
        std::cout << "|" << std::endl;
    }
}

int main()
{
    bool running = true;
    printf("Welcome to connect four!\n");
    srand (time(NULL));
    
    int32_t connectedPiecesToWin = 0;
    int32_t numOfRows = 0;
    int32_t numOfCols = 0;
    
    // setup game
    std::cout << "How many connected pieces does it take to win?" << std::endl;
    std::cin >> connectedPiecesToWin;
    
    numOfRows = connectedPiecesToWin + 2;
    numOfCols = connectedPiecesToWin + 3;
    
    std::cout << "You have selected " << connectedPiecesToWin << " in a row with a game board of " << numOfCols
    << " x " << numOfRows << std::endl;
    
    // setup board
    char** pBoard = NULL;
    
    // TODO create the game board
    pBoard = new char *[numOfRows];
    
    for (int i = 0; i < numOfRows; i++) {
        pBoard[i] = new char [numOfCols];
    }
    
    // initialize board
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < numOfCols; j++) {
            pBoard[i][j] = ' ';
        }
    }
    
    // play
    char winner = 0;
    char player = 'p';
    do
    {
        int columnChoice = 0;
        
        do
        {
            if (player == 'p')
            {
                printBoard(pBoard, numOfCols, numOfRows);
                std::cout << "Player's column: ";
                std::cin >> columnChoice;
            }
            else
            {
                // computers turn
                columnChoice = rand() % numOfCols;
            }
        } while (!placePiece(pBoard, numOfCols, numOfRows, columnChoice, player));
        
        winner = checkWinner(pBoard, numOfCols, numOfRows, connectedPiecesToWin);
        player = (player == 'c') ? 'p' : 'c';
    } while (running && winner == 0);
    
    printBoard(pBoard, numOfCols, numOfRows);
    
    if (winner == 't')
    {
        std::cout << "Too bad, the game was a tie!" << std::endl;
    }
    else if (winner == 'c')
    {
        std::cout << "Oh man, you lost to a computer that randomly places pieces!" << std::endl;
    }
    else
    {
        std::cout << "Congrats! You won!" << std::endl;
    }
    
    // cleanup
    // TODO cleanup the board
    for (int i = 0; i < numOfRows; i++) {
        delete pBoard[i];
    }
    
    delete pBoard;
    
    return 0;
}