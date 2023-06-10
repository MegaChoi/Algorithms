#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Cell.hpp"
#include "Astar.hpp"
#include <math.h>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <functional>

struct compareFunc {
    bool operator()(Cell const* a, Cell const* b)
    {
        return a->distance > b->distance;
    }
};
class Dijkstra {
private:
    Cell startCell;
    std::priority_queue<Cell*, std::vector<Cell*>, compareFunc> pq;

public:
    Dijkstra();
    ~Dijkstra();
    void updateMap(Map::Grid<Cell>& Grid, bool& totalVisited);
    void path(Cell * cell);
    void setStartCell(Cell& startCell);
    bool isValidCell(int row, int col);
};

#endif
