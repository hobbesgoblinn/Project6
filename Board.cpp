#include "Board.h"
void Board::CopyBoard(const char toCopy[]) {
    for (int i = 0; i < 42; i++) {
        data[i] = toCopy[i];
    }
}
void Board::Print() {
    cout << "0 1 2 3 4 5 6 " << endl;
    for (int i = 0; i < 42; i++) {
        cout << data[i] << " ";
        // When the board array reaches a border, endl is printed
        if ((i % 7) == (7 - 1)) {
            cout << endl;
        }
    }
}