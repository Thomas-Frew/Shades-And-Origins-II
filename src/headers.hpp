#pragma once
#include "types.hpp"
#include <vector>

class Symbol {
  private:
    Identity identity;

  public:
    Symbol() : identity(EMPTY) {}
    Symbol(Identity i) : identity(i) {}
    Identity getIdentity();
};

class Position {
  public:
    int row;
    int col;
};

class Board : public Symbol {
  protected:
    int size;
    std::vector<std::vector<Symbol>> data;

  public:
    Board(int s) : size(s), data(s, std::vector<Symbol>(s, Symbol(EMPTY))) {}

    int getSize();
    bool validatePosition(Position position);

    Symbol getSymbolAtPosition(Position position);
    bool setSymbolAtPosition(Symbol symbol, Position position);

    void printBoard();
};

class Game {
  protected:
    Board board;

  public:
    Game();
    Game(int size) : board(size) {}
    virtual ~Game() = default;
    virtual bool makeMove(Position position) = 0;
    virtual Identity getWinnerIdentity();

    Board getBoard();
};

class SimpleGame : public Game {
  private:
    Identity turn;

  public:
    SimpleGame(int size) : Game(size), turn(SHADE) {}
    bool makeMove(Position position);
};
