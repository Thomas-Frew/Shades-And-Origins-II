#include "../src/board.cpp"
#include <gtest/gtest.h>

TEST(BoardTest, SetAndGetSymbol) {
  Board board(3, 3);
  Position pos{1, 1};

  EXPECT_EQ(board.getSymbol(pos).getIdentity(), EMPTY);

  Symbol shadeSymbol(SHADE);
  EXPECT_TRUE(board.setSymbol(shadeSymbol, pos));
  EXPECT_EQ(board.getSymbol(pos).getIdentity(), SHADE);

  Symbol originSymbol(ORIGIN);
  EXPECT_FALSE(board.setSymbol(originSymbol, pos));
  EXPECT_EQ(board.getSymbol(pos).getIdentity(), SHADE);
}

TEST(BoardTest, OutOfBounds) {
  Board board(3, 3);
  Position pos{3, 3};
  Symbol shadeSymbol(SHADE);

  EXPECT_FALSE(board.setSymbol(shadeSymbol, pos));
}
