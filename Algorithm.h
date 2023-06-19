#ifndef ALGO_H
#define ALGO_H

#include "Cell.hpp"
#include <math.h>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <functional>

struct compareFunc {
    bool operator()(Cell const* a, Cell const* b);
};
class Algorithm {
protected:
    Cell goalCell;
    std::priority_queue<Cell*, std::vector<Cell*>, compareFunc> pq;

public:
    Algorithm();
    ~Algorithm();
    void virtual updateMap(Map::Grid<Cell>& Grid, bool& totalVisited);
    void virtual path(Cell * cell);
    void virtual setGoalCell(Cell & startCell, Map::Grid<> & Grid);
    void virtual setStartCell(Cell & startCell);
    bool virtual isValidCell(int row, int col);
};

#endif

