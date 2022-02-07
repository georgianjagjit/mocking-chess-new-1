CXX = g++
CXXFLAGS = -std=c++11 -g -fprofile-arcs -ftest-coverage

LINKFLAGS = -lgtest -lpthread -lgmock

TEST_DIR = test

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

SRC_DIR = src

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint.py

PROGRAM = chess
PROGRAM_TEST = testChess

DOCS_DIR = docs

.PHONY: all
all: $(PROGRAM_TEST) memcheck static style

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *~ *.o $(SRC)/*.o $(TEST_SRC)/*.o \
	$(PROGRAM_TEST) $(PROGRAM) \
	$(DOCS_DIR) obj bin *.gc* .objs \
	$(COVERAGE_RESULTS) $(COVERAGE_DIR)

$(PROGRAM): $(SRC_DIR) $(SRC_DIR)/game/main.cpp
		$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(INCLUDE) \
		$(SRC_DIR)/*.cpp $(SRC_DIR)/game/main.cpp


$(PROGRAM_TEST): Pawn.o Chess.o Board.o ChessUI.o\
		Piece.o Coordinate.o \
		testMain.o testGame.o testChess.o\
		testPawn.o testMovement.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) \
		testMain.o ChessUI.o testGame.o testChess.o\
		testPawn.o testMovement.o \
		Chess.o Board.o Pawn.o Piece.o  \
		Coordinate.o \
		$(LINKFLAGS)

Pawn.o: $(SRC_DIR)/Pawn.cpp $(SRC_INCLUDE)/Pawn.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Pawn.cpp -o Pawn.o -I $(SRC_INCLUDE)

Chess.o: $(SRC_DIR)/Chess.cpp $(SRC_INCLUDE)/Chess.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Chess.cpp -o Chess.o -I $(SRC_INCLUDE)

Board.o: $(SRC_DIR)/Board.cpp $(SRC_INCLUDE)/Board.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Board.cpp -o Board.o -I $(SRC_INCLUDE)

Piece.o: $(SRC_DIR)/Piece.cpp $(SRC_INCLUDE)/Piece.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Piece.cpp -o Piece.o -I $(SRC_INCLUDE)

Coordinate.o: $(SRC_DIR)/Coordinate.cpp $(SRC_INCLUDE)/Coordinate.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Coordinate.cpp -o Coordinate.o -I $(SRC_INCLUDE)

ChessUI.o: $(SRC_DIR)/ChessUI.cpp $(SRC_INCLUDE)/ChessUI.h
		$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/ChessUI.cpp -o ChessUI.o -I $(SRC_INCLUDE)

testMain.o: $(TEST_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/main.cpp -o testMain.o -I $(SRC_INCLUDE)

testPawn.o: $(TEST_DIR)/Pawn.cpp
		$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/Pawn.cpp -o testPawn.o -I $(SRC_INCLUDE)

testMovement.o: $(TEST_DIR)/Movement.cpp
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/Movement.cpp -o testMovement.o -I $(SRC_INCLUDE)

testChess.o: $(TEST_DIR)/Chess.cpp
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/Chess.cpp -o testChess.o -I $(SRC_INCLUDE)

testGame.o: $(TEST_DIR)/Game.cpp
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/Game.cpp -o testGame.o -I $(SRC_INCLUDE)


tests: $(PROGRAM_TEST)
	$(PROGRAM_TEST)

memcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST) --error-exitcode=1

style: ${TEST_DIR} ${SRC_INCLUDE}
	${STYLE_CHECK} $(SRC_INCLUDE)/* ${TEST_DIR}/* --error-exitcode=1
