// AIEngine.h
#ifndef AI_ENGINE_H
#define AI_ENGINE_H

#include "GameLogic.h"
#include <limits>
#include <vector>
#include <algorithm>
#include <random>

class AIEngine {
public:
    static sf::Vector2i findBestMove(Board& board, Player aiPlayer, int maxDepth = 6);

private:
    static int minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta, Player aiPlayer);
    static std::vector<sf::Vector2i> getValidMoves(const Board& board);
};

inline sf::Vector2i AIEngine::findBestMove(Board& board, const Player aiPlayer, const int maxDepth) {
    int bestScore = std::numeric_limits<int>::min();
    sf::Vector2i bestMove(-1, -1);

    for (const auto& move : getValidMoves(board)) {
        board[move.y][move.x] = aiPlayer;
        const int score = minimax(board, maxDepth - 1, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), aiPlayer);
        board[move.y][move.x] = Player::Empty;

        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

inline int AIEngine::minimax(Board& board, const int depth, const bool isMaximizing, int alpha, int beta, const Player aiPlayer) {
    const Player opponent = (aiPlayer == Player::Cross) ? Player::Circle : Player::Cross;

    if (GameLogic::checkWin(board, aiPlayer)) {
        return 1000 - depth; // Favor quicker wins
    }
    if (GameLogic::checkWin(board, opponent)) {
        return depth - 1000; // Favor slower losses
    }
    if (GameLogic::isBoardFull(board) || depth == 0) {
        return GameLogic::evaluateBoard(board, aiPlayer);
    }

    if (isMaximizing) {
        int maxEval = std::numeric_limits<int>::min();

        for (const auto& move : getValidMoves(board)) {
            board[move.y][move.x] = aiPlayer;
            int eval = minimax(board, depth - 1, false, alpha, beta, aiPlayer);
            board[move.y][move.x] = Player::Empty;

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);

            if (beta <= alpha) {
                break; // Prune
            }
        }

        return maxEval;
    }
    int minEval = std::numeric_limits<int>::max();

    for (const auto& move : getValidMoves(board)) {
        board[move.y][move.x] = opponent;
        int eval = minimax(board, depth - 1, true, alpha, beta, aiPlayer);
        board[move.y][move.x] = Player::Empty;

        minEval = std::min(minEval, eval);
        beta = std::min(beta, eval);

        if (beta <= alpha) {
            break; // Prune
        }
    }

    return minEval;
}

inline std::vector<sf::Vector2i> AIEngine::getValidMoves(const Board& board) {
    std::vector<sf::Vector2i> validMoves;

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (board[i][j] == Player::Empty) {
                validMoves.emplace_back(j, i);
            }
        }
    }

    // Optional: Move ordering to improve alpha-beta pruning efficiency
    std::ranges::shuffle(validMoves, std::mt19937{std::random_device{}()});

    return validMoves;
}

#endif // AI_ENGINE_H
