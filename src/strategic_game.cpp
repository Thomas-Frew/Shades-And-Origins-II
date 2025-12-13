#include "headers.hpp"

StrategicGame::StrategicGame(int size, int upperSize) {
    upperBoard = Board<Board<Symbol>>(upperSize, Board<Symbol>(size));
    turn = SHADE;
    activeUpperPositions = getValidUpperPositions();
}

Identity StrategicGame::getPlayerIdentity() {
    return turn;
}

bool StrategicGame::makeMove(Move move) {
    if (upperBoard.getIdentity().has_value()) return false;

    auto upperPosition = move.getUpperPosition();
    if (!upperBoard.validatePosition(upperPosition)) return false;

    auto &lowerBoardOpt = upperBoard.getValueAtPositionRef(upperPosition);
    if (!lowerBoardOpt.has_value()) return false;

    Board<Symbol> &board = *lowerBoardOpt;
    if (board.getIdentity().has_value()) return false;

    auto lowerPosition = move.getLowerPosition();
    bool moveSuccess = board.setValueAtPosition(Symbol(turn), lowerPosition);
    if (!moveSuccess) return false;

    if (!board.getIdentity().has_value()) {
        activeUpperPositions = {lowerPosition};
    } else {
        activeUpperPositions = getValidUpperPositions();
    }

    turn = invertIdentity(turn);
    return true;
}

std::vector<Move> StrategicGame::getValidMoves() {
    return getValidMoves(std::vector<Move>{});
}

std::vector<Move> StrategicGame::getValidMoves(std::vector<Move> bannedMoves) {
    std::vector<Move> validMoves;
    if (upperBoard.getIdentity().has_value()) return validMoves;

    if (activeUpperPositions.empty()) activeUpperPositions = getValidUpperPositions();

    for (auto upperPos : activeUpperPositions) {
        auto lowerBoardPtr = upperBoard.getValueAtPosition(upperPos);
        if (!lowerBoardPtr) continue;

        Board<Symbol> board = *lowerBoardPtr;
        if (board.getIdentity().has_value()) continue;

        int size = board.getSize();
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                Position pos(row, col);
                Move move(row, col, upperPos.row, upperPos.col);
                if (!board.getValueAtPosition(pos).has_value() && std::count(bannedMoves.begin(), bannedMoves.end(), move) == 0) {
                    validMoves.push_back(move);
                }
            }
        }
    }

    return validMoves;
}

std::vector<Position> StrategicGame::getValidUpperPositions() {
    std::vector<Position> validUpperPositions;
    if (upperBoard.getIdentity().has_value()) return validUpperPositions;

    int upperSize = upperBoard.getSize();
    for (int row = 0; row < upperSize; row++) {
        for (int col = 0; col < upperSize; col++) {
            Position pos(row, col);
            auto lowerBoardPtr = upperBoard.getValueAtPosition(pos);
            if (lowerBoardPtr && !lowerBoardPtr->getIdentity().has_value()) {
                validUpperPositions.push_back(pos);
            }
        }
    }

    return validUpperPositions;
}

std::optional<Move> StrategicGame::getRandomValidMove() {
    return getRandomValidMove(std::vector<Move>{});
}

std::optional<Move> StrategicGame::getRandomValidMove(std::vector<Move> bannedMoves) {
    auto validMoves = getValidMoves(bannedMoves);
    if (validMoves.empty()) return std::nullopt;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, validMoves.size() - 1);

    return validMoves[dist(gen)];
}

GamePtr StrategicGame::clone() {
    return std::make_unique<StrategicGame>(*this);
}

std::optional<Identity> StrategicGame::getWinnerIdentity() {
    return upperBoard.getIdentity();
}

std::string StrategicGame::stringify() {
    int upperSize = upperBoard.getSize();
    if (upperSize == 0) return "";

    int lowerSize = upperBoard.getValueAtPosition(Position(0, 0))->getSize();
    std::string result;

    for (int uRow = 0; uRow < upperSize; uRow++) {
        for (int lRow = 0; lRow < lowerSize; lRow++) {
            for (int uCol = 0; uCol < upperSize; uCol++) {
                auto lowerBoardPtr = upperBoard.getValueAtPosition(Position(uRow, uCol));
                for (int lCol = 0; lCol < lowerSize; lCol++) {
                    std::string cell = ".";
                    if (lowerBoardPtr) {
                        auto symbolOpt = lowerBoardPtr->getValueAtPosition(Position(lRow, lCol));
                        if (symbolOpt.has_value()) {
                            cell = identityString(symbolOpt->getIdentity().value());
                        }
                    }
                    result += cell;
                    if (lCol < lowerSize - 1) result += " ";
                }
                if (uCol < upperSize - 1) result += " | ";
            }
            result += "\n";
        }
        if (uRow < upperSize - 1) result += std::string((lowerSize * (upperSize + 1)) * 2 - 2, '-') + "\n";
    }

    return result;
}

std::string StrategicGame::toDot() {
    int upperSize = upperBoard.getSize();
    if (upperSize == 0) return "";

    int lowerSize = 0;
    auto firstLower = upperBoard.getValueAtPosition(Position(0, 0));
    if (firstLower) lowerSize = firstLower->getSize();

    std::string result;

    for (int uRow = 0; uRow < upperSize; uRow++) {
        for (int lRow = 0; lRow < lowerSize; lRow++) {
            for (int uCol = 0; uCol < upperSize; uCol++) {
                auto lowerBoardPtr = upperBoard.getValueAtPosition(Position(uRow, uCol));
                for (int lCol = 0; lCol < lowerSize; lCol++) {
                    std::string cell = ".";
                    if (lowerBoardPtr) {
                        auto symbolOpt = lowerBoardPtr->getValueAtPosition(Position(lRow, lCol));
                        if (symbolOpt.has_value()) {
                            cell = identityString(symbolOpt->getIdentity().value());
                        }
                    }
                    result += cell;
                    if (lCol < lowerSize - 1) result += " ";
                }
                if (uCol < upperSize - 1) result += " | ";
            }
            result += "\\n"; // use escaped newline for DOT labels
        }
        if (uRow < upperSize - 1) result += std::string((lowerSize * (upperSize + 1)) * 2 - 2, '-') + "\\n";
    }

    return result;
}
