#include "../src/headers.hpp"
#include <iostream>

int main() {
    SimpleGame simpleGame(3);

    simpleGame.makeMove(Position(0, 0));
    simpleGame.makeMove(Position(0, 1));
    simpleGame.makeMove(Position(1, 1));
    simpleGame.makeMove(Position(0, 2));
    simpleGame.makeMove(Position(2, 2));

    std::cout << "GAME BOARD" << '\n';
    simpleGame.getBoard().printBoard();
}