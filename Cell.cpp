#include "Cell.h"
#include <climits>
/**
 * Constructor.
**/
Cell::Cell(){
    this->g_cost     = INT_MAX;
    this->h_cost     = -1;
    this->location.x = -1;
    this->location.y = -1;
    this->parent.x   = -1;
    this->parent.y   = -1;
}

/**
 * Destructor
**/
Cell::~Cell(){
}

/**
 * Returns the f_cost = g_cost + h_cost
**/
int Cell::f_cost() const {
    return this->g_cost + this->h_cost;
}
/**
 * An initial setup. Sets up the location of the Cell and the h_cost.
**/
void Cell::setup(int i, int j, xy finish){
    this->location.x = i;
    this->location.y = j;
    this->h_cost     = abs(i - finish.x) + abs(j - finish.y);//the heuristic - Manhattan distance to finish
    this->g_cost     = INT_MAX - 100000;
    this->parent.x   = -1;
    this->parent.y   = -1;
}

/**
 * \brief Adds the neighbors of a cell to the neighbors list.
 * Checks the maze_grid if the neighbor is a wall or not and then adds it if it is a passage.
**/
void Cell::set_neighbors(int height, int width, bool** maze_grid, Cell** cell_grid){
    int i = this->location.x;
    int j = this->location.y;
    //bottom
    if(i + 1 < height && maze_grid[i + 1][j] == 1){
        xy tmp = cell_grid[i + 1][j].location;
        this->neighbors.push_back(tmp);
    }
    //top
    if(i > 0 && maze_grid[i - 1][j] == 1){
        xy tmp = cell_grid[i - 1][j].location;
        this->neighbors.push_back(tmp);
    }
    //right
    if(j + 1 < width && maze_grid[i][j + 1] == 1){
        xy tmp = cell_grid[i][j + 1].location;
        this->neighbors.push_back(tmp);
    }
    //left
    if(j > 0 && maze_grid[i][j - 1] == 1){
        xy tmp = cell_grid[i][j - 1].location;
        this->neighbors.push_back(tmp);
    }
}

/**
 * The operators are overloaded because the Cells need to be ordered in the OrderedList
 * The Cell is less than another Cell when their f_cost is less than the other Cell's f_cost.
**/
bool Cell::operator< (const Cell& rhs) const{
    return this->f_cost() < rhs.f_cost();
}
/**
 * The operators are overloaded because the Cells need to be ordered in the OrderedList
 * The Cell is bigger than another Cell when their f_cost is bigger than the other Cell's f_cost.
 */
bool Cell::operator> (const Cell& rhs) const{
    return this->f_cost() > rhs.f_cost();
}

/**
 * The operators are overloaded because the Cells need to be ordered in the OrderedList
 * Two Cells are equal when their locations are equal.
 * It is so because the algorithm needs to check whether a Cell with a given location is in the open set.
 */
bool Cell::operator==(const Cell& rhs) const{
    return this->location == rhs.location;
}
bool Cell::operator!=(const Cell& rhs) const {
    return !(*this == rhs);
}
