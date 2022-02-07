#include <string>
#include "gtest/gtest.h"
#include "Chess.h"
#include "TestEnvironment.h"

class Game : public TestEnvironment {
};


TEST_F(Game, over) {
    std::string moves[] = {
        "A1", "A3", "B5", "B3", "A3", "B4", "A5", "B4",
        "B1", "B3", "C5", "C3", "B3", "C4", "D5", "C4",
        "C1", "C3", "B4", "C3", "D1", "D3", "C4", "D3",
        "E1", "E3", "D3", "E2"
                          };
    Chess game(ui, board);
    game.setup();
    Board* board = game.getBoard();

    Colour player = Colour::WHITE;
    unsigned int move = 0;
    do {
        Coordinate* start = new Coordinate(moves[move]);
        Coordinate* end = new Coordinate(moves[move+1]);

        EXPECT_TRUE(board->movePiece(player, start, end));
        player = (player == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
        move += 2;

        delete start;
        delete end;
    } while (move/2 < 14);

    EXPECT_TRUE(board->isWinner(Colour::BLACK));
}
