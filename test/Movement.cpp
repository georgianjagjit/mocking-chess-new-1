#include <string>
#include "gtest/gtest.h"
#include "Chess.h"
#include "TestEnvironment.h"

class Movement : public TestEnvironment {
};

TEST_F(Movement, emptySpace) {
    Board board;

    EXPECT_THROW(board.movePiece(Colour::WHITE, c2,
                                 c3), no_piece_error);
}

TEST_F(Movement, initialSetupWhite) {
    Chess game(ui, board);
    game.setup();
    Board* board = game.getBoard();

    Colour colour = Colour::WHITE;

    for (int i = 0; i < 5; ++i) {
        char column = 'A' + i;
        std::string s(1, column);
        s.append("1");
        Coordinate* c = new Coordinate(s);
        Piece* pawn = dynamic_cast<Pawn*>(board->getPiece(c));
        EXPECT_TRUE(nullptr != pawn);
        if (pawn != nullptr) {
            EXPECT_EQ(colour, pawn->getSide());
        }
        delete c;
    }
}

TEST_F(Movement, initialSetupBlack) {
    Chess game(ui, board);
    game.setup();
    Board* board = game.getBoard();

    Colour colour = Colour::BLACK;

    for (int i = 0; i < 5; ++i) {
        char column = 'A' + i;
        std::string s(1, column);
        s.append("5");
        Coordinate* c = new Coordinate(s);
        Piece* pawn = dynamic_cast<Pawn*>(board->getPiece(c));
        EXPECT_TRUE(nullptr != pawn);
        if (pawn != nullptr) {
            EXPECT_EQ(colour, pawn->getSide());
        }
        delete c;
    }
}

TEST_F(Movement, notPlayers) {
    Board board;
    Piece* pawn = new Pawn(Colour::WHITE);
    board.placePiece(pawn, e2);

    EXPECT_THROW(board.movePiece(Colour::BLACK, e2, e3), invalid_piece_error);
}

TEST_F(Movement, offBoard) {
    Board board;
    Coordinate* rank = new Coordinate("I2");
    Coordinate* file = new Coordinate("A9");
    Piece* p = new Pawn(Colour::BLACK);
    EXPECT_THROW(board.placePiece(p, rank),
      invalid_location_error);
    EXPECT_THROW(board.placePiece(p, file),
      invalid_location_error);
    EXPECT_THROW(board.movePiece(Colour::BLACK, rank, a1),
      invalid_location_error);
    EXPECT_THROW(board.movePiece(Colour::BLACK, file, a1),
      invalid_location_error);
    delete rank;
    delete file;
    delete p;
}

TEST_F(Movement, illegalCoordiante) {
    EXPECT_THROW(new Coordinate("A12"), invalid_location_error);
}
