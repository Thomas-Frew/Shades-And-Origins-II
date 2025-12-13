#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(SimpleGameTest, ValidMovesLimited) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));

    std::vector<Position> expectedMoves = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1), Position(2, 2)};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(validMoves, expectedMoves);
}

TEST(SimpleGameTest, ValidMovesAll) {
    SimpleGame simpleGame(3);
    std::vector<Position> expectedMoves = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1),
                                           Position(1, 2), Position(2, 0), Position(2, 1), Position(2, 2)};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(validMoves, expectedMoves);
}

TEST(SimpleGameTest, NoValidMovesAfterWinRows) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));

    std::vector<Position> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, NoValidMovesAfterWinCols) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));

    std::vector<Position> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, NoValidMovesAfterWinDiag1) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 1)));

    std::vector<Position> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, NoValidMovesAfterWinDiag2) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));

    std::vector<Position> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, ValidMovesWithBan) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Position(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Position(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Position(1, 0)));

    std::vector<Position> bannedMoves = {Position(0, 2), Position(1, 1), Position(1, 2)};
    std::vector<Position> expectedMoves = {Position(2, 0), Position(2, 1), Position(2, 2)};

    auto validMoves = simpleGame.getValidMoves(bannedMoves);
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(validMoves, expectedMoves);
}