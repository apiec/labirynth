#include "MazeSolver.h"
#include "Maze.h"
#include "Cell.h"
#include "OrderedList.h"

#include <cstdlib>
#include <cstring>

MazeSolver::MazeSolver(){
    this->maze = new Maze(30, 30, true);
    this->solution_found = this->a_star();
}

MazeSolver::MazeSolver(int h, int w, bool treelike){
    this->maze = new Maze(h, w, treelike);
    this->solution_found = this->a_star();
}
MazeSolver::MazeSolver(std::string filename){
    this->maze = new Maze(filename);
    this->solution_found = this->a_star();
}

MazeSolver::~MazeSolver(){
    delete maze;
    delete maze_print;
}

bool MazeSolver::a_star(){
    /**
    *   implementation of the A* algorithm
    *   return true if it finds the way
    *   return false if it does not
    *   https://en.wikipedia.org/wiki/A*_search_algorithm
    **/
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
    for(int i = 0; i < height; i++){
        delete [] cell_grid[i];
    }
    delete[] cell_grid;

    return false; //it only gets here if it doesn't find the end
}

void MazeSolver::reconstruct_path(Cell current, Cell** cell_grid){
    while(!path.empty()){
        path.pop_back();
    }
    while(current.parent.x > -1 && current.parent.y > -1){
        path.push_back(current.location);
        current = cell_grid[current.parent.x][current.parent.y];
    }
}

void MazeSolver::create_maze_print(){
    char passage = ' ';
    char wall    = 219;
    char pth     = 177;
    char strt    = 's';
    char fnsh    = 'e';
    int width    = maze->get_width();
    int height   = maze->get_height();

    bool** maze_grid = maze->get_maze_grid();

    maze_print = new char[width * height];

    for(int i = 0; i < width * height; i++){
        bool is_passage = maze_grid[i / width][i % width];
        if(is_passage == 1){
            maze_print[i] = passage;
        }else{
            maze_print[i] = wall;
        }
    }
    for(int i = 0; i < (int)path.size(); i++){
        int x = path[i].x;
        int y = path[i].y;
        maze_print[x * width + y] = pth;
    }
    xy start = maze->get_start();
    xy finish = maze->get_finish();
    maze_print[start.x * width + start.y] = strt;
    maze_print[finish.x * width + finish.y] = fnsh;
}

void MazeSolver::print_maze_solution(){
    create_maze_print();
    std::cout << "\n";
    int width = maze->get_width();
    int height = maze->get_height();
    for(int i = 0; i < width + 2; i++) std::cout << '*';
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

void MazeSolver::print_maze_grid(){
    maze->print_maze_grid();
}
void MazeSolver::print_maze(){
    maze->print_maze();
}
void MazeSolver::print_maze_totxt(std::string filename){
    maze->print_maze_totxt(filename);
}

bool MazeSolver::get_solution_found(){
    return this->solution_found;
}

