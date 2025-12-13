#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(StrategicGameTest, SimpleWin) {
    StrategicGame game(2, 2);
    EXPECT_TRUE(game.makeMove(Move(0, 0, 0, 0)));
    EXPECT_TRUE(game.makeMove(Move(0, 1, 0, 0)));
    EXPECT_TRUE(game.makeMove(Move(1, 0, 0, 0)));
    EXPECT_TRUE(game.makeMove(Move(0, 0, 0, 1)));
    EXPECT_TRUE(game.makeMove(Move(0, 0, 1, 1)));
    EXPECT_TRUE(game.makeMove(Move(0, 1, 1, 1)));
    EXPECT_TRUE(game.makeMove(Move(1, 0, 1, 1)));

    std::cout << game.stringify() << '\n';

    EXPECT_EQ(game.getWinnerIdentity(), SHADE);
}