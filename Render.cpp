#include "Render.h"

void Render::draw(RectangleShape & cell, RenderWindow& window, Map::Grid<> & Grid) {
    // Draw the grid
    for (int i = 0; i < Size::COLS; ++i)
    {
        for (int j = 0; j < Size::ROWS; ++j)
        {   
            switch(Grid[i][j].type){
                case Type::START:
                    cell.setFillColor(sf::Color::Red);
                    break;
                case Type::EMPTY:
                    cell.setFillColor(sf::Color::White);
                    break;
                case Type::GOAL:
                    cell.setFillColor(sf::Color::Green);
                    break;
                case Type::VISITED:
                    cell.setFillColor(sf::Color::Cyan);
                    break;
                case Type::WALL:
                    cell.setFillColor(sf::Color::Black);
                    break;
                case Type::PATH:
                    cell.setFillColor(sf::Color::Yellow);
                    break;
            }
            cell.setPosition(i * Size::CELL_SIZE, j * Size::CELL_SIZE);
            window.draw(cell);
        }
    }
    
}