#include "../src/headers.hpp"
#include <gtest/gtest.h>

int getWins(const NodePtrVec &nodes) {
    int val = 0;
    for (auto &node : nodes) val += node->wins;
    return val;
}

int getVisits(const NodePtrVec &nodes) {
    int val = 0;
    for (auto &node : nodes) val += node->visits;
    return val;
}

TEST(MCNodeTest, SelectBestNode) {
    NodePtrVec children;
    children.push_back(std::make_unique<MonteCarloNode>(nullptr, nullptr, NodePtrVec{}, 1, 1));
    children.push_back(std::make_unique<MonteCarloNode>(nullptr, nullptr, NodePtrVec{}, 1, 0));

    int totalVisits = getVisits(children);
    int totalWins = getWins(children);

    auto parentNode = std::make_unique<MonteCarloNode>(nullptr, nullptr, std::move(children), totalVisits, totalWins);

    auto bestChild = parentNode->selectBestChild(root2);
    ASSERT_NE(bestChild, nullptr);
    ASSERT_EQ(bestChild->visits, 1);
    ASSERT_EQ(bestChild->wins, 1);
}

TEST(MCNodeTest, SelectBestNodeMoreComplex) {
    NodePtrVec children;
    children.push_back(std::make_unique<MonteCarloNode>(nullptr, nullptr, NodePtrVec{}, 5, 3));
    children.push_back(std::make_unique<MonteCarloNode>(nullptr, nullptr, NodePtrVec{}, 6, 4));
    children.push_back(std::make_unique<MonteCarloNode>(nullptr, nullptr, NodePtrVec{}, 2, 0));

    int totalVisits = getVisits(children);
    int totalWins = getWins(children);

    auto parentNode = std::make_unique<MonteCarloNode>(nullptr, nullptr, std::move(children), totalVisits, totalWins);

    auto bestChild = parentNode->selectBestChild(root2);
    ASSERT_NE(bestChild, nullptr);
    ASSERT_EQ(bestChild->visits, 6);
    ASSERT_EQ(bestChild->wins, 4);
}
