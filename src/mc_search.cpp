#include "headers.hpp"
#include <iostream>
#include <memory>
#include <random>

std::mt19937 randGen;

void MonteCarloSearch::simulate(int n) {
    std::mt19937 randGen(std::random_device{}());
    for (int i = 0; i < n; i++) {
        simulateOne();
    }
}

MonteCarloNode *MonteCarloSearch::selectOrExpand(MonteCarloNode *node, double C) {
    while (true) {
        auto validMoves = node->game->getValidMoves(node->usedMoves);

        if (!validMoves.empty()) {
            std::uniform_int_distribution<size_t> dist(0, validMoves.size() - 1);
            auto move = validMoves[dist(randGen)];

            node->usedMoves.push_back(move);

            auto newGame = node->game->clone();
            newGame->makeMove(move);

            auto child = std::make_unique<MonteCarloNode>(std::move(newGame), node);
            node->children.push_back(std::move(child));

            return node->children.back().get();
        }

        if (node->children.empty()) return node;
        node = node->selectBestChild(C);
    }
}

void MonteCarloSearch::simulateOne() {
    MonteCarloNode *leaf = selectOrExpand(head.get(), C);

    auto simGame = leaf->game->clone();
    while (true) {
        auto moveOpt = simGame->getRandomValidMove();
        if (!moveOpt.has_value()) break;
        simGame->makeMove(*moveOpt);
    }

    auto winner = simGame->getWinnerIdentity();
    MonteCarloNode *node = leaf;
    while (node != nullptr) {
        node->visits++;
        if (winner.has_value() && winner.value() == node->game->getPlayerIdentity()) {
            node->wins++;
        }
        node = node->parent;
    }
};

void MonteCarloSearch::exportDot(std::string filename, int maxChildren) {
    std::ofstream out(filename);
    out << "digraph MCTS {\n";
    int nodeId = 0;
    head->toDot(out, nodeId, maxChildren);
    out << "}\n";
    out.close();
}