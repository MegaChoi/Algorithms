#ifndef ASTAR_H
#define ASTAR_H

#include "Cell.hpp"
#include <math.h>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <functional>

struct compareFunc {
    bool operator()(Cell const* a, Cell const* b)
    {
        return a->fValue > b->fValue;
    }
};
class Astar {
private:
    Cell goalCell;
    std::priority_queue<Cell*, std::vector<Cell*>, compareFunc> pq;

public:
    Astar();
    ~Astar();
    void updateMap(Map::Grid<Cell>& Grid, bool& totalVisited);
    void path(Cell * cell);
    void setGoalCell(Cell & startCell, Map::Grid<> & Grid);
    void setStartCell(Cell & startCell);
    bool isValidCell(int row, int col);
};

#endif

