#include "headers.hpp"

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
