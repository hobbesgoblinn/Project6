/******************************************************************************
This program allows two players to compete in a game of Connect Four, with the
added ability to undo each other's moves and display all previous moves made.
Author: Michelle Perez
December 1, 2023
System: Microsoft Visual Studio 2022
*******************************************************************************/
#include <iostream>
#include "Player.h"
using namespace std;
void PlayGame(Board& board);
int InputMove(Board& board, Player*& player);
void SwapPlayers(Player*& player, Player*& otherPlayer);
int MakeMove(Board& board, const int column, Player* player);
bool BoardFull(const Board& board);
bool CheckWin(const Board& board, Player* player, int index);
int SearchDirection(const Board& board, int direction, int index);
int main()
{
    cout << "This is the Game Connect 4.\n"
        << "Each player should place an X or an O in the space \n"
        << "by entering the column you want to place the piece.\n"
        << "The piece will fall until it reaches the bottom or \n"
        << "the current pieces in the board. When X or O gets 4 in \n"
        << "a row (either horizontally, vertically, or diagonally, \n"
        << "then that person wins. The user can enter U (or u) to \n"
        << "undo the last move, or Q (or q) to end the game early.\n"
        << "Let's get started!!! \n";

    Board board;
    board.Print();
    PlayGame(board);

    return 0;
}
// PLAYGAME
// Recieves board
// Swaps between players until 'q'/'Q' is entered, a player wins, or the  board is filled
void PlayGame(Board& board) {
    int column;
    Player X('X');
    Player O('O');
    Player* currPlayer = &X;
    Player* otherPlayer = &O;
    int moveIndex = 0;

    column = InputMove(board, currPlayer);
    // InputMove returns either a valid column, 
    // or -3 if 'Q' is input, -2 for 'U', and -1 for 'P'
    while (column > -3) {
        if (column > -1) {
            moveIndex = MakeMove(board, column, currPlayer);
            // Exits if player won or board is full
            if (CheckWin(board, currPlayer, moveIndex) || BoardFull(board)) { break; }
            SwapPlayers(currPlayer, otherPlayer);
        }
        else if (column == -1) {
            X.PrintAllMoves(O);
        }
        else {
            if (currPlayer->UndoMove(board, otherPlayer)) {
                SwapPlayers(currPlayer, otherPlayer);
            }
        }
        column = InputMove(board, currPlayer);
    }
}
// SWAPPLAYERS
// Recieves pointers to players and swaps addresses
void SwapPlayers(Player*& player, Player*& otherPlayer) {
    Player* temp = player;
    player = otherPlayer;
    otherPlayer = temp;
}
// INPUTMOVE
// Recieves board and current player
// Prompts for input until a valid column is entered or player enters 'Q', 'U', or 'P'.
// Returns integer: valid column, or negative number depending on choice:
// -3 if 'Q', -2 if 'U', or -1 if 'P'
int InputMove(Board& board, Player*& player) {
    char input;
    int column;

    cout << "It is " << player->GetPiece() << "'s turn.\n"
        << "Enter a column to place your piece. \n";
    cin >> input;

    while (toupper(input) != 'Q') {
        // Print
        if (toupper(input) == 'P') {
            return -1;
        }
        // Undo
        if (toupper(input) == 'U') {
            return -2;
        }
        // Valid column
        if ((atoi(&input) >= 0) && (atoi(&input) < board.width)) {
            column = atoi(&input);

            if (board.data[column] == '-') {
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
    return -3;
}
// MAKEMOVE
// Recieves board, column, and player
// Updates board and player's move list, then prints board
// Returns index of move to check for win later
int MakeMove(Board& board, const int column, Player* player) {
    int moveIndex = column;
    int currIndex;

    for (int i = 0; i < board.height; i++) {
        // Finds lowest available spot
        currIndex = column + (i * board.width);
        if (board.data[currIndex] == '-') {
            moveIndex = currIndex;
        }
        else { break; }
    }
    board.data[moveIndex] = player->GetPiece();
    player->AddMove(board);
    board.Print();
    return moveIndex;
}
// BOARDFULL
// Recieves board
// Returns true if the uppermost row is full
bool BoardFull(const Board& board) {
    for (int i = 0; i < board.width; i++) {
        // Returns false if any of the spots in the top row are open
        if (board.data[i] == '-') {
            return false;
        }
    }
    cout << "Board is Full, It's a Draw!!!\n";
    return true;
}
// CHECKWIN
// Recieves board, current player, and index of last move
// Searches each direction starting from last move for the number of matches
// Checks whether there are 4 in a row in any orientation
bool CheckWin(const Board& board, Player* player, int index) {
    int width = board.width;
    // L horizontal, L up diagonal, up vertical, R up diagonal
    // R horizontal, R down diagonal, down vertical, L down diagonal
    const int direction[8] = {-1, -width - 1, -width, -width + 1, 1, width + 1, width, width - 1};
    int count[8];
    // Count starts at one to include current piece
    int horizontal = 1, vertical = 1, rDiag = 1, lDiag = 1;

    for (int i = 0; i < 8; i++) {
        // Gets count of matching pieces in direction i
        count[i] = SearchDirection(board, direction[i], index);
    }

    horizontal += count[0] + count[4];
    // lDiag: Upper left to lower right
    lDiag += count[1] + count[5];
    vertical += count[2] + count[6];
    // rDiag: Upper right to lower left
    rDiag += count[3] + count[7];

    if ((horizontal >= 4) || (vertical >= 4) || (lDiag >= 4) || (rDiag >= 4)) {
        cout << "Game is Over, Player " << player->GetPiece() << " got 4 in a row!!!!\n";
        return true;
    }

    return false;
}
// SEARCHDIRECTION
// Recieves board, direction, and index
// Returns the count of matching pieces in the direction
int SearchDirection(const Board& board, int direction, int index) {
    int nextIndex = index + direction;
    int col = index % board.width;
    int nextCol = nextIndex % board.width;

    // If next index is off board or not in a contiguous column, return 0
    if ((nextIndex >= board.size) || (nextIndex < 0) || (abs(col - nextCol) > 1)) {
        return 0;
    }
    // If next index doesn't match, return 0
    if (board.data[index] != board.data[nextIndex]) {
        return 0;
    }
    else {
        // Recursively adds 1 for each new match
        return 1 + SearchDirection(board, direction, nextIndex);
    }
}