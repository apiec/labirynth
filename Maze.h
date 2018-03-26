#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <iostream>
#include <vector>
#include "xy.h"

/** \brief Contains basic functionality of a maze.
 *
 * The maze is made up of square cells. Each cell can either be a wall or a passage.
 * A maze can either randomly generated or read from a txt file.
**/
class Maze {

    private:

        int width, height;

        bool** maze_grid;
        //the layout of the maze
        //0 - wall, 1 - passage

        bool treelike; //true = maze is treelike (from any point
        //there's only one way to any other point
        //false = multiple possible ways

        xy start;
        xy finish;
        //the start and the end of the maze

        int initiate_maze_grid();
        //creates a height x width boolean matrix
        //filled with 0s (walls)

        int add_wallstolist(xy cell, std::vector<xy>& wall_list);
        //adds walls of a cell to a wall_list
        bool can_bepassage(xy tocheck);
        //checks if a point with those coordinates can be added as a passage

        int generate_maze();
        //create a maze out of maze_grid

        int generate_maze(std::string filename);
        //reads a maze layout from a txt file

        int find_nearest_passage(xy& point);
        int random_startfinish();

        void initiate_startfinish();

    public:

        int print_maze_grid();
        //prints out the maze_grid as it is (in binary)

        int print_maze();
        //prints out the maze_grid as a readable maze in console

        int print_maze_totxt(std::string filename);
        //prints the maze to txt

        bool** get_maze_grid();
        int get_height();
        int get_width();
        xy get_start();
        xy get_finish();

        Maze(bool is_treelike = true);
        Maze(int h, int w, bool is_treelike = true);
        Maze(std::string mazetxt);
        ~Maze();



};

#endif // MAZE_H_INCLUDED
