#include "headers.hpp"

Position Move::getLowerPosition() const {
    return Position(row, col);
}

Position Move::getUpperPosition() const {
    return Position(upperRow, upperCol);
}