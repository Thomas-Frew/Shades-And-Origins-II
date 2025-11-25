#include "headers.hpp"
#include <unordered_map>
#include <vector>

Board SimpleGame::getBoard() {
    return board;
}

Identity SimpleGame::getWinnerIdentity() {
    int size = board.getSize();

    for (int row = 0; row < size; row++) {
        std::unordered_map<Identity, int> freq;

        for (int col = 0; col < size; col++) {
            Identity identity = board.getSymbolAtPosition(Position(row, col)).getIdentity();
            freq[identity]++;
        }

        for (auto [k, v] : freq) {
            if (v == size && k != EMPTY) {
                return k;
            }
        }
    }

    for (int col = 0; col < size; col++) {
        std::unordered_map<Identity, int> freq;

        for (int row = 0; row < size; row++) {
            Identity identity = board.getSymbolAtPosition(Position(row, col)).getIdentity();
            freq[identity]++;
        }

        for (auto [k, v] : freq) {
            if (v == size && k != EMPTY) {
                return k;
            }
        }
    }

    {
        std::unordered_map<Identity, int> freq;
        for (int i = 0; i < board.getSize(); i++) {
            Identity identity = board.getSymbolAtPosition(Position(i, i)).getIdentity();
            freq[identity]++;
        }

        for (auto [k, v] : freq) {
            if (v == size && k != EMPTY) {
                return k;
            }
        }
    }

    return EMPTY;
}

bool SimpleGame::makeMove(Position position) {
    if (getWinnerIdentity() != EMPTY) {
        return false;
    }

    Symbol simpleSymbol(turn);
    bool moveSuccess = board.setSymbolAtPosition(Symbol(turn), position);

    if (!moveSuccess) return false;

    turn = invertIdentity(turn);
    return true;
}

std::vector<Position> SimpleGame::getValidMoves() {
    std::vector<Position> validMoves;
    if (getWinnerIdentity() != EMPTY) {
        return validMoves;
    }

    int size = board.getSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board.getSymbolAtPosition(Position(row, col)).getIdentity() == EMPTY) {
                validMoves.emplace_back(row, col);
            }
        }
    }

    return validMoves;
}