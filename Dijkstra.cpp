#include "Dijkstra.h"
Dijkstra::Dijkstra(){
    
}

void Dijkstra::startCell(int x, int y){
    this->myQueue.emplace(x,y);
    this->start = pair(x,y);
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
            if (type == WALL){
                cell.distance = 0;
            }
            if (type == GOAL){
                totalVisited = true;
                path(Grid);
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


void Dijkstra::path(Map::Grid<> & Grid) {
    std::pair<int, int> curr = start;
    Cell& cell = Grid[curr.first][curr.second];

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (cell.type != GOAL) {
        double min = 1000;
        std::pair<int, int> nextCell;

        for (int i = 0; i < 4; i++) {
            int newRow = curr.first + dr[i];
            int newCol = curr.second + dc[i];
            if (isValidCell(newRow, newCol)){
                Cell& temp = Grid[newCol][newRow];

                if (temp.distance < min) {
                    min = temp.distance;
                    nextCell = std::make_pair(newRow, newCol);
                }
            }
        }

        curr = nextCell;
        cell = Grid[curr.first][curr.second];
        std::cout << curr.first << curr.second << std::endl;
        if (cell.type != GOAL) {
            cell.type = PATH;
        }
    }
}
// Function to check if a given cell is valid within the grid
bool Dijkstra::isValidCell(int row, int col) {
    return (row >= 0 && row < 36 && col >= 0 && col < 64);
}

Dijkstra::~Dijkstra()
{
}