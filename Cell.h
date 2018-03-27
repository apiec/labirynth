#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#include "xy.h"
#include "MyList.h"

/**
 * Cells class used in the A* search algorithm. Each cell is a point of a Maze.
**/
class Cell {
    public:
        int g_cost; /**< The cost of traveling from the start to this cell. */
        int h_cost; /**< The heuristic. The expected shortest way to get to the finish.*/

        xy location; /**< The position of this cell. */
        xy parent;   /**< The position of this cell's parent. */

        MyList<xy> neighbors; /**< The list of the positions of all neighbor cells. */

        Cell();
        ~Cell();

        int f_cost() const;

        void setup(int i, int j, xy finish);

        void set_neighbors(int height, int width, bool** maze_grid, Cell** cell_grid);

        bool operator< (const Cell& rhs) const;
        bool operator> (const Cell& rhs) const;
        bool operator==(const Cell& rhs) const;
        bool operator!=(const Cell& rhs) const;
};

#endif // CELL_H_INCLUDED
