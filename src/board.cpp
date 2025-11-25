#include "headers.hpp"
#include <iostream>

bool Board::validatePosition(Position position) {
    return (position.row >= 0 && position.row < size && position.col >= 0 && position.col < size);
}

Symbol Board::getSymbolAtPosition(Position position) {
    if (!validatePosition(position)) {
        return EMPTY;
    }

    return data[position.row][position.col];
}

bool Board::setSymbolAtPosition(Symbol symbol, Position position) {
    if (!validatePosition(position)) {
        return false;
    }

    if (getSymbolAtPosition(position).getIdentity() != EMPTY) {
        return false;
    }

    data[position.row][position.col] = symbol;
    return true;
}

int Board::getSize() {
    return size;
}

void Board::printBoard() {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::cout << identityString(data[row][col].getIdentity()) << ' ';
        }
        std::cout << '\n';
    }
}