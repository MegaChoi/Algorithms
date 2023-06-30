#include "Astar.h"
Astar::Astar(){
    for (int i = 0; i < Size::COLS; ++i)
    {
        for (int j = 0; j < Size::ROWS; ++j)
        {
            Grid[i][j] = Cell();
            Grid[i][j].set(i,j);
        }
    }
}

void Astar::reset(){
    for (int i = 0; i < Size::COLS; ++i)
    {
        for (int j = 0; j < Size::ROWS; ++j)
        {
            Grid[i][j] = Cell();
            Grid[i][j].set(i,j);
        }
    }
    
    while(!pq.empty()){
        pq.pop();
    }
}


// calcualte the distance from cell to goal cell
void Astar::setGoalCell(int col, int row){
    Grid[col][row].type = Type::GOAL;
    cout << Grid[col][row].col << Grid[col][row].row << endl;
    this->goalCell = Grid[col][row];

    // euclidean distance
    auto getH = [&](Cell & cell) ->void {
        cell.hValue = sqrt(pow(cell.row - goalCell.row,2) + pow(cell.col - goalCell.col,2));
    };


    // calcualte h distance for each cell 
    for (int i = 0; i < Size::COLS; ++i)
    {
        for (int j = 0; j < Size::ROWS; ++j)
        {  
            getH(Grid[i][j]);
        }
    };
    
}

void Astar::setStartCell(int col, int row){
    Grid[col][row].type = Type::START;
    Grid[col][row].distance = 0;
    this->pq.push(&Grid[col][row]);
}

// void Astar::render(RectangleShape & cell, RenderWindow& window){
//     Render::draw(cell, window, Grid);
// }

// void Astar::setWall(int col, int row){
//     if(Grid[col][row].type != Type::START && Grid[col][row].type != Type::GOAL)
//     Grid[col][row].type = Type::WALL;
// }




void Astar::updateMap(bool & goalFound) {

    Cell * curr = pq.top();

    // combinations of neighbouring indexes
    int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
    int dc[] = {0, 1, 0, -1, -1, 1, 1, -1};
    // track if any of the 4 adjacent cells are WALLs
    bool wall[] = {0, 0, 0, 0};

    // udpate distance for diagonal cells
    auto updateDistance = [&](Cell * cell) ->void {
        double newDist = curr->distance + 1;
        cell->distance = newDist;
        if(newDist < cell->distance)
            cell->distance = newDist;

        // update the f value
        cell->fValue = cell->hValue + cell->distance;
    };

    // update distance for vertical and horizontal cells
    auto updateDiagDistance = [&](Cell * cell) ->void {
        double newDist = sqrt(2) + curr->distance;
        cell->distance = newDist;
        if(newDist < cell->distance)
            cell->distance = newDist;
        // update the f value
        cell->fValue = cell->hValue + cell->distance;
    };

    // check if the cell is out of bounds
    auto isValidCell = [](int& newCol, int& newRow) ->bool {
        return (newRow >= 0 && newRow < 36 && newCol >= 0 && newCol < 64);
    };

    // update the type for for cells
    auto updateCell = [&](int& newCol, int& newRow, bool diagonal) -> Type {
        Type type = VISITED;

        // check if this cell is a valid position
        if (isValidCell(newCol, newRow)) {
            // 
            Cell * cell = &Grid[newCol][newRow];
            type = cell->type;

            // skip visited and wall cells
            if (type != WALL && type != VISITED){
                // if cell is goal trace the path
                if (type == GOAL){
                    goalFound = true;
                    cell->prev = curr;
                    // goalFound = true;
                    path(cell);
                    return type;
                }
                // update distance
                else if (type == EMPTY){
                    if (diagonal){
                        updateDiagDistance(cell);
                    }else{
                        updateDistance(cell);
                    }
                    pq.push(cell);
                    cell->type = Type::VISITED;
                    cell->prev = curr;
                }
            }
        }
        return type ;
    };
    // check 4 adjacent cells first
    for (int i = 0; i < 4; i++) {
        int newCol = curr->col + dr[i];
        int newRow = curr->row + dc[i];
        Type type = updateCell(newCol, newRow, false);

        if ( type == WALL)
            wall[i] = true;
        else if ( type == GOAL){
            return;
        }
        
    }

    // check 4 diagonal cells afterward
    for (int i = 4; i < 8; i++) {
        int newCol = curr->col + dr[i];
        int newRow = curr->row + dc[i];
        
        switch (i){
            case 4:
                if(!wall[0] && !wall[3])
                    updateCell(newCol, newRow, true);
                break;
            case 5:
                if(!wall[0] && !wall[1])
                    updateCell(newCol, newRow, true);
                break;
            case 6:
                if(!wall[1] && !wall[2])
                    updateCell(newCol, newRow, true);
                break;
            case 7:
                if(!wall[2] && !wall[3])
                    updateCell(newCol, newRow, true);
                break;
        }
    }
    pq.pop();
}


void Astar::path(Cell * cell) {
    Cell * temp = cell; 
    cell = cell->prev;
    while (cell->type != START) {
        cell->type = PATH;
        cell = cell->prev;
    }
}


Astar::~Astar()
{
}