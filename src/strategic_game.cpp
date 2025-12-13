// #include "headers.hpp"

// StrategicGame::StrategicGame(int size, int upperSize) {
//     upperBoard = Board(upperSize, Board(size));
//     turn = SHADE;
// }

// Identity SimpleGame::getPlayerIdentity() {
//     return turn;
// }

// std::string SimpleGame::getGameData() {
//     return board.stringify();
// }

// std::optional<Identity> SimpleGame::getWinnerIdentity() {
//     int size = board.getSize();

//     for (int row = 0; row < size; row++) {
//         std::unordered_map<Identity, int> freq;

//         for (int col = 0; col < size; col++) {
//             std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(row, col));
//             if (symbol) {
//                 freq[symbol.value().getIdentity()]++;
//             }
//         }

//         for (auto [k, v] : freq) {
//             if (v == size) {
//                 return k;
//             }
//         }
//     }

//     for (int col = 0; col < size; col++) {
//         std::unordered_map<Identity, int> freq;

//         for (int row = 0; row < size; row++) {
//             std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(row, col));
//             if (symbol) {
//                 freq[symbol.value().getIdentity()]++;
//             }
//         }

//         for (auto [k, v] : freq) {
//             if (v == size) {
//                 return k;
//             }
//         }
//     }

//     {
//         std::unordered_map<Identity, int> freq;
//         for (int i = 0; i < board.getSize(); i++) {
//             std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(i, i));
//             if (symbol) {
//                 freq[symbol.value().getIdentity()]++;
//             }
//         }

//         for (auto [k, v] : freq) {
//             if (v == size) {
//                 return k;
//             }
//         }
//     }

//     {
//         std::unordered_map<Identity, int> freq;
//         for (int i = 0; i < board.getSize(); i++) {
//             std::optional<Symbol> symbol = board.getSymbolAtPosition(Position(i, board.getSize() - 1 - i));
//             if (symbol) {
//                 freq[symbol.value().getIdentity()]++;
//             }
//         }

//         for (auto [k, v] : freq) {
//             if (v == size) {
//                 return k;
//             }
//         }
//     }

//     return std::nullopt;
// }

// bool SimpleGame::makeMove(Move move) {
//     if (getWinnerIdentity().has_value()) {
//         return false;
//     }

//     bool moveSuccess = board.setSymbolAtPosition(Symbol(turn), move.getLowerPosition());
//     if (!moveSuccess) return false;

//     turn = invertIdentity(turn);
//     return true;
// }

// std::vector<Move> SimpleGame::getValidMoves() {
//     return getValidMoves(std::vector<Move>{});
// }

// std::vector<Move> SimpleGame::getValidMoves(std::vector<Move> bannedMoves) {
//     std::vector<Move> validMoves;
//     if (getWinnerIdentity().has_value()) {
//         return validMoves;
//     }

//     int size = board.getSize();
//     for (int row = 0; row < size; row++) {
//         for (int col = 0; col < size; col++) {
//             Move move(row, col);
//             Position pos(row, col);
//             if (!board.getSymbolAtPosition(pos).has_value() && std::count(bannedMoves.begin(), bannedMoves.end(), move) == 0) {
//                 validMoves.push_back(move);
//             }
//         }
//     }

//     return validMoves;
// }

// std::optional<Move> SimpleGame::getRandomValidMove() {
//     return getRandomValidMove(std::vector<Move>{});
// }

// std::optional<Move> SimpleGame::getRandomValidMove(std::vector<Move> bannedMoves) {
//     std::vector<Move> validMoves = getValidMoves(bannedMoves);
//     if (validMoves.empty()) {
//         return std::nullopt;
//     }

//     static std::random_device rd;
//     static std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dist(0, validMoves.size() - 1);

//     return validMoves[dist(gen)];
// }

// GamePtr SimpleGame::clone() {
//     return std::make_unique<SimpleGame>(*this);
// }
