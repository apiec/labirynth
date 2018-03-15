#ifndef MAZEMENU_H
#define MAZEMENU_H
#include "MazeSolver.h"

class MazeMenu
{
    private:

        MazeSolver* maze_instance;
        int read_int(int low_bound, int high_bound, std::string val_name);
        std::string read_filename();
    public:

        void main_menu();
        void generation_menu();
        void txt_menu();
        void maze_loaded_menu();

        MazeMenu();
        ~MazeMenu();
};

#endif // MAZEMENU_H
