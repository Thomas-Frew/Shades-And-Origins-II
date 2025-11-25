#include "headers.hpp"
#include <vector>

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