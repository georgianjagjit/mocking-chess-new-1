#ifndef CHESSUI_H
#define CHESSUI_H

#include "Piece.h"
#include <string>
#include <stdexcept>

class ChessUI {
 public:
    virtual std::string getLocation(Colour side,
        const std::string desc);
    virtual void invalidMove(const std::runtime_error& e);
    virtual void gameOver(Colour side);
};

#endif
