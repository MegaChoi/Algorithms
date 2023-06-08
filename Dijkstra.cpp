#include "Dijkstra.h"
Dijkstra::Dijkstra(){
    this->myQueue.emplace(0,0);
}

void Dijkstra::updateMap(Map::Grid<> & Grid, int & totalVisited){
    std::pair<int, int> curr = myQueue.front();
    // Explore the neighboring cells
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int newRow = curr.first + dr[i];
        int newCol = curr.second + dc[i];
        if (isValidCell(newRow, newCol) && Grid[newCol][newRow].type != Type::VISITED) {
            myQueue.emplace(newRow,newCol);
            Grid[newCol][newRow].type = Type::VISITED;
            totalVisited ++;
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