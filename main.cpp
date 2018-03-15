#include "MazeMenu.h";
#include "MazeSolver.h"
#include "Maze.h"
#include "MyList.h"
#include "OrderedList.h"

#include <cstdlib>
#include <ctime>

int main(){
    srand(time(NULL));
    std::string fn = "test.txt";
    //Maze* maze = new Maze(fn);
    //Maze* maze = new Maze(100, 100);
    //maze->print_maze_grid();
    //maze->print_maze();
    //maze->print_maze_totxt("test.txt");
    //delete maze;
    /*
    std::cout << sizeof(Cell) << "\n";
    std::cout << sizeof(MazeSolver) << "\n";
    std::cout << sizeof(Maze) << "\n";
    std::cout << sizeof(xy) << "\n";
    */
   // MazeSolver* test = new MazeSolver(10, 20, false);
//    MazeSolver* test = new MazeSolver(fn);
//
//
//
//    //test->print_maze_grid();
//    test->print_maze();
//    test->print_maze_solution();
    MazeMenu test_menu;
    test_menu.main_menu();

    return 0;
}
