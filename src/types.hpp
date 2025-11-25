#include <string>

enum Identity { EMPTY, SHADE, ORIGIN };

inline std::string identityString(Identity id) {
    switch (id) {
    case EMPTY:
        return ".";
    case SHADE:
        return "X";
    case ORIGIN:
        return "O";
    default:
        return "?";
    }
}

inline Identity invertIdentity(Identity id) {
    switch (id) {
    case EMPTY:
        return EMPTY;
    case SHADE:
        return ORIGIN;
    case ORIGIN:
        return SHADE;
    default:
        return EMPTY;
    }
}