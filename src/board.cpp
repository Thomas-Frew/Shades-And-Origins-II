#include "headers.hpp"
#include <iostream>
#include <string>

bool Board::validatePosition(Position position) {
    return (position.row >= 0 && position.row < size && position.col >= 0 && position.col < size);
}

std::optional<Symbol> Board::getSymbolAtPosition(Position position) {
    if (!validatePosition(position)) {
        return std::nullopt;
    }

    return data[position.row][position.col];
}

bool Board::setSymbolAtPosition(Symbol symbol, Position position) {
    if (!validatePosition(position)) {
        return false;
    }

    if (getSymbolAtPosition(position).has_value()) {
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
            std::string id = ".";
            std::optional<Symbol> symbol = getSymbolAtPosition(Position(row, col));

            if (symbol.has_value()) {
                id = identityString(symbol.value().getIdentity());
            }

            std::cout << id << ' ';
        }
        std::cout << '\n';
    }
}

std::string Board::stringBoard() {
    std::string result;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::string id = ".";
            std::optional<Symbol> symbol = getSymbolAtPosition(Position(row, col));

            if (symbol.has_value()) {
                id = identityString(symbol.value().getIdentity());
            }

            result += id;
            if (col < size - 1) result += " ";
        }
        result += "\\n";
    }

    return result;
}