#define GOL_ROWS 200
#define GOL_COLS 200

#include "Arduino.h"

class Board {
public:
    void initialize() {
        for (int i =0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                m_grid[i][j] = false;
            }
        }
    }

    void set(int x, int y, bool val) {
        if (!valid(x, y)) return;
        m_grid[x][y] = val;
    }

    bool get(int x, int y) const {
        if (!valid(x, y)) return false;
        return m_grid[x][y];
    }

    int toRange(int val) const {
        val %= m_size;
        if (val < 0) val += m_size;
        return val;
    }

    int getModulus(int x, int y) const {
        return get(toRange(x), toRange(y));
    }

    int size() const {
        return m_size;
    }

    bool operator==(const Board & rhs) {
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < rhs.size(); j++) {
                if (get(i, j) != rhs.get(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

private:
    static const int m_size = 150;
    bool m_grid[m_size][m_size];

    bool valid(int x, int y) const {
        return (x < m_size && y < m_size);
    }
};


class GameOfLife {
public:

    void init() {
        randomize(boardeven);
        even = true;
    }

    void update() {
        if(even) {
            next(boardeven, boardodd);
        } else {
            next(boardodd, boardeven);
        }

        even = !even;

        if(boardeven == boardodd) {
            delay(1000);
            randomize(boardeven);
            even = true;
        }
    }

    Board getCurrentBoard() {
        return even ? boardeven : boardodd;
    }

private:
    Board boardeven;
    Board boardodd;
    bool even = true;

    void next(const Board & src, Board & dest) {
        for(int y = 0; y < src.size(); y++) {
            for(int x = 0; x < src.size(); x++) {
                int neighbors = src.getModulus(x - 1, y + 1)
                + src.getModulus(x, y + 1)
                + src.getModulus(x + 1, y + 1)
                + src.getModulus(x - 1, y)
                + src.getModulus(x + 1, y)
                + src.getModulus(x - 1, y - 1)
                + src.getModulus(x, y - 1)
                + src.getModulus(x + 1, y - 1);

                bool live = true;

                if(src.get(x, y)) {
                    if(neighbors < 2 || 3 < neighbors) {
                        live = false;
                    }
                } else {
                    if(neighbors != 3) {
                        live = false;
                    }
                }

                dest.set(x, y, live);
            }
        }
    }

    void randomize(Board & board) {
        for(int y = 0; y < board.size(); y++) {
            for(int x = 0; x < board.size(); x++) {
                board.set(x, y, random(2));
            }
        }
    }
};
