#include <string>
#include "gtest/gtest.h"
#include "Chess.h"
#include "TestEnvironment.h"

class PawnTest : public TestEnvironment {
};

TEST_F(PawnTest, oneSpaceValid) {
    Board board;
    Piece* pawnWhite = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, a1);

    EXPECT_TRUE(board.movePiece(Colour::WHITE, a1, a2));

    Piece* pawnBlack = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, a5);

    EXPECT_TRUE(board.movePiece(Colour::BLACK, a5, a4));
}

TEST_F(PawnTest, backwards) {
    Board board;
    Piece* pawnWhite = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, a2);
    EXPECT_FALSE(board.movePiece(Colour::WHITE, a2, a1));


    Piece* pawnBlack = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, a4);

    EXPECT_FALSE(board.movePiece(Colour::BLACK, a4, a5));
}

TEST_F(PawnTest, twoSpacesValid) {
    Board board;
    Piece* pawnWhite = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, a1);

    EXPECT_TRUE(board.movePiece(Colour::WHITE, a1, a3));

    Piece* pawnBlack = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, b5);

    EXPECT_TRUE(board.movePiece(Colour::BLACK, b5, b3));
}

TEST_F(PawnTest, twoSpacesInvalid) {
    Board board;
    Piece* pawnWhite = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, a2);

    EXPECT_FALSE(board.movePiece(Colour::WHITE, a2, a4));

    Piece* pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, b4);

    EXPECT_FALSE(board.movePiece(Colour::BLACK, b4, b2));
}

TEST_F(PawnTest, sideways) {
    Board board;
    Piece* pawnWhite = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, b2);

    EXPECT_FALSE(board.movePiece(Colour::WHITE, b2, c2));
    EXPECT_FALSE(board.movePiece(Colour::WHITE, b2, a2));
}

TEST_F(PawnTest, enPassantBlack) {
    Board board;

    // A-file
    Piece* pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, a1);

    Piece* pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, b3);

    EXPECT_TRUE(board.movePiece(Colour::WHITE, a1, a3));
    EXPECT_TRUE(board.movePiece(Colour::BLACK, b3, a2));
    EXPECT_EQ(Colour::NONE, board.getPiece(a3)->getSide());

    // C-file
    pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, c1);
    pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, b3);

    EXPECT_TRUE(board.movePiece(Colour::WHITE, c1, c3));
    EXPECT_TRUE(board.movePiece(Colour::BLACK, b3, c2));
    EXPECT_EQ(Colour::NONE, board.getPiece(c3)->getSide());

    // E-file
    pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, e1);
    pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, d3);

    EXPECT_TRUE(board.movePiece(Colour::WHITE, e1, e3));
    EXPECT_TRUE(board.movePiece(Colour::BLACK, d3, e2));
    EXPECT_EQ(Colour::NONE, board.getPiece(e3)->getSide());
}

TEST_F(PawnTest, enPassantWhite) {
    Board board;

    // A-file
    Piece* pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, b3);

    Piece* pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, a5);

    EXPECT_TRUE(board.movePiece(Colour::BLACK, a5, a3));
    EXPECT_TRUE(board.movePiece(Colour::WHITE, b3, a4));
    EXPECT_EQ(Colour::NONE, board.getPiece(a3)->getSide());

    // C-file
    pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, b3);
    pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, c5);

    EXPECT_TRUE(board.movePiece(Colour::BLACK, c5, c3));
    EXPECT_TRUE(board.movePiece(Colour::WHITE, b3, c4));
    EXPECT_EQ(Colour::NONE, board.getPiece(c3)->getSide());

    // E-file
    pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, d3);
    pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, e5);

    EXPECT_TRUE(board.movePiece(Colour::BLACK, e5, e3));
    EXPECT_TRUE(board.movePiece(Colour::WHITE, d3, e4));
    EXPECT_EQ(Colour::NONE, board.getPiece(e3)->getSide());
}

TEST_F(PawnTest, enPassantFail) {
    Board board;

    // White pawn already moved
    Piece* pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, e2);

    Piece* pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, d3);

    EXPECT_TRUE(board.movePiece(Colour::WHITE, e2, e3));
    EXPECT_FALSE(board.movePiece(Colour::BLACK, d3, e2));
    Piece* pawn = dynamic_cast<Pawn*>(board.getPiece(e3));
    EXPECT_TRUE(pawn != nullptr);
    EXPECT_EQ(Colour::WHITE, board.getPiece(e3)->getSide());

    // Black pawn already moved
    pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, b3);
    pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, c4);

    EXPECT_TRUE(board.movePiece(Colour::BLACK, c4, c3));
    EXPECT_FALSE(board.movePiece(Colour::WHITE, b3,
                                c4));
    pawn = dynamic_cast<Pawn*>(board.getPiece(c3));
    EXPECT_TRUE(pawn != nullptr);
    EXPECT_EQ(Colour::BLACK, board.getPiece(c3)->getSide());
}

TEST_F(PawnTest, noForward) {
    Board board;

    Piece* pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, c3);

    Piece* pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, c4);

    EXPECT_FALSE(board.movePiece(Colour::WHITE, c3,
                                c4));
    EXPECT_FALSE(board.movePiece(Colour::BLACK, c4,
                                c3));
}

TEST_F(PawnTest, takePieceWhite) {
    Board board;

    Piece* pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, a2);

    // Pawn
    pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, a2);
    Piece* pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, b3);
    EXPECT_TRUE(board.movePiece(Colour::WHITE, a2,
                               b3));
    Pawn* pawn = dynamic_cast<Pawn*>(board.getPiece(b3));
    EXPECT_TRUE(pawn != nullptr);
    EXPECT_EQ(Colour::WHITE, board.getPiece(b3)->getSide());
}


TEST_F(PawnTest, takePieceBlack) {
    Board board;

    Piece* pawnBlack  = new Pawn(Colour::BLACK);
    board.placePiece(pawnBlack, a5);

    Piece* pawnWhite  = new Pawn(Colour::WHITE);
    board.placePiece(pawnWhite, b4);

    EXPECT_TRUE(board.movePiece(Colour::BLACK, a5,
                               b4));
    Piece* pawn = dynamic_cast<Pawn*>(board.getPiece(b4));
    EXPECT_TRUE(pawn != nullptr);

    EXPECT_EQ(Colour::BLACK, board.getPiece(b4)->getSide());
}
