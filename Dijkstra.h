#ifndef D
#define D
#include "Cell.hpp"
#include "Astar.hpp"
#include <vector>
#include <queue>
#include <climits>
class Dijkstra
{
private:
    std::queue<std::pair<int, int>> myQueue;
public:
    Dijkstra();
    ~Dijkstra();
    void updateMap(Map::Grid<> & Grid, int & totalVisited);
    bool isValidCell(int row, int col);
};

#endif

