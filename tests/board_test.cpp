#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(BoardTest, SetAndGetSymbol) {
    Board board(3);
    Position pos{1, 1};

    EXPECT_EQ(board.getSymbolAtPosition(pos).getIdentity(), EMPTY);

    Symbol shadeSymbol(SHADE);
    EXPECT_TRUE(board.setSymbolAtPosition(shadeSymbol, pos));
    EXPECT_EQ(board.getSymbolAtPosition(pos).getIdentity(), SHADE);

    Symbol originSymbol(ORIGIN);
    EXPECT_FALSE(board.setSymbolAtPosition(originSymbol, pos));
    EXPECT_EQ(board.getSymbolAtPosition(pos).getIdentity(), SHADE);
}

TEST(BoardTest, OutOfBounds) {
    Board board(3);
    Position pos{3, 3};
    Symbol shadeSymbol(SHADE);

    EXPECT_FALSE(board.setSymbolAtPosition(shadeSymbol, pos));
}
