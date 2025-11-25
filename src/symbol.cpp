#pragma once
#include "types.cpp"

class Symbol {
private:
  Identity identity;

public:
  Symbol() : identity(EMPTY) {}
  Symbol(Identity i) : identity(i) {}
  Identity getIdentity();
};

Identity Symbol::getIdentity() { return identity; }