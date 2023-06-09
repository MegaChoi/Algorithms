#ifndef D
#define D
#include "Cell.hpp"
#include "Astar.hpp"
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
class Dijkstra
{
private:
    pair<int, int> start;
    std::queue<std::pair<int, int>> myQueue;
public:
    Dijkstra();
    ~Dijkstra();
    void updateMap(Map::Grid<> & Grid, bool & totalVisited);
    void path(Map::Grid<> & Grid);
    void startCell(int y, int x);
    bool isValidCell(int row, int col);
};

#endif

