#include "../src/headers.hpp"
#include <iostream>

int main() {
    auto gamePtr = std::make_unique<SimpleGame>(3);
    auto nodePtr = std::make_unique<MonteCarloNode>(std::move(gamePtr));

    MonteCarloSearch monteCarloSearch(std::move(nodePtr), 1.44);
    monteCarloSearch.simulate(100000);
    monteCarloSearch.exportDot("../tree.dot", 3);

    return 0;
}
