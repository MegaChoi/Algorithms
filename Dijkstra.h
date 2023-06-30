#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Algorithm.h"

class Dijkstra : public Algorithm {
protected:
    struct compareFunc {
        bool operator()(Cell const *a, Cell const *b) {
            return a->distance > b->distance;
        }
    };

    std::priority_queue<Cell *, std::vector<Cell *>, compareFunc> pq;

public:
    Dijkstra();
    ~Dijkstra();

    void updateMap(bool &goalFound) override;
    void path(Cell *cell) override;
    void setStartCell(int col, int row) override;
    void setGoalCell(int col, int row) override;
    void reset() override;
};

#endif