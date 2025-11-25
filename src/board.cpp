#pragma once
#include <vector>

#include "position.cpp"
#include "symbol.cpp"

class Board : public Symbol {
private:
  int rows;
  int cols;
  std::vector<std::vector<Symbol>> data;

public:
  Board(int rows, int cols)
      : rows(rows), cols(cols),
        data(rows, std::vector<Symbol>(cols, Symbol(EMPTY))) {}

  bool validatePosition(Position position);

  Symbol getSymbol(Position position);
  bool setSymbol(Symbol symbol, Position position);
};

bool Board::validatePosition(Position position) {
  return (position.row >= 0 && position.row < rows && position.col >= 0 &&
          position.col < cols);
}

Symbol Board::getSymbol(Position position) {
  if (!validatePosition(position)) {
    return EMPTY;
  }

  return data[position.row][position.col];
}

bool Board::setSymbol(Symbol symbol, Position position) {
  if (!validatePosition(position)) {
    return false;
  }

  if (getSymbol(position).getIdentity() != EMPTY) {
    return false;
  }

  data[position.row][position.col] = symbol;
  return true;
}
