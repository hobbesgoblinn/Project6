/******************************************************************************
This program allows two players to compete in a game of Connect Four.
Author: Michelle Perez
November 17, 2023
System: Microsoft Visual Studio 2022
*******************************************************************************/
#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"
using namespace std;
const int BOARD_SIZE = 42;
const int WIDTH = 7;
const int HEIGHT = 6;
struct player {
    char piece;
    player(char playPiece = '?') { piece = playPiece; }
    vector<int> moves;
    int latestIndex = 0;
};
void DisplayBoard(const char board[]);
void PlayGame(char board[]);
int InputMove(const char board[], player* player);
int NextMoveIndex(const char board[], const int column);
void MakeMove(char board[], const int column, player* player);
bool BoardFull(const char board[]);
bool CheckWin(const char board[], player* player);
bool CheckBoard(const char board[], player* player);
int SearchDirection(const char board[], int direction, int index);
int main()
{
    char board[BOARD_SIZE] =
    {//  0   1   2   3   4   5   6  << COLUMNS
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','r','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-' };
    cout << "This is the Game Connect 4.\n"
        << "Each player should place an X or an O in the space \n"
        << "by entering the column you want to place the piece.\n"
        << "The piece will fall until it reaches the bottom or \n"
        << "the current pieces in the board. When X or O gets 4 in \n"
        << "a row (either horizontally, vertically, or diagonally, \n"
        << "then that person wins. The user can enter Q (or q) to \n"
        << "end the game early.\n"
        << "Let's get started!!! \n";
    // Board is displayed and the game begins
    Board newBoard;
    
    DisplayBoard(board);
    PlayGame(board);

    return 0;
}
// DISPLAYBOARD
// Recieves board array
// Prints each character in the board array
void DisplayBoard(const char board[]) {
    cout << "0 1 2 3 4 5 6 " << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << board[i] << " ";
        // When the board array reaches a border, endl is printed
        if ((i % WIDTH) == (WIDTH - 1)) {
            cout << endl;
        }
    }
}
// PLAYGAME
// Recieves board array
// Swaps between players until 'q'/'Q' is entered, a player wins, or the  board is filled
void PlayGame(char board[]) {
    int column;
    player playerX('X');
    player playerO('O');
    player* currPlayer = &playerX;

    column = InputMove(board, currPlayer);
    // InputMove returns -1 if 'q'/'Q' is input
    while (column > -1) {
        MakeMove(board, column, currPlayer);
        DisplayBoard(board);
        // Breaks out of loop if a player wins or the board is filled
        if (CheckWin(board, currPlayer)) { break; }
        if (BoardFull(board)) { break; }
        // Switching player
        currPlayer = (currPlayer->piece == 'X') ? &playerO : &playerX;
        column = InputMove(board, currPlayer);
    }
}
// INPUTMOVE
// Recieves board array and current player
// Returns integer: column number, or -1 if player quits game
// This function allows the user to input a char, and checks its validity. 
// Keeps prompting for input until it is valid or player quits game.
int InputMove(const char board[], player* player) {
    char input;
    int column;

    cout << "It is " << player->piece << "'s turn.\n"
        << "Enter a column to place your piece. \n";
    cin >> input;

    while (toupper(input) != 'Q') {
        // If input is a valid column
        if ((input >= '0') && (input < (WIDTH + '0'))) {
            column = input - '0';

            if (board[column] == '-') {
                // Add column to moves vector if column is not full
                player->moves.push_back(column);
                return column;
            }
            cout << "column chosen is already full\n";
        }
        else {
            cout << "Please enter a valid column\n";
        }
        cin >> input;
    }
    cout << "Ending Game\n";
    return -1;
}
// NEXTMOVEINDEX
// Recieves board array and column
// Returns index of next move
int NextMoveIndex(const char board[], const int column) {
    int currIndex;
    int moveIndex = -1;

    for (int i = 0; i < HEIGHT; i++) {
        // Checks column at row i
        currIndex = column + (i * WIDTH);
        if (board[currIndex] == '-') {
            moveIndex = currIndex;
        }
        // Breaks if spot is filled
        else { break; }
    }

    return moveIndex;
}
// MAKEMOVE
// Recieves board array, column, and player
// Finds index of move and uses it to update the board and the player's move board
void MakeMove(char board[], const int column, player* player) {
    int index;
    if (column >= 0) {
        index = NextMoveIndex(board, column);
        board[index] = player->piece;
        player->latestIndex = index;
    }
}
// BOARDFULL
// Recieves board array
// Returns full if the uppermost row is full
bool BoardFull(const char board[]) {
    bool full = true;
    for (int i = 0; i < WIDTH; i++) {
        // Checks if any of the spots in the top row are open
        if (board[i] == '-') {
            full = false;
        }
    }
    if (full) {
        cout << "Board is Full, It's a Draw!!!\n";
    }
    return full;
}
// CHECKWIN
// Recieves board array and player
// Checks whether player has won, returns bool
bool CheckWin(const char board[], player* player) {
    bool win = false;
    // Checks board if player has input enough moves
    if (player->moves.size() >= 4) {
        win = CheckBoard(board, player);
    }
    if (win) {
        cout << "Game is Over, Player " << player->piece << " got 4 in a row!!!!\n";
    }
    return win;
}
// CHECKBOARD
// Recieves board array and player, returns bool
// Searches each direction starting from last piece placed for the number of matching pieces
// and then checks whether there are 4 in a row
bool CheckBoard(const char board[], player* player) {
    const int xMvmt[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    const int yMvmt[8] = { 0, -WIDTH, -WIDTH, -WIDTH, 0, WIDTH, WIDTH, WIDTH };
    int count[8];
    int moveDir;
    // Count starts at one to include current piece
    int horizontal = 1, vertical = 1, rDiag = 1, lDiag = 1;

    for (int i = 0; i < 8; i++) {
        // Amount to add to current index to get next index in direction i
        moveDir = xMvmt[i] + yMvmt[i];
        // Gets count of matching pieces in direction i
        count[i] = SearchDirection(board, moveDir, player->latestIndex);
    }
    horizontal += count[0] + count[4];
    lDiag += count[1] + count[5];
    vertical += count[2] + count[6];
    rDiag += count[3] + count[7];
    // If there is a line of 4 in any orientation, returns true
    if ((horizontal >= 4) || (vertical >= 4) || (lDiag >= 4) || (rDiag >= 4)) {
        return true;
    }

    return false;

}
// SEARCHDIRECTION
// Recieves board array, direction, and index
// Returns count
// Counts the number of matching pieces in a particular direction
int SearchDirection(const char board[], int direction, int index) {
    int nextIndex = index + direction;
    int col = index % WIDTH;
    int nextCol = nextIndex % WIDTH;

    // If next index is off board or not in a contiguous column, return 0
    if ((nextIndex >= BOARD_SIZE) || (nextIndex < 0) || (abs(col - nextCol) > 1)) {
        return 0;
    }

    // If next index doesn't match, return 0
    if (board[index] != board[nextIndex]) {
        return 0;
    }
    else {
        // Recursively calls itself, adding 1 for each new match
        return 1 + SearchDirection(board, direction, nextIndex);
    }
}


