#ifndef ALGO_H
#define ALGO_H

#include "Cell.hpp"
#include <math.h>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <functional>


class Algorithm {
protected:
    Cell goalCell;
    Cell startCell;
public:
    void virtual updateMap(Map::Grid<Cell>& Grid, bool& totalVisited){};
    void virtual path(Cell * cell){};
    void virtual setStartCell(Cell& startCell){};
    void virtual setGoalCell(Cell & startCell, Map::Grid<> & Grid){};
};

#endif

