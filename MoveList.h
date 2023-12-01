#pragma once
#include "Board.h"
class Move {
public:
	Move();
	Move(const Board& toCopy);
	void SetNextMove(Move* newLink) { nextMove = newLink; }
	Move* GetNextMove() { return nextMove; }
	Board GetBoard() { return board; }
	void PrintBoard() { board.Print(); }
private:
	Board board;
	Move* nextMove;
};
class MoveList {
public:
	MoveList();
	~MoveList();
	int GetNumMoves() { return numMoves; }
	Move* GetMoveListHead() { return moveListHead; }
	Move* GetLatestMove() { return latestMove; }
	void AddMove(const Board& board);
	void RemoveLastMove();
private:
	int numMoves;
	Move* moveListHead;
	Move* latestMove;
};

