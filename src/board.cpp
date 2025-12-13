#include "headers.hpp"
#include <iostream>
#include <string>

template <typename T> bool Board<T>::validatePosition(Position position) {
    return (position.row >= 0 && position.row < size && position.col >= 0 && position.col < size);
}

template <typename T> std::optional<T> Board<T>::getValueAtPosition(Position pos) {
    return data[pos.row][pos.col];
}

template <typename T> std::optional<T> &Board<T>::getValueAtPositionRef(Position pos) {
    return data[pos.row][pos.col];
}

template <typename T> bool Board<T>::setValueAtPosition(T value, Position pos) {
    if (!validatePosition(pos) || data[pos.row][pos.col].has_value()) {
        return false;
    }
    data[pos.row][pos.col] = value;
    return true;
}

template <typename T> int Board<T>::getSize() {
    return size;
}

template <typename T> std::optional<Identity> Board<T>::getIdentity() {
    int size = getSize();

    auto getCellIdentity = [&](const Position &pos) -> std::optional<Identity> {
        std::optional<T> cellOpt = getValueAtPosition(pos);
        if (!cellOpt.has_value()) return std::nullopt;

        if constexpr (std::is_base_of<Symbol, T>::value) {
            return cellOpt->getIdentity();
        } else {
            return std::nullopt;
        }
    };

    for (int row = 0; row < size; row++) {
        std::unordered_map<Identity, int> freq;
        for (int col = 0; col < size; col++) {
            auto idOpt = getCellIdentity(Position(row, col));
            if (idOpt.has_value()) freq[idOpt.value()]++;
        }
        for (auto [k, v] : freq)
            if (v == size) return k;
    }

    for (int col = 0; col < size; col++) {
        std::unordered_map<Identity, int> freq;
        for (int row = 0; row < size; row++) {
            auto idOpt = getCellIdentity(Position(row, col));
            if (idOpt.has_value()) freq[idOpt.value()]++;
        }
        for (auto [k, v] : freq)
            if (v == size) return k;
    }

    {
        std::unordered_map<Identity, int> freq;
        for (int i = 0; i < size; i++) {
            auto idOpt = getCellIdentity(Position(i, i));
            if (idOpt.has_value()) freq[idOpt.value()]++;
        }
        for (auto [k, v] : freq)
            if (v == size) return k;
    }

    {
        std::unordered_map<Identity, int> freq;
        for (int i = 0; i < size; i++) {
            auto idOpt = getCellIdentity(Position(i, size - 1 - i));
            if (idOpt.has_value()) freq[idOpt.value()]++;
        }
        for (auto [k, v] : freq)
            if (v == size) return k;
    }

    return std::nullopt;
}
