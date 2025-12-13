#include "headers.hpp"
#include <optional>
#include <unordered_map>
#include <vector>

Identity StrategicGame::getPlayerIdentity() {
    return turn;
}

std::string StrategicGame::getGameData() {
    return board.stringify();
}

std::optional<Identity> StrategicGame::getWinnerIdentity() {
    int size = board.getSize();

    for (int row = 0; row < size; row++) {
        std::unordered_map<Identity, int> freq;

        for (int col = 0; col < size; col++) {
            std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(row, col));
            if (symbol) {
                freq[symbol.value().getIdentity()]++;
            }
        }

        for (auto [k, v] : freq) {
            if (v == size) {
                return k;
            }
        }
    }

    for (int col = 0; col < size; col++) {
        std::unordered_map<Identity, int> freq;

        for (int row = 0; row < size; row++) {
            std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(row, col));
            if (symbol) {
                freq[symbol.value().getIdentity()]++;
            }
        }

        for (auto [k, v] : freq) {
            if (v == size) {
                return k;
            }
        }
    }

    {
        std::unordered_map<Identity, int> freq;
        for (int i = 0; i < board.getSize(); i++) {
            std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(i, i));
            if (symbol) {
                freq[symbol.value().getIdentity()]++;
            }
        }

        for (auto [k, v] : freq) {
            if (v == size) {
                return k;
            }
        }
    }

    {
        std::unordered_map<Identity, int> freq;
        for (int i = 0; i < board.getSize(); i++) {
            std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(i, board.getSize() - 1 - i));
            if (symbol) {
                freq[symbol.value().getIdentity()]++;
            }
        }

        for (auto [k, v] : freq) {
            if (v == size) {
                return k;
            }
        }
    }

    return std::nullopt;
}

bool StrategicGame::makeMove(Position position) {
    if (getWinnerIdentity().has_value()) {
        return false;
    }

    bool moveSuccess = board.setSymbolAtPosition(Symbol(turn), position);
    if (!moveSuccess) return false;

    turn = invertIdentity(turn);
    return true;
}

std::vector<Position> StrategicGame::getValidMoves() {
    return getValidMoves(std::vector<Position>{});
}

std::vector<Position> StrategicGame::getValidMoves(std::vector<Position> bannedMoves) {
    std::vector<Position> validMoves;
    if (getWinnerIdentity().has_value()) {
        return validMoves;
    }

    int size = board.getSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Position pos(row, col);
            if (!board.getSymbolAtPosition(pos).has_value() && std::count(bannedMoves.begin(), bannedMoves.end(), pos) == 0) {
                validMoves.push_back(pos);
            }
        }
    }

    return validMoves;
}

std::optional<Position> StrategicGame::getRandomValidMove() {
    return getRandomValidMove(std::vector<Position>{});
}

std::optional<Position> StrategicGame::getRandomValidMove(std::vector<Position> bannedMoves) {
    std::vector<Position> validMoves = getValidMoves(bannedMoves);
    if (validMoves.empty()) {
        return std::nullopt;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, validMoves.size() - 1);

    return validMoves[dist(gen)];
}

GamePtr StrategicGame::clone() {
    return std::make_unique<StrategicGame>(*this);
}
