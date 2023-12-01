#include "MoveList.h"
Move::Move() {
	nextMove = nullptr;
}
Move::Move(const Board& toCopy) {
	board.CopyBoard(toCopy);
	nextMove = nullptr;
}
MoveList::MoveList() {
	numMoves = 0;
	moveListHead = nullptr;
	latestMove = nullptr;
}
MoveList::~MoveList() {
	Move* currMove;
	while (moveListHead != nullptr) {
		currMove = moveListHead;
		moveListHead = moveListHead->GetNextMove();
		delete currMove;
	}
}
// ADDMOVE
// Recieves game board
// Copies board into a new move and adds move to move list
void MoveList::AddMove(const Board& toCopy) {
	Move* newMove = new Move(toCopy);

	// Checks whether new move is the first move and adds it to list accordingly
	if (latestMove != nullptr) {
		latestMove->SetNextMove(newMove);
	}
	else {
		moveListHead = newMove;
	}
	latestMove = newMove;
	numMoves++;
}
// REMOVELASTMOVE
// Removes last move from move list
void MoveList::RemoveLastMove() {
	Move* currMove = moveListHead;

	if (numMoves == 0) { return; }

	if (numMoves == 1) {
		moveListHead = nullptr;
		latestMove = nullptr;
		delete currMove;
	}
	else {
		// Finds second to last move in list
		while (currMove->GetNextMove() != latestMove) {
			currMove = currMove->GetNextMove();
		}
		// Deletes old last move and makes currMove the new last
		delete latestMove;
		latestMove = currMove;
		latestMove->SetNextMove(nullptr);
	}
	numMoves--;
}

