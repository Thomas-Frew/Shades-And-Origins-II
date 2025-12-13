#include "../src/headers.hpp"
#include <gtest/gtest.h>

TEST(BoardTest, SelectBestChild) {
    Board<Symbol> board(3);
    Position pos{1, 1};

    EXPECT_EQ(board.getValueAtPosition(pos).has_value(), false);

    Symbol shadeSymbol(SHADE);
    EXPECT_TRUE(board.setValueAtPosition(shadeSymbol, pos));
    EXPECT_EQ(board.getValueAtPosition(pos).value().getIdentity(), SHADE);

    Symbol originSymbol(ORIGIN);
    EXPECT_FALSE(board.setValueAtPosition(originSymbol, pos));
    EXPECT_EQ(board.getValueAtPosition(pos).value().getIdentity(), SHADE);
}

TEST(BoardTest, OutOfBounds) {
    Board<Symbol> board(3);
    Position pos{3, 3};
    Symbol shadeSymbol(SHADE);

    EXPECT_FALSE(board.setValueAtPosition(shadeSymbol, pos));
}

TEST(BoardTest, IdentityBoardSymbols) {
    Board<Symbol> board(2);

    Symbol shadeSymbol(SHADE);
    EXPECT_TRUE(board.setValueAtPosition(shadeSymbol, Position(0, 0)));
    EXPECT_TRUE(board.setValueAtPosition(shadeSymbol, Position(1, 1)));
    EXPECT_EQ(board.getIdentity(), SHADE);
}

TEST(BoardTest, IdentityUpperBoardSymbols) {
    // First, create a simple lower board
    Board<Symbol> board(2);
    Symbol shadeSymbol(SHADE);

    EXPECT_TRUE(board.setValueAtPosition(shadeSymbol, Position(0, 0)));
    EXPECT_TRUE(board.setValueAtPosition(shadeSymbol, Position(1, 1)));
    EXPECT_EQ(board.getIdentity(), SHADE);

    // Create an upper board of boards
    Board<Board<Symbol>> upperBoard(2);
    EXPECT_TRUE(upperBoard.setValueAtPosition(board, Position(0, 0)));
    EXPECT_TRUE(upperBoard.setValueAtPosition(board, Position(1, 1)));

    // Count identities inside the nested boards
    std::unordered_map<Identity, int> freq;
    for (int i = 0; i < 2; i++) {
        std::optional<Board<Symbol>> lowerBoardOpt = upperBoard.getValueAtPosition(Position(i, i));
        if (lowerBoardOpt.has_value() && lowerBoardOpt->getIdentity().has_value()) {
            freq[lowerBoardOpt->getIdentity().value()]++;
        }
    }

    // Print map for debugging
    std::cout << "Identity frequency map:\n";
    for (auto [k, v] : freq) {
        std::cout << k << " -> " << v << '\n';
    }

    // Upper board's identity should match the lower board's identity
    EXPECT_EQ(upperBoard.getIdentity(), SHADE);

    // Each diagonal lower board should have SHADE identity
    EXPECT_EQ(freq[SHADE], 2);
}
