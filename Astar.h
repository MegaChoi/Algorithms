#ifndef ASTAR_H
#define ASTAR_H

#include "Algorithm.h"


class Astar : public Algorithm{
private:
    struct compareFunc {
        bool operator()(Cell const* a, Cell const* b)
        {
            return a->fValue > b->fValue;
        }
    };
    std::priority_queue<Cell*, std::vector<Cell*>, compareFunc> pq;
public:
    Astar();
    ~Astar();
    void updateMap(Map::Grid<Cell>& Grid, bool& totalVisited);
    void path(Cell * cell);
    void setGoalCell(Cell & startCell, Map::Grid<> & Grid);
    void setStartCell(Cell & startCell);
};

#endif

