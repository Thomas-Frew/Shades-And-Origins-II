#include "headers.hpp"
#include <algorithm>
#include <optional>
#include <random>
#include <vector>

Identity SimpleGame::getPlayerIdentity() {
    return turn;
}

std::string SimpleGame::stringify() {
    return "NI";
}

bool SimpleGame::makeMove(Move move) {
    if (board.getIdentity().has_value()) return false;
    if (!board.setValueAtPosition(Symbol(turn), move.getLowerPosition())) return false;

    turn = invertIdentity(turn);
    return true;
}

std::vector<Move> SimpleGame::getValidMoves() {
    return getValidMoves({});
}

std::vector<Move> SimpleGame::getValidMoves(std::vector<Move> bannedMoves) {
    std::vector<Move> validMoves;
    if (getWinnerIdentity().has_value()) return validMoves;

    int size = board.getSize();
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            Move move(row, col);
            if (!board.getValueAtPosition(move.getLowerPosition()).has_value() && std::count(bannedMoves.begin(), bannedMoves.end(), move) == 0) {
                validMoves.push_back(move);
            }
        }
    }

    return validMoves;
}

std::optional<Move> SimpleGame::getRandomValidMove() {
    return getRandomValidMove({});
}

std::optional<Move> SimpleGame::getRandomValidMove(std::vector<Move> bannedMoves) {
    auto validMoves = getValidMoves(bannedMoves);
    if (validMoves.empty()) return std::nullopt;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, validMoves.size() - 1);

    return validMoves[dist(gen)];
}

GamePtr SimpleGame::clone() {
    return std::make_unique<SimpleGame>(*this);
}

std::optional<Identity> SimpleGame::getWinnerIdentity() {
    return board.getIdentity();
}

std::string SimpleGame::toDot() {
    std::string result;
    int size = board.getSize();

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::string id = ".";
            std::optional<Symbol> symbol = board.getValueAtPosition(Position(row, col));

            if (symbol.has_value()) {
                id = identityString(symbol.value().getIdentity().value());
            }

            result += id;
            if (col < size - 1) result += " ";
        }
        result += "\\n";
    }
    return result;
}
