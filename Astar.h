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
    void updateMap(bool & goalFound) override;
    void path(Cell * cell) override;
    void setStartCell(int col, int row) override;
    void setGoalCell(int col, int row) override;
    void render(RectangleShape & cell, RenderWindow& window) override;
    void setWall(int col, int row) override;
    void reset() override;
};

#endif

