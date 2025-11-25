#include "../src/board.cpp"
#include "../src/types.cpp"
#include <iostream>

int main() {
  Board board(3, 3);

  std::cout << String(board.getSymbol(Position(0, 0)).getIdentity()) << '\n';
}