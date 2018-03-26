
#include "MazeMenu.h"
#include <cstdlib>
#include <ctime>
/** \brief This program solves mazes.
 *
 * This is a program that can generate mazes or read them off a txt file and solve them.
 *
 * It has a simple console menu that prompts the user for whether they want to generate
 * the maze randomly or read it off a txt file. It can display the mazes,
 * display them with a solution, save the maze to a txt file.
**/
int main(){

    srand(time(NULL));

    MazeMenu test_menu;
    test_menu.main_menu();

    return 0;
}
