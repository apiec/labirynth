#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#include "xy.h"
#include "MyList.h"

class Cell {
    public:
        int g_cost;
        int h_cost;

        xy location;
        xy parent;

        MyList<xy> neighbors;

        Cell();
        ~Cell();

        void setup(int i, int j, int height, int width, xy finish, bool** maze_grid, Cell** cell_grid);
        void set_neighbors(int height, int width, xy finish, bool** maze_grid, Cell** cell_grid);

        int f_cost() const;

        bool operator< (const Cell& rhs) const;
        bool operator> (const Cell& rhs) const;
        bool operator==(const Cell& rhs) const;
        bool operator!=(const Cell& rhs) const;
};

#endif // CELL_H_INCLUDED
