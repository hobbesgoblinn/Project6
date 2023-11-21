#pragma once
#include<vector>
#include "Board.h"
class Player{
public:
	struct move {
		Board board;
		move* next = nullptr;
	};
	Player(char piece = '?');
	~Player();
	void PrintMoves();
	void CopyBoard(const char board[]);
	void AddMove(const char board[]);
private:
	char piece;
	move* moveListHead;
	move* latestMove;
};

