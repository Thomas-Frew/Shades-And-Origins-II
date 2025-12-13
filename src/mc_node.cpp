#include "headers.hpp"

MonteCarloNode::MonteCarloNode(GamePtr game, MonteCarloNode *parentNode, NodePtrVec &&childNodes, int initialVisits, int initialWins)
    : game(std::move(game)), parent(parentNode), children(std::move(childNodes)), visits(initialVisits), wins(initialWins) {
    for (auto &child : children) {
        child->parent = this;
    }
}

MonteCarloNode *MonteCarloNode::selectBestChild(double c) {
    double bestScore = -1e9;
    MonteCarloNode *bestChild;

    for (auto &child : children) {
        MonteCarloNode *rawChild = child.get();
        double exploitation = double(rawChild->wins) / (rawChild->visits + 1);
        double exploration = c * sqrt(log(visits + 1) / (rawChild->visits + 1));
        double uct = exploitation + exploration;

        if (uct > bestScore) {
            bestScore = uct;
            bestChild = rawChild;
        }
    }

    return bestChild;
}

Identity MonteCarloNode::getDominantPlayer() {
    auto player = game->getPlayerIdentity();

    if (static_cast<double>(wins) / static_cast<double>(visits) < 0.5) {
        player = invertIdentity(player);
    }

    return player;
}

void MonteCarloNode::toDot(std::ofstream &out, int &nodeId, int maxChildren) {
    int currentId = nodeId++;
    std::string boardStr = game->getBoard().stringBoard();

    std::string fillColor = white;
    std::string fontColor = black;

    if (game->getWinnerIdentity().has_value()) {
        fontColor = white;
        if (game->getWinnerIdentity().value() == SHADE) {
            fillColor = blue;
        } else if (game->getWinnerIdentity().value() == ORIGIN) {
            fillColor = red;
        }
    } else {
        if (getDominantPlayer() == SHADE) {
            fillColor = lightRed;
        } else if (getDominantPlayer() == ORIGIN) {
            fillColor = lightBlue;
        }
    }

    out << "  node" << currentId << " [label=\"visits=" << visits << "\\nwins=" << wins << "\\nplayer=" << game->getPlayerIdentity() << "\\n"
        << boardStr << "\", fontname=\"Monospace\", fontsize=" << 8 << ", shape=box, style=filled, fontcolor=\"" << fontColor << "\", fillcolor=\""
        << fillColor << "\"];\n";

    std::sort(children.begin(), children.end(), [](const auto &a, const auto &b) { return a->visits > b->visits; });

    int childrenRendered = 0;
    for (auto &child : children) {
        if (childrenRendered >= maxChildren) {
            int ellipsisId = nodeId++;
            out << "  node" << ellipsisId << " [label=\"...\", fontname=\"Monospace\", fontsize=8, shape=box];\n";
            out << "  node" << currentId << " -> node" << ellipsisId << ";\n";
            break;
        }

        int childId = nodeId;
        child->toDot(out, nodeId, maxChildren);
        out << "  node" << currentId << " -> node" << childId << ";\n";
        childrenRendered++;
    }
}
