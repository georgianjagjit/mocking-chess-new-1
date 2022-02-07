#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <string>
#include "Exceptions.h"
#include "Coordinate.h"
#include "Board.h"
#include "ChessUI.h"


class Chess {
 public:
    Chess(ChessUI* ui, Board* b);
    virtual ~Chess();

    /**
    * Place the pieces in their starting positions on the board.
    */
    void setup();

    /**
    * Start the game.
    */
    void playGame();

    Board* getBoard() {
        return board;
    }

 private:
    const unsigned int BOARD_SIZE = 5;
    Board* board;
    ChessUI* ui;
};
#endif // CHESS_H
