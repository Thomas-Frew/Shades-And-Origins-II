#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(BoardTest, SelectBestChild) {
    Board board(3);
    Position pos{1, 1};

    EXPECT_EQ(board.getSymbolAtPosition(pos).has_value(), false);

    Symbol shadeSymbol(SHADE);
    EXPECT_TRUE(board.setSymbolAtPosition(shadeSymbol, pos));
    EXPECT_EQ(board.getSymbolAtPosition(pos).value().getIdentity(), SHADE);

    Symbol originSymbol(ORIGIN);
    EXPECT_FALSE(board.setSymbolAtPosition(originSymbol, pos));
    EXPECT_EQ(board.getSymbolAtPosition(pos).value().getIdentity(), SHADE);
}

TEST(BoardTest, OutOfBounds) {
    Board board(3);
    Position pos{3, 3};
    Symbol shadeSymbol(SHADE);

    EXPECT_FALSE(board.setSymbolAtPosition(shadeSymbol, pos));
}
