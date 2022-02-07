#ifndef CHESS_TEST_H_INCLUDED
#define CHESS_TEST_HINCLUDED

#include <string>
#include <vector>
#include "gmock/gmock.h"
#include "Chess.h"
#include "ChessUI.h"
#include "Pawn.h"

using ::testing::Expectation;
using ::testing::Return;
using ::testing::_;

class mBoard: public Board {
 public:
  explicit mBoard(unsigned int size):Board(size) {}
  virtual ~mBoard() {}
  MOCK_METHOD3(movePiece, bool(Colour, Coordinate, Coordinate));
  MOCK_METHOD2(placePiece, void(Piece*, Coordinate*));
  MOCK_METHOD1(emptySpace, void(Coordinate*));
  MOCK_METHOD1(getPiece, Piece*(Coordinate*));
  MOCK_METHOD1(isWinner, bool(Colour));
  MOCK_METHOD0(draw, void());
  MOCK_METHOD0(getBoard, std::vector<std::vector<Piece*>>*());
};

class mui: public ChessUI {
 public:
  explicit mui() {}
  virtual ~mui() {}
  MOCK_METHOD2(getLocation, std::string(Colour, std::string));
  MOCK_METHOD1(invalidMove, void(const std::runtime_error&));
  MOCK_METHOD1(gameOver, void(Colour));
};

TEST(chessTest, setupTest) {
  mui interface;
  mBoard boardModel(5);
  EXPECT_CALL(boardModel, placePiece(_, _))
  .Times(10);
  Chess* Game = new Chess(&interface, &boardModel);
  Game->setup();
  delete Game;
}
#endif
