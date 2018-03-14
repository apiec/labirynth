#include "Cell.h"
#include <climits>

Cell::Cell(){
    this->g_cost     = INT_MAX;
    this->h_cost     = -1;
    this->location.x = -1;
    this->location.y = -1;
    this->parent.x   = -1;
    this->parent.y   = -1;
}

Cell::~Cell(){
}

int Cell::f_cost() const {
    return this->g_cost + this->h_cost;
}

void Cell::setup(int i, int j, int height, int width, xy finish, bool** maze_grid, Cell** cell_grid){
    cell_grid[i][j].location.x = i;
    cell_grid[i][j].location.y = j;
    cell_grid[i][j].h_cost     = abs(i - finish.x) + abs(j - finish.y);//the heuristic - Manhattan distance to finish
    cell_grid[i][j].g_cost     = INT_MAX - 100000;
    cell_grid[i][j].parent.x   = -1;
    cell_grid[i][j].parent.y   = -1;
}
void Cell::set_neighbors(int height, int width, xy finish, bool** maze_grid, Cell** cell_grid){
    //adding neighbors to the neighbors list
    int i = this->location.x;
    int j = this->location.y;
    if(i + 1 < height && maze_grid[i + 1][j] == 1){
        xy tmp = cell_grid[i + 1][j].location;
        cell_grid[i][j].neighbors.push_back(tmp);
    }
    if(i > 0 && maze_grid[i - 1][j] == 1){
        xy tmp = cell_grid[i - 1][j].location;
        cell_grid[i][j].neighbors.push_back(tmp);
    }
    if(j + 1 < width && maze_grid[i][j + 1] == 1){
        xy tmp = cell_grid[i][j + 1].location;
        cell_grid[i][j].neighbors.push_back(tmp);
    }
    if(j > 0 && maze_grid[i][j - 1] == 1){
        xy tmp = cell_grid[i][j - 1].location;
        cell_grid[i][j].neighbors.push_back(tmp);
    }
}

//Cells are ordered according to their f_cost
bool Cell::operator< (const Cell& rhs) const{
    return this->f_cost() < rhs.f_cost();
}
bool Cell::operator> (const Cell& rhs) const{
    return this->f_cost() > rhs.f_cost();
}

//Cells are equal or not equal if their locations are the same or different
bool Cell::operator==(const Cell& rhs) const{
    return this->location == rhs.location;//(this->location.x == rhs.location.x) && (this->location.y == rhs.location.y);
}
bool Cell::operator!=(const Cell& rhs) const {
    return !(*this == rhs);
}
