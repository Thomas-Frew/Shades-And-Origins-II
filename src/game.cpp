#include "headers.hpp"
#include <iostream>
#include <unordered_map>

Board Game::getBoard() {
    return board;
}

Identity Game::getWinnerIdentity() {
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