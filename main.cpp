#include "MazeMenu.h"
#include "MazeSolver.h"
#include "Maze.h"
#include "MyList.h"
#include "OrderedList.h"

#include <cstdlib>
#include <ctime>

int main(){

    srand(time(NULL));

    MazeMenu test_menu;
    test_menu.main_menu();

    return 0;
}
