#include "Dijkstra.h"
Dijkstra::Dijkstra(){
    
}

void Dijkstra::setStartCell(Cell & startCell){
    this->pq.push(&startCell);
}


void Dijkstra::updateMap(Map::Grid<> & Grid, bool & goalFound) {
    Cell * curr = pq.top();
    // Explore the neighboring cells
    int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
    int dc[] = {0, 1, 0, -1, -1, 1, 1, -1};

    for (int i = 0; i < 8; i++) {
        int newCol = curr->col + dr[i];
        int newRow = curr->row + dc[i];
        
        if (isValidCell(newCol, newRow)) {
            Cell * cell = &Grid[newCol][newRow];
            Type type = cell->type;
            if (type == WALL){
                continue;
            }
            if (type == GOAL){
                cell->prev = curr;
                goalFound = true;
                path(cell);
                return;
            }

            double newDist = 0;
            if (i > 3){
                // update distance for diagonal cells
                newDist = sqrt(2) + curr->distance;
            }else{
                newDist = curr->distance + 1;
            }

            if(newDist < cell->distance)
                cell->distance = newDist;

            
            if (type == EMPTY && type != VISITED){
                pq.push(cell);
                cell->type = Type::VISITED;
                cell->prev = curr;
            }
        }
    }
    pq.pop();
}
// Function to check if a given cell is valid within the grid
bool Dijkstra::isValidCell( int col, int row) {
    return (row >= 0 && row < 36 && col >= 0 && col < 64);
}

void Dijkstra::path(Cell * cell) {
    Cell * temp = cell; 
    while (cell->type != START) {
        cout << cell->col << " " << cell->row << endl;
        cell->type = PATH;
        cell = cell->prev;
    }
}


Dijkstra::~Dijkstra()
{
}