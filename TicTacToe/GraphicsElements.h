// GraphicsElements.h
#ifndef GRAPHICS_ELEMENTS_H
#define GRAPHICS_ELEMENTS_H

#include <SFML/Graphics.hpp>

class GraphicsElements {
public:
    static void drawGrid(sf::RenderWindow& window, int gridSize, int cellSize);
    static void drawCross(sf::RenderWindow& window, int x, int y, int cellSize);
    static void drawCircle(sf::RenderWindow& window, int x, int y, int cellSize);
};

inline void GraphicsElements::drawGrid(sf::RenderWindow& window, const int gridSize, const int cellSize) {
    const auto gridColor = sf::Color(50, 50, 50);
    sf::RectangleShape line;

    // Горизонтальные линии
    for (int i = 1; i < gridSize; ++i) {
        line.setSize(sf::Vector2f(gridSize * cellSize, 2));
        line.setFillColor(gridColor);
        line.setPosition(0, i * cellSize);
        window.draw(line);
    }

    // Вертикальные линии
    for (int i = 1; i < gridSize; ++i) {
        line.setSize(sf::Vector2f(2, gridSize * cellSize));
        line.setFillColor(gridColor);
        line.setPosition(i * cellSize, 0);
        window.draw(line);
    }
}

inline void GraphicsElements::drawCross(sf::RenderWindow& window, const int x, const int y, const int cellSize) {
    const sf::Color crossColor = sf::Color::Red;
    const float padding = cellSize * 0.2f;

    const sf::Vertex line1[] = {
        sf::Vertex(sf::Vector2f(x + padding, y + padding), crossColor),
        sf::Vertex(sf::Vector2f(x + cellSize - padding, y + cellSize - padding), crossColor)
    };

    const sf::Vertex line2[] = {
        sf::Vertex(sf::Vector2f(x + padding, y + cellSize - padding), crossColor),
        sf::Vertex(sf::Vector2f(x + cellSize - padding, y + padding), crossColor)
    };

    window.draw(line1, 2, sf::Lines);
    window.draw(line2, 2, sf::Lines);
}

inline void GraphicsElements::drawCircle(sf::RenderWindow& window, const int x, const int y, const int cellSize) {
    sf::CircleShape circle;
    const float radius = (cellSize * 0.4f);
    circle.setRadius(radius);
    circle.setOutlineThickness(5);
    circle.setOutlineColor(sf::Color::Blue);
    circle.setFillColor(sf::Color::Transparent);

    circle.setPosition(x + cellSize * 0.1f, y + cellSize * 0.1f);
    window.draw(circle);
}

#endif // GRAPHICS_ELEMENTS_H
