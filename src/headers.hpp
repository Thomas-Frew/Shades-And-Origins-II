#pragma once
#include "types.hpp"
class Symbol {
  private:
    std::optional<Identity> identity;

  public:
    Symbol() : identity(std::nullopt) {}
    Symbol(std::optional<Identity> i) : identity(i) {}
    std::optional<Identity> getIdentity();
};

class Position {
  public:
    int row;
    int col;

    Position() : row(0), col(0) {}
    Position(int r, int c) : row(r), col(c) {}

    bool operator<(const Position &other) const {
        if (row != other.row) return row < other.row;
        return col < other.col;
    }

    bool operator==(const Position &other) const { return row == other.row && col == other.col; }
    bool operator!=(const Position &other) const { return !(*this == other); }
};

class Move {
  public:
    int row;
    int col;
    int upperRow;
    int upperCol;

    Move() : row(0), col(0), upperRow(0), upperCol(0) {}
    Move(int r, int c) : row(r), col(c), upperRow(r), upperCol(c) {}
    Move(int r, int c, int ur, int uc) : row(r), col(c), upperRow(ur), upperCol(uc) {}

    Position getLowerPosition() const;
    Position getUpperPosition() const;

    bool operator<(const Move &other) const {
        if (getLowerPosition() != other.getLowerPosition()) return getLowerPosition() < other.getLowerPosition();
        return getUpperPosition() < other.getUpperPosition();
    }

    bool operator==(const Move &other) const {
        return getUpperPosition() == other.getUpperPosition() && getUpperPosition() == other.getUpperPosition();
    }
};

template <typename T> class Board : public Symbol {
  private:
    int size;
    std::vector<std::vector<std::optional<T>>> data;

  public:
    Board() : Symbol(std::nullopt), size(0), data() {}
    Board(int s) : Board(s, std::nullopt) {}
    Board(int s, std::optional<T> value) : size(s), data(s, std::vector<std::optional<T>>(s, value)) {}

    int getSize();
    bool validatePosition(Position pos);

    std::optional<T> getValueAtPosition(Position pos);
    std::optional<T> &getValueAtPositionRef(Position pos);
    bool setValueAtPosition(T value, Position pos);

    std::optional<Identity> getIdentity();
};

template class Board<Symbol>;
template class Board<Board<Symbol>>;

class Game {
  public:
    Game() = default;
    virtual ~Game() = default;
    virtual Identity getPlayerIdentity() = 0;
    virtual std::optional<Identity> getWinnerIdentity() = 0;
    virtual bool makeMove(Move move) = 0;
    virtual std::vector<Move> getValidMoves() = 0;
    virtual std::vector<Move> getValidMoves(std::vector<Move> bannedMoves) = 0;
    virtual std::optional<Move> getRandomValidMove() = 0;
    virtual std::optional<Move> getRandomValidMove(std::vector<Move> bannedMoves) = 0;
    virtual std::string stringify() = 0;
    virtual std::string toDot() = 0;
    virtual GamePtr clone() = 0;
};

class SimpleGame : public Game {
  private:
    Identity turn;
    Board<Symbol> board;

  public:
    SimpleGame(int size) : board(size), turn(SHADE) {}

    Identity getPlayerIdentity();
    std::optional<Identity> getWinnerIdentity();

    bool makeMove(Move move);

    std::vector<Move> getValidMoves();
    std::vector<Move> getValidMoves(std::vector<Move> bannedMoves);

    std::optional<Move> getRandomValidMove();
    std::optional<Move> getRandomValidMove(std::vector<Move> bannedMoves);

    std::string stringify();
    std::string toDot();
    GamePtr clone();
};

class StrategicGame : public Game {
  private:
    Identity turn;
    std::vector<Position> activeUpperPositions;
    Board<Board<Symbol>> upperBoard;

  public:
    StrategicGame(int size, int upperSize);

    Identity getPlayerIdentity();
    std::optional<Identity> getWinnerIdentity();

    bool makeMove(Move move);

    std::vector<Position> getValidUpperPositions();

    std::vector<Move> getValidMoves();
    std::vector<Move> getValidMoves(std::vector<Move> bannedMoves);

    std::optional<Move> getRandomValidMove();
    std::optional<Move> getRandomValidMove(std::vector<Move> bannedMoves);

    std::string stringify();
    std::string toDot();
    GamePtr clone();
};

class MonteCarloNode {
  public:
    GamePtr game;
    int visits = 0, wins = 0;
    NodePtrVec children;
    MonteCarloNode *parent = nullptr;
    std::vector<Move> usedMoves;

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
