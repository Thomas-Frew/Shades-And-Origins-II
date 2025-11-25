#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(SimpleGameTest, RaceToTheEnd) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(2, 0)));

    simpleGame.getBoard().printBoard();
    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, CheatersLeague) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Position(3, 3)));
    EXPECT_TRUE(simpleGame.makeMove(Position(2, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(2, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Position(2, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Position(2, 1)));

    simpleGame.getBoard().printBoard();
    EXPECT_EQ(simpleGame.getWinnerIdentity(), ORIGIN);
}

TEST(SimpleGameTest, Diagonal) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Position(2, 2)));

    simpleGame.getBoard().printBoard();
    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, ColumnNoPlayAfterWin) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Position(2, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Position(2, 2)));
    EXPECT_FALSE(simpleGame.makeMove(Position(-1, -1)));

    simpleGame.getBoard().printBoard();
    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, ValidMovesLimited) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));

    std::vector<Position> expectedMoves = {Position(0, 2), Position(1, 1), Position(1, 2),
                                           Position(2, 0), Position(2, 1), Position(2, 2)};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    simpleGame.getBoard().printBoard();
    EXPECT_EQ(simpleGame.getValidMoves(), expectedMoves);
}

TEST(SimpleGameTest, ValidMovesAll) {
    SimpleGame simpleGame(3);
    std::vector<Position> expectedMoves = {Position(0, 0), Position(0, 1), Position(0, 2),
                                           Position(1, 0), Position(1, 1), Position(1, 2),
                                           Position(2, 0), Position(2, 1), Position(2, 2)};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    simpleGame.getBoard().printBoard();
    EXPECT_EQ(simpleGame.getValidMoves(), expectedMoves);
}

TEST(SimpleGameTest, NoValidMovesAfterWin) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Position(2, 0)));

    std::vector<Position> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    simpleGame.getBoard().printBoard();
    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}