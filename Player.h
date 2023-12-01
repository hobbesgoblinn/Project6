#pragma once
#include<vector>
#include "MoveList.h"
class Player{
public:
	Player(char piece = '?');
	char GetPiece() { return piece; }
	int GetNumMoves() { return moves.GetNumMoves(); }
	Move* GetMoveListHead() { return moves.GetMoveListHead(); }
	Move* GetLatestMove() { return moves.GetLatestMove(); }
	void AddMove(const Board& board) { moves.AddMove(board); }
	bool UndoMove(Board& board, Player*& toUndo);
	void PrintAllMoves(Player& secondPlayer);
private:
	char piece;
	MoveList moves;
};