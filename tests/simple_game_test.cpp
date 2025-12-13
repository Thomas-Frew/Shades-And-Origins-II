#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(SimpleGameTest, RaceToTheEnd) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(2, 0)));

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, CheatersLeague) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Move(3, 3)));
    EXPECT_TRUE(simpleGame.makeMove(Move(2, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(2, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Move(2, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Move(2, 1)));

    EXPECT_EQ(simpleGame.getWinnerIdentity(), ORIGIN);
}

TEST(SimpleGameTest, Diagonal) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Move(2, 2)));

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}

TEST(SimpleGameTest, ColumnNoPlayAfterWin) {
    SimpleGame simpleGame(3);

    EXPECT_TRUE(simpleGame.makeMove(Move(0, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 1)));
    EXPECT_TRUE(simpleGame.makeMove(Move(1, 0)));
    EXPECT_TRUE(simpleGame.makeMove(Move(0, 2)));
    EXPECT_TRUE(simpleGame.makeMove(Move(2, 0)));
    EXPECT_FALSE(simpleGame.makeMove(Move(2, 2)));
    EXPECT_FALSE(simpleGame.makeMove(Move(-1, -1)));

    EXPECT_EQ(simpleGame.getWinnerIdentity(), SHADE);
}