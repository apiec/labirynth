#ifndef MAZESOLVER_H_INCLUDED
#define MAZESOLVER_H_INCLUDED

#include "xy.h"
#include "Maze.h"
#include "Cell.h"
#include <vector>

class MazeSolver {

    private:

        Maze* maze;
        std::vector<xy> path;
        char* maze_print;
        bool solution_found;

        void reconstruct_path(Cell current, Cell** cell_grid);
        bool a_star();

        void create_maze_print();

    public:
        void print_maze_grid();
        void print_maze();
        void print_maze_solution();
        void print_maze_totxt(std::string filename);
        bool get_solution_found();

        //constructors
        MazeSolver();
        MazeSolver(int h, int w, bool treelike = true);
        MazeSolver(std::string filename);

        //deconstructor
        ~MazeSolver();


};


#endif // MAZESOLVER_H_INCLUDED
