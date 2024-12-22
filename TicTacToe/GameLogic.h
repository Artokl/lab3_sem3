#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <array>

constexpr int GRID_SIZE = 5;
constexpr int WIN_CONDITION = 4;

enum class Player { Empty, Cross, Circle };

typedef std::array<std::array<Player, GRID_SIZE>, GRID_SIZE> Board;

class GameLogic {
public:
    // Check if the current player has won
    static bool checkWin(const Board& board, Player player);

    // Check if the board is full (draw condition)
    static bool isBoardFull(const Board& board);

    // Evaluate the board for heuristic scoring
    static int evaluateBoard(const Board& board, Player maximizingPlayer);
};

inline bool GameLogic::checkWin(const Board& board, Player player) {
    // Horizontal, vertical, and diagonal checks
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (j + WIN_CONDITION <= GRID_SIZE) {
                // Horizontal
                bool win = true;
                for (int k = 0; k < WIN_CONDITION; ++k) {
                    if (board[i][j + k] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }

            if (i + WIN_CONDITION <= GRID_SIZE) {
                // Vertical
                bool win = true;
                for (int k = 0; k < WIN_CONDITION; ++k) {
                    if (board[i + k][j] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;

                if (j + WIN_CONDITION <= GRID_SIZE) {
                    // \ Diagonal
                    win = true;
                    for (int k = 0; k < WIN_CONDITION; ++k) {
                        if (board[i + k][j + k] != player) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return true;
                }

                if (j - WIN_CONDITION + 1 >= 0) {
                    // / Diagonal
                    win = true;
                    for (int k = 0; k < WIN_CONDITION; ++k) {
                        if (board[i + k][j - k] != player) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return true;
                }
            }
        }
    }

    return false;
}

inline bool GameLogic::isBoardFull(const Board& board) {
    for (const auto& row : board) {
        for (const Player cell : row) {
            if (cell == Player::Empty) {
                return false;
            }
        }
    }
    return true;
}

inline int GameLogic::evaluateBoard(const Board& board, Player maximizingPlayer) {
    const Player minimizingPlayer = (maximizingPlayer == Player::Cross) ? Player::Circle : Player::Cross;

    if (checkWin(board, maximizingPlayer)) {
        return 1000;
    }
    if (checkWin(board, minimizingPlayer)) {
        return -1000;
    }

    // Heuristic: Sum of consecutive player counts in rows, columns, and diagonals
    int score = 0;

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (board[i][j] == maximizingPlayer) {
                score += 10;
            } else if (board[i][j] == minimizingPlayer) {
                score -= 10;
            }
        }
    }

    return score;
}

#endif // GAME_LOGIC_H
