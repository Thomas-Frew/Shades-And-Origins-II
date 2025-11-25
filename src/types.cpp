#pragma once
#include <string>

enum Identity { EMPTY, SHADE, ORIGIN };

inline std::string String(Identity id) {
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