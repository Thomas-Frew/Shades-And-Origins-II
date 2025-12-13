#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

// Constants
inline constexpr double root2 = 1.41;

// Types
enum Identity { UNKNOWN, SHADE, ORIGIN };

inline std::string identityString(Identity id) {
    switch (id) {
    case SHADE:
        return "X";
    case ORIGIN:
        return "O";
    default:
        return ".";
    }
}

inline std::string identityToColor(Identity id) {
    switch (id) {
    case SHADE:
        return "X";
    case ORIGIN:
        return "O";
    default:
        return ".";
    }
}

inline Identity invertIdentity(Identity id) {
    switch (id) {
    case SHADE:
        return ORIGIN;
    case ORIGIN:
        return SHADE;
    default:
        return UNKNOWN;
    }
}

// Typedefs
class Game;
class Position;
class MonteCarloNode;
class Symbol;
class SimpleGame;

using NodePtr = std::unique_ptr<MonteCarloNode>;
using GamePtr = std::unique_ptr<Game>;
using SimpleGamePtr = std::unique_ptr<SimpleGame>;

using NodePtrVec = std::vector<NodePtr>;

// Style
inline std::string red = "#990000";
inline std::string blue = "#003090";
inline std::string lightRed = "#FFEEEE";
inline std::string lightBlue = "#DDEEFF";
inline std::string white = "#FFFFFF";
inline std::string black = "#151515";
