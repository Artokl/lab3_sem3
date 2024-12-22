// GameWindow.h
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SFML/Graphics.hpp>
#include "GraphicsElements.h"
#include "GameLogic.h"
#include "AIEngine.h"

class GameWindow {
public:
    GameWindow();
    void run();

private:
    sf::RenderWindow window;
    static constexpr int gridSize = 5;
    static constexpr int cellSize = 100;
    static constexpr int windowSize = gridSize * cellSize;

    Board board;
    Player currentPlayer;
    bool gameOver;

    void processEvents();
    void render();
    void handleMouseClick(int x, int y);
    void checkGameState();
    void makeAIMove();
};

inline GameWindow::GameWindow()
    : window(sf::VideoMode(windowSize, windowSize), "Tic Tac Toe", sf::Style::Close),
board{{{Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
 {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
 {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
 {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
 {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty}}},
      currentPlayer(Player::Cross),
      gameOver(false) {}

inline void GameWindow::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

inline void GameWindow::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (!gameOver && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }
}

inline void GameWindow::render() {
    window.clear(sf::Color::White);
    GraphicsElements::drawGrid(window, gridSize, cellSize);

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            int x = j * cellSize;
            int y = i * cellSize;
            if (board[i][j] == Player::Cross) {
                GraphicsElements::drawCross(window, x, y, cellSize);
            } else if (board[i][j] == Player::Circle) {
                GraphicsElements::drawCircle(window, x, y, cellSize);
            }
        }
    }

    window.display();
}

inline void GameWindow::handleMouseClick(int x, int y) {
    const int col = x / cellSize;

    if (const int row = y / cellSize; board[row][col] == Player::Empty) {
        board[row][col] = currentPlayer;
        checkGameState();

        if (!gameOver) {
            makeAIMove();
        }
    }
}

inline void GameWindow::checkGameState() {
    if (GameLogic::checkWin(board, currentPlayer)) {
        gameOver = true;
        // Display win message
        std::cout << "Player " << (currentPlayer == Player::Cross ? "Cross" : "Circle") << " wins!\n";
        window.close();
    } else if (GameLogic::isBoardFull(board)) {
        gameOver = true;
        // Display draw message
        std::cout <<"It's a draw!\n";
        window.close();
    }
    currentPlayer = (currentPlayer == Player::Cross) ? Player::Circle : Player::Cross;
}

inline void GameWindow::makeAIMove() {
    if (const sf::Vector2i bestMove = AIEngine::findBestMove(board, Player::Circle); bestMove.x != -1 && bestMove.y != -1) {
        board[bestMove.y][bestMove.x] = Player::Circle;
        checkGameState();
    }
}

#endif // GAME_WINDOW_H
