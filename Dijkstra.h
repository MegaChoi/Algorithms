#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Algorithm.h"
class Dijkstra : public Algorithm {
protected:
    struct compareFunc {
        bool operator()(Cell const* a, Cell const* b)
        {
            return a->distance > b->distance;
        }
    };
    std::priority_queue<Cell*, std::vector<Cell*>, compareFunc> pq;
public:
    Dijkstra() : Algorithm(){};
    ~Dijkstra();
    void updateMap(Map::Grid<Cell>& Grid, bool& totalVisited);
    void path(Cell * cell);
    void setStartCell(Cell& startCell);
};

#endif
