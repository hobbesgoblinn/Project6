#include "Player.h"
using namespace std;
Player::Player(char piece) {
	this->piece = piece;
}
// UNDOMOVE
// Recieves game board and player whose move will be undone
// Calls RemoveLastMove and then updates the board
// Returns true if there was a move to undo
bool Player::UndoMove(Board& board, Player*& toUndo) {
	bool moveUndone = false;
	Board blank;

	if (toUndo->GetNumMoves() > 0) {
		toUndo->moves.RemoveLastMove();
		moveUndone = true;
		// Clears board if move to be undone was the only move left
		if (GetNumMoves() < 1) {
			board.CopyBoard(blank);
		}
		// Otherwise copies the last move made by the undoing player to the board
		else {
			board.CopyBoard(GetLatestMove()->GetBoard());
		}
	}
	board.Print();
	return moveUndone;
}
// PRINTALLMOVES
// Called from first player, recieves reference to second player
// Prints all moves in sequential order
void Player::PrintAllMoves(Player& secondPlayer) {
	Move* currMove1 = moves.GetMoveListHead();
	Move* currMove2 = secondPlayer.GetMoveListHead();
	int maxMoveNum = (GetNumMoves() > secondPlayer.GetNumMoves()) ? GetNumMoves() : secondPlayer.GetNumMoves();
	for (int i = 0; i < maxMoveNum; i++) {
		// Prints moves until the ends of both lists have been reached
		if (currMove1 != nullptr) {
			currMove1->PrintBoard();
			currMove1 = currMove1->GetNextMove();
		}
		if (currMove2 != nullptr) {
			currMove2->PrintBoard();
			currMove2 = currMove2->GetNextMove();
		}
	}
}