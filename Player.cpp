#include "Player.h"
using namespace std;
Player::Player(char piece) {
	this->piece = piece;
	moveListHead = nullptr;
	latestMove = nullptr;
}
Player::~Player() {
	move* currMove;
	while (moveListHead != nullptr) {
		currMove = moveListHead;
		moveListHead = moveListHead->next;
		delete currMove;
	}
}
void Player::AddMove(const char toCopy[]) {
	move* newMove = new move;
	newMove->board.CopyBoard(toCopy);
	if (latestMove != nullptr) {
		latestMove->next = newMove;
	}
	else {
		moveListHead = newMove;
	}
	latestMove = newMove;
}
void Player::PrintMoves() {
	move* currMove;
	currMove = moveListHead;
	while (currMove != nullptr) {
		currMove->board.Print();
		currMove = currMove->next;
	}
}