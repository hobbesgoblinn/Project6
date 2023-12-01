#include "Board.h"
// COPYBOARD
// Recieves another board
// Copies contents of other board
void Board::CopyBoard(const Board& toCopy) {
    for (int i = 0; i < size; i++) {
        data[i] = toCopy.data[i];
    }
}
// PRINT
// Displays board
void Board::Print() {
    cout << "\t0 1 2 3 4 5 6 \n";
    for (int i = 0; i < size; i++) {
        if ((i % width) == 0) {
            cout << "\t";
        }
        cout << data[i] << " ";
        // Newline at the end of row
        if ((i % width) == (width - 1)) {
            cout << "\n";
        } 
    }
    cout << endl;
}