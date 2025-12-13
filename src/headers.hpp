#pragma once
#include "types.hpp"
class Symbol {
  private:
    Identity identity;

  public:
    Symbol() : identity(UNKNOWN) {}
    Symbol(Identity i) : identity(i) {}
    Identity getIdentity();
};

class Position {
  public:
    int row;
    int col;
    bool operator<(const Position &other) const {
        if (row < other.row) return true;
        if (row > other.row) return false;
        return col < other.col;
    }
    bool operator==(const Position &other) const { return row == other.row && col == other.col; }
};

class Board : public Symbol {
  private:
    int size;
    std::vector<std::vector<std::optional<Symbol>>> data;

  public:
    Board(int s) : size(s), data(s, std::vector<std::optional<Symbol>>(s, std::nullopt)) {}
    int getSize();
    bool validatePosition(Position position);
    std::optional<Symbol> getSymbolAtPosition(Position position);
    bool setSymbolAtPosition(Symbol symbol, Position position);
    void printBoard();
    std::string stringBoard();
};

class Game {
  public:
    Game() = default;
    virtual ~Game() = default;
    virtual Board getBoard() = 0;
    virtual Identity getPlayerIdentity() = 0;
    virtual bool makeMove(Position position) = 0;
    virtual std::optional<Identity> getWinnerIdentity() = 0;
    virtual std::vector<Position> getValidMoves() = 0;
    virtual std::vector<Position> getValidMoves(std::vector<Position> bannedMoves) = 0;
    virtual std::optional<Position> getRandomValidMove() = 0;
    virtual std::optional<Position> getRandomValidMove(std::vector<Position> bannedMoves) = 0;
    virtual GamePtr clone() = 0;
};

class SimpleGame : public Game {
  private:
    Identity turn;
    Board board;

  public:
    SimpleGame(int size) : board(size), turn(SHADE) {}

    Board getBoard();
    Identity getPlayerIdentity();

    bool makeMove(Position position);
    std::optional<Identity> getWinnerIdentity();

    std::vector<Position> getValidMoves();
    std::vector<Position> getValidMoves(std::vector<Position> bannedMoves);

    std::optional<Position> getRandomValidMove();
    std::optional<Position> getRandomValidMove(std::vector<Position> bannedMoves);

    GamePtr clone();
};

class MonteCarloNode {
  public:
    GamePtr game;
    int visits = 0, wins = 0;
    NodePtrVec children;
    MonteCarloNode *parent = nullptr;
    std::vector<Position> usedMoves;

    MonteCarloNode(GamePtr game) : game(std::move(game)) {}
    MonteCarloNode(GamePtr game, MonteCarloNode *parent) : MonteCarloNode(std::move(game), parent, {}, 0, 0) {}
    MonteCarloNode(GamePtr game, MonteCarloNode *parent, NodePtrVec &&children, int visits, int wins);

    MonteCarloNode *selectBestChild(double C);
    Identity getDominantPlayer();

    void toDot(std::ofstream &out, int &nodeId, int maxChildren);
};

class MonteCarloSearch {
  public:
    double C;
    MonteCarloSearch(NodePtr head, double C) : head(std::move(head)), C(C) {}

    NodePtr head;
    void simulate(int n);
    void simulateOne();
    MonteCarloNode *selectOrExpand(MonteCarloNode *node, double C);
    void exportDot(std::string filename, int maxChildren);
};
