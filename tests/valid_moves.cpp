#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(SimpleGameTest, ValidMovesLimited) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));

    std::vector<Move> expectedMoves = {Move(0, 2), Move(1, 1), Move(1, 2), Move(2, 0), Move(2, 1), Move(2, 2)};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(validMoves, expectedMoves);
}

TEST(SimpleGameTest, ValidMovesAll) {
    SimpleGame simpleGame(3);
    std::vector<Move> expectedMoves = {Move(0, 0), Move(0, 1), Move(0, 2), Move(1, 0), Move(1, 1), Move(1, 2), Move(2, 0), Move(2, 1), Move(2, 2)};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(validMoves, expectedMoves);
}

TEST(SimpleGameTest, NoValidMovesAfterWinRows) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 1)));

    std::vector<Move> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, NoValidMovesAfterWinCols) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));

    std::vector<Move> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, NoValidMovesAfterWinDiag1) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 1)));

    std::vector<Move> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, NoValidMovesAfterWinDiag2) {
    SimpleGame simpleGame(2);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));

    std::vector<Move> expectedMoves = {};

    auto validMoves = simpleGame.getValidMoves();
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, ValidMovesWithBan) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));

    std::vector<Move> bannedMoves = {Move(0, 2), Move(1, 1), Move(1, 2)};
    std::vector<Move> expectedMoves = {Move(2, 0), Move(2, 1), Move(2, 2)};

    auto validMoves = simpleGame.getValidMoves(bannedMoves);
    std::sort(validMoves.begin(), validMoves.end());

    EXPECT_EQ(validMoves, expectedMoves);
}