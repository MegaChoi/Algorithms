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
    void virtual updateMap(bool & goalFound){};
    void virtual path(Cell * cell){};
    void virtual setStartCell(int col, int row){};
    void virtual setGoalCell(int col, int row){};
    void virtual render(RectangleShape & cell, RenderWindow& window){};
    void virtual setWall(int col, int row){};
    void virtual reset(){};
};

#endif

