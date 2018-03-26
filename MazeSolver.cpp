#include "MazeSolver.h"
#include "Maze.h"
#include "Cell.h"
#include "OrderedList.h"

#include <cstdlib>
#include <cstring>

/**
 * Default constructor.
**/
MazeSolver::MazeSolver(){
    //create the Maze object
    this->maze = new Maze(30, 30, true);

    //calls the a_star() search algorithm and passes whether it's been
    //successful or not to the soultion_found variable
    this->solution_found = this->a_star();
    this->maze_print = NULL;
}

/**
 * Constructor. Creates the Maze object and calls the a_star search algorithm on that maze.
**/
MazeSolver::MazeSolver(int h, int w, bool treelike){
    //create the Maze object
    this->maze = new Maze(h, w, treelike);

    //calls the a_star() search algorithm and passes whether it's been
    //successful or not to the soultion_found variable
    this->solution_found = this->a_star();
    this->maze_print = NULL;
}

/**
 * Constructor. Takes a filename string as an input. Reads the maze off that txt file and call the a_star algorithm.
**/
MazeSolver::MazeSolver(std::string filename){
    //create the Maze object
    this->maze = new Maze(filename);

    //calls the a_star() search algorithm and passes whether it's been
    //successful or not to the soultion_found variable
    this->solution_found = this->a_star();
    this->maze_print = NULL;
}

/**
 * Destructor. deletes the maze and maze_print.
**/
MazeSolver::~MazeSolver(){
    delete this->maze;
    delete this->maze_print;
}

/**
 * Implementation of the A* search algorithm.
 * Return true if it finds the path from start to finish.
 * Return false if it does not.
 * https://en.wikipedia.org/wiki/A*_search_algorithm
**/
bool MazeSolver::a_star(){

    int height       = this->maze->get_height();
    int width        = this->maze->get_width();
    bool** maze_grid = this->maze->get_maze_grid();
    xy start         = this->maze->get_start();
    xy finish        = this->maze->get_finish();

    //creating a maze out of cells
    //setting up the cells
    Cell** cell_grid = new Cell*[height];

    for(int i = 0; i < height; i++){
        cell_grid[i] = new Cell[width];
        for(int j = 0; j < width; j++){
            cell_grid[i][j].setup(i, j, height, width, finish, maze_grid, cell_grid);
        }
    }
    //setting the neigbors of the cells
    //the entire cell grid needed to be initialized
    //for the neighbors to be added so we do that in a separate loop
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cell_grid[i][j].set_neighbors(height, width, finish, maze_grid, cell_grid);
        }
    }

    //if closed_set[x][y] == true then it is in closed set
    bool** closed_set = new bool*[height];
    for(int i = 0; i < height; i++){
        closed_set[i] = new bool[width];
        for(int j = 0; j < width; j++){
            closed_set[i][j] = false;
        }
    }
    //initalizing the starting cell and adding it to the open set
    OrderedList<Cell> open_set;
    cell_grid[start.x][start.y].g_cost = 0;
    open_set.append(cell_grid[start.x][start.y]);

    //while there are cells in the open set
    while(!open_set.empty()){
        //choose the cell with the lowest f_score and remove it from the open set
        Cell best = open_set.front();
        open_set.pop_front();
        path.push_back(best.location);

        if(best.location == finish){
            //reconstructing the path and finishing
            reconstruct_path(best, cell_grid);
            //delete the dynamically allocated recources
            for(int i = 0; i < height; i++){
                delete [] cell_grid[i];
            }
            delete[] cell_grid;
            //path found => return true
            return true;
        }
        closed_set[best.location.x][best.location.y] = true; //adding the cell to the closed set
        while(!best.neighbors.empty()){
            xy neighbor = best.neighbors.back();
            best.neighbors.pop_back();
            int xn = neighbor.x; //neighbor x and y
            int yn = neighbor.y;
            if(!closed_set[xn][yn]){
                //checking if the new g_cost is lower then the g_cost already in the cell
                int new_g = best.g_cost + 1;
                if(!open_set.contains(cell_grid[xn][yn])){
                    cell_grid[xn][yn].g_cost = new_g;
                    cell_grid[xn][yn].parent = best.location;
                    open_set.append(cell_grid[xn][yn]);
                }else if(new_g < cell_grid[xn][yn].g_cost){
                    cell_grid[xn][yn].g_cost = new_g;
                    cell_grid[xn][yn].parent = best.location;
                }
            }
        }
    }
    //delete the dynamic resources
    for(int i = 0; i < height; i++){
        delete [] cell_grid[i];
    }
    delete[] cell_grid;
    //it only gets here if it doesn't find the end
    //no path => return false
    return false;
}

/**
 * Reconstructs the path from the cell that is passed as the argument.
 * It follows it until a cell that has negative parent coordinates is reached.
**/
void MazeSolver::reconstruct_path(Cell current, Cell** cell_grid){
    //make sure that path is empty
    while( !path.empty() ){
        path.pop_back();
    }
    //follow the path until the start is reached
    while( current.parent.x > -1 && current.parent.y > -1 ){
        path.push_back(current.location);
        current = cell_grid[current.parent.x][current.parent.y];
    }
}

/**
 * Creates the
**/
void MazeSolver::create_maze_print(){
    //if the maze_print has already been created leave
    if(maze_print) return;
    //setting up some constants
    const char passage = ' ';
    const char wall    = 219;
    const char pth     = 177;
    const char strt    = 's';
    const char fnsh    = 'e';
    //copying for ease of use
    const int width    = maze->get_width();
    const int height   = maze->get_height();
    bool** maze_grid = maze->get_maze_grid();

    //maze_print holds the graphical representation of the maze
    maze_print = new char[width * height];

    //sets up the walls and paths in the maze_print
    for(int i = 0; i < width * height; i++){
        bool is_passage = maze_grid[i / width][i % width];
        if(is_passage == 1){
            maze_print[i] = passage;
        }else{
            maze_print[i] = wall;
        }
    }
    //fills in the path
    for(int i = 0; i < (int)path.size(); i++){
        int x = path[i].x;
        int y = path[i].y;
        maze_print[x * width + y] = pth;
    }
    //sets up the start and finish cells
    xy start = maze->get_start();
    xy finish = maze->get_finish();
    maze_print[start.x * width + start.y] = strt;
    maze_print[finish.x * width + finish.y] = fnsh;
}

/**
 * Prints the graphical representation of the maze and its solution.
**/
void MazeSolver::print_maze_solution(){
    create_maze_print();
    std::cout << "\n";
    int width = maze->get_width();
    int height = maze->get_height();
    for(int i = 0; i < width + 2; i++){std::cout << '*';}
    std::cout << "\n*";
    for(int i = 0; i < width * height; i++){
            std::cout << maze_print[i];
            if( (i + 1) % width == 0 ){
                std::cout << "*\n*";
            }
    }
    for(int i = 0; i < width + 1; i++) std::cout << '*';
    std::cout << std::endl;
}
/**
 * Calls the maze's print_maze_grid method.
**/
void MazeSolver::print_maze_grid(){
    this->maze->print_maze_grid();

}
/**
 * Calls maze's print_maze method.
**/
void MazeSolver::print_maze(){
    this->maze->print_maze();
}

/**
 * Calls maze's print_maze_totxt method.
**/
void MazeSolver::print_maze_totxt(std::string filename){
    this->maze->print_maze_totxt(filename);
}

/**
 * Returns whether the path from the start to finish points
 * has been found. Defaults to false.
**/
bool MazeSolver::get_solution_found(){
    return this->solution_found;
}

