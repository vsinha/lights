#include "Arduino.h"

#include "life.h"

namespace GOL {

bool board1 [GOL_ROWS][GOL_COLS];
bool board2 [GOL_ROWS][GOL_COLS];

// bool (*currBoard)[GOL_ROWS][GOL_COLS];
// bool (*prevBoard)[GOL_ROWS][GOL_COLS];

// set every element in the array to false
void clear(bool (*arr)[GOL_ROWS][GOL_COLS]) {
    for (int i = 0; i < GOL_ROWS; i++) {
        for (int j = 0; j < GOL_COLS; j++) {
            (*arr)[i][j] = false;
        }
    }
}

void randomize(bool (*arr)[GOL_ROWS][GOL_COLS]) {
    for(int j = 0; j < GOL_ROWS; j++) {
        for (int i = 0; i < GOL_COLS; i++) {
            (*arr)[j][i] = (bool)(random(2));
        }
    }
}

void initialize() {
    currBoard = &board1;
    prevBoard = &board2;

    clear(currBoard);
    randomize(prevBoard);

}

bool checkNeighborhood(bool (*arr)[GOL_ROWS][GOL_COLS], int j, int i) {
    auto array = *arr;
    int count = array[j-1][i] +
        array[j-1][i-1] +
        array[j][i-1] +
        array[j+1][i-1] +
        array[j+1][i] +
        array[j+1][i+1] +
        array[j][i+1] +
        array[j-1][i+1];

    //The cell dies.
    if(count < 2 || count > 3)
        return 0;

    //The cell stays the same.
    if(count == 2)
        return array[j][i];

    //The cell either stays alive, or is "born".
    if(count == 3)
        return 1;

    return 0;
}

bool (*update())[GOL_ROWS][GOL_COLS] {
    for (int i = 0; i < GOL_ROWS; i++) {
        for (int j = 0; j < GOL_COLS; j++) {
            (*currBoard)[i][j] = checkNeighborhood(prevBoard, i, j);
        }
    }

    // swap the arrays
    auto tmp = prevBoard;
    prevBoard = currBoard;
    currBoard = tmp;
    clear(currBoard);

    return prevBoard;
}

} // namespace
