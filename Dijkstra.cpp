#include "Dijkstra.h"
Dijkstra::Dijkstra(){
    
}

void Dijkstra::startCell(int y, int x){
    this->myQueue.emplace(y,x);
}


void Dijkstra::updateMap(Map::Grid<> & Grid, bool & totalVisited) {
    std::pair<int, int> curr = myQueue.front();
    // Explore the neighboring cells
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int newRow = curr.first + dr[i];
        int newCol = curr.second + dc[i];
        
        if (isValidCell(newRow, newCol)) {
            Cell& cell = Grid[newCol][newRow];
            Type type = cell.type;
            if (type == GOAL){
                totalVisited = true;
                return;
            }
            if (type != VISITED){
                if (type == EMPTY) {
                    myQueue.emplace(newRow, newCol);
                    cell.type = Type::VISITED;
                }
            }
        }
    }
    myQueue.pop();
}

// Function to check if a given cell is valid within the grid
bool Dijkstra::isValidCell(int row, int col) {
    return (row >= 0 && row < 36 && col >= 0 && col < 64);
}

Dijkstra::~Dijkstra()
{
}