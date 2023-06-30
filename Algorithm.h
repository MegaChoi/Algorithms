#ifndef ALGO_H
#define ALGO_H

#include "Cell.hpp"
#include <math.h>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <functional>
#include "Render.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Algorithm {
protected:
    Map::Grid<> Grid;
    Cell goalCell;
    Cell startCell;

public:
    virtual void updateMap(bool &goalFound) {};
    virtual void path(Cell *cell) {};
    virtual void setStartCell(int col, int row) {};
    virtual void setGoalCell(int col, int row) {};
    virtual void render(RectangleShape &cell, RenderWindow &window) {
        Render::draw(cell, window, Grid);
    };
    virtual void setWall(int col, int row) {
        if (Grid[col][row].type != Type::START && Grid[col][row].type != Type::GOAL)
            Grid[col][row].type = Type::WALL;
    };
    virtual void reset() {};
};

#endif