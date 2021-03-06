#include "Maze.h"

#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>

#include "MyList.h"

/**
 * Default constructor.
**/
Maze::Maze(bool is_treelike){
    this->width = 100;
    this->height = 40;
    this->initiate_startfinish();
    this->treelike = is_treelike;
    this->initiate_maze_grid();
    this->generate_maze();
}

/**
 * Constructor with width and height as parameters. Also takes the treelike parameter.
 * When treelike is set to true the maze generator creates a maze where there is
 * only one possible from any given point to any other point.
**/
Maze::Maze(int h, int w, bool is_treelike): width(w), height(h) {
    this->initiate_startfinish();
    this->treelike = is_treelike;
    this->initiate_maze_grid();
    this->generate_maze();
}
/**
 * Constructor that takes a filename with maze information as a parameter.
**/
Maze::Maze(std::string mazetxt){
    this->initiate_startfinish();
    this->generate_maze(mazetxt);
}

/**
 * Destructor.
**/
Maze::~Maze(){
    //deleting maze_grid
    for(int i = 0; i < height; i++){
        delete[] this->maze_grid[i];
    }
    delete[] this->maze_grid;
}

/**
 * Sets start and finish coordinates to (-1, -1).
**/
void Maze::initiate_startfinish(){
    this->start.x = -1;
    this->start.y = -1;
    this->finish.x = -1;
    this->finish.y = -1;
}

/**
 * Creates a boolean two-dimensional (height x width) array full of 0.
**/
int Maze::initiate_maze_grid(){
    //initiating maze_grid with 0s
    this->maze_grid = new bool*[height];

    for(int i = 0; i < height; i++){
        this->maze_grid[i] = new bool[width];
        std::memset(this->maze_grid[i], 0, width);
    }
    return 0;
}


/**
 * Adds walls of a cell to a wall_list. Checks if the neighbor
 * is not on the edge and add it to the list if it's a wall.
**/
int Maze::add_wallstolist(xy cell, std::vector<xy>& wall_list){

    if(cell.x + 1 < height - 1){
        xy tmp = cell;
        tmp.x++;
        if(this->maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    if(cell.x - 1 > 0){
        xy tmp = cell;
        tmp.x--;
        if(this->maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    if(cell.y + 1 < width - 1){
        xy tmp = cell;
        tmp.y++;
        if(this->maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    if(cell.y - 1 > 0){
        xy tmp = cell;
        tmp.y--;
        if(this->maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    return 0;
}
/**
 * Checks if the given point can be a passage.
 * It can be a passage only if a certain amount of its neighbors is passages already.
**/
bool Maze::can_bepassage(xy tocheck){

    int passage_count = 0;
    int corner_count = 0;

    int x = tocheck.x;
    int y = tocheck.y;

    //checks the 3x3 grid around the point
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(this->maze_grid[x+i][y+j] == 1 && (i != 0 || j != 0 )){
                if(abs(i) == 1 && abs(j) == 1){
                    corner_count++;
                }else{
                    passage_count++;
                }
            }
        }
    }
    int passage_threshold = treelike ? 1 : 2;
    if(passage_count > passage_threshold || corner_count > 1) {return false;}

    return true;
}

/**
 * Generates the maze using randomized Prim's algorithm.
**/
int Maze::generate_maze(){

    this->initiate_maze_grid();
    std::vector<xy> wall_vec;

    //pick a random point
    xy pt;
    pt.x = rand() % (height - 2) + 1;   //we only want a point from the inside of the maze
    pt.y = rand() % (width - 2) + 1;    //therefore the rand % (dim - 2) + 1

    //adding the random point to the maze;
    this->maze_grid[pt.x][pt.y] = 1;
    //adding the starting point walls to the wall_vec
    add_wallstolist(pt, wall_vec);
    //going on until there are walls in the wall_vec
    while(!wall_vec.empty()){
        //choosing a random wall in the list
        int position = rand() % wall_vec.size();
        xy wall = wall_vec[position];
        //checking if wall can be made into a passage
        if(can_bepassage(wall)){
            //making the wall into a passage
            this->maze_grid[wall.x][wall.y] = 1;
            this->add_wallstolist(wall, wall_vec);
        }
        wall_vec.erase(wall_vec.begin() + position);
    }
    this->random_startfinish();
    return 0;
}
/**
 * Reads the maze from a txt file.
 * Treats all '#' as walls.
 * 's' as a start, 'e' as an end.
**/
int Maze::generate_maze(std::string filename){
    //open a file with the given name
    std::ifstream f(filename.c_str());
    //if f failed to open, quit.
    if(!f.is_open()) return -1;
    //loading the txt to a list of strings
    MyList<std::string> lines;
    int max_line_size = 0;
    while(!f.eof()){
        std::string line;
        getline(f, line);
        lines.push_back(line);
        max_line_size = std::max(max_line_size, (int)line.size());
    }
    f.close();
    //setting width and height and creating maze_grid
    this->width = max_line_size;
    this->height = (int)lines.size();
    this->initiate_maze_grid();

    //setting some constants
    const char wll = '#';
    const char strt = 's';
    const char fnsh = 'e';
    //parsing the input and creating a maze of maze_grid
    for(int i = 0; i < height; i++){
        std::string line = lines.front();
        lines.pop_front();
        for(int j = 0; j < width; j++){
            if(j < (int)line.size()){
                switch(line[j]){
                    case wll :
                        this->maze_grid[i][j] = 0;
                        break;

                    case strt :
                        this->start.x = i;
                        this->start.y = j;
                        this->maze_grid[i][j] = 1;
                        break;

                    case fnsh :
                        this->finish.x = i;
                        this->finish.y = j;
                        this->maze_grid[i][j] = 1;
                        break;

                    default :
                        this->maze_grid[i][j] = 1;
                }
            }else{
                this->maze_grid[i][j] = 1;
            }
        }
    }

    this->random_startfinish();

    return 0;
}

/**
 * If there is no start or finish set up picks two point on the opposite corners of the maze.
**/
int Maze::random_startfinish(){
    //picks a random point that is a passage from opposite corners of the maze
    int x1 = 0;
    int x2 = bool(rand() % 2) ? 0 : height - 1;
    int y1 = 0;
    int y2 = width - 1;

    if(rand()%2){
        if(this->start.x < 0) this->start.x = x1;
        if(this->finish.x < 0) this->finish.x = x2;
    }else{
        if(this->start.x < 0) this->start.x = x2;
        if(this->finish.x < 0) this->finish.x = x1;
    }
    if(rand()%2){
        if(this->start.y < 0) this->start.y = y1;
        if(this->finish.y < 0) this->finish.y = y2;
    }else{
        if(this->start.y < 0) this->start.y = y2;
        if(this->finish.y < 0) this->finish.y = y1;
    }
    this->find_nearest_passage(this->start);
    this->find_nearest_passage(this->finish);
    return 0;
}

/**
 * Searches for a passage closest to the given point.
 * If it finds one it substitutes the given point's coordinates
 * with those of the found passage and returns true.
 * If it does not find a passage it returns false.
**/
int Maze::find_nearest_passage(xy &point){

    int search_radius = 1;
    int x = point.x;
    int y = point.y;
    while(this->maze_grid[x][y] == 0){
        for(int i = -search_radius; i <= search_radius; i++){
            if(x + i < height && x + i > 0){
                if(y - search_radius > 0 && maze_grid[x + i][y - search_radius] == 1){
                    x += i;
                    y -= search_radius;
                    break;
                }
                if(y + search_radius < width && maze_grid[x + i][y + search_radius] == 1){
                    x += i;
                    y += search_radius;
                    break;
                }
            }
            if(y + i < width && y + i > 0){
                if(x - search_radius > 0 && maze_grid[x - search_radius][y + i] == 1){
                    y += i;
                    x -= search_radius;
                    break;
                }
                if(x + search_radius < height && maze_grid[x + search_radius][y + i] == 1){
                    y += i;
                    x += search_radius;
                    break;
                }
            }
        }
        search_radius++;
        if(search_radius > std::max(height, width))
            return 1;
    }
    point.x = x;
    point.y = y;
    return 0;
}

/**
 * Prints out the maze_grid to the console.
**/
int Maze::print_maze_grid(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            std::cout << this->maze_grid[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    return 0;
}


/**
 * Prints out the maze_grid as a readable maze.
**/
int Maze::print_maze(){
    char wall = 219;
    char passage = ' ';
    char frame = '*';
    //print out the frame

    for(int i = -1; i < width + 1; i++){
        std::cout << frame;
    }
    std::cout << "\n";
    //actually printing out the maze with the frame
    for(int i = 0; i < height; i++){
        std::cout << frame;
        for(int j = 0; j < width; j++){
            if(i == this->start.x && j == this->start.y){
                std::cout << 's';
            }else if(i == this->finish.x && j == this->finish.y){
                std::cout << 'e';
            }else{
                if(maze_grid[i][j] == 0){
                    std::cout << wall;
                }else{
                    std::cout << passage;
                }
            }
        }
        std::cout << frame;
        std::cout << "\n";
    }
    //printing out the frame
    for(int i = -1; i < width + 1; i++){
        std::cout << frame;
    }
    std::cout << std::endl;
    return 0;
}

/**
 * Print the maze to a txt file. Passage is a space (' ').
 * A wall is a hash ('#').
**/
int Maze::print_maze_totxt(std::string filename){

    std::ofstream txt_write(filename.c_str());

    if(!txt_write.is_open()) return -1;

    char wall = '#';
    char passage = ' ';
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
           if(i == this->start.x && j == this->start.y){
                txt_write << 's';
            }else if(i == this->finish.x && j == this->finish.y){
                txt_write << 'e';
            }else{
                if(this->maze_grid[i][j] == 0){
                    txt_write << wall;
                }else{
                    txt_write << passage;
                }
            }
        }
        if(i != height - 1){
            txt_write << "\n";
        }
    }
    txt_write.close();
    return 0;
}

//getters
/**
 * Return the pointer to maze_grid.
**/
bool** Maze::get_maze_grid(){
    return this->maze_grid;
}
/**
 * Return the value of height.
**/
int Maze::get_height(){
    return this->height;
}
/**
 * Return the value of width.
**/
int Maze::get_width(){
    return this->width;
}
/**
 * Returns the start coordinates.
**/
xy Maze::get_start(){
    return this->start;
}
/**
 * Returns the finish coordinates.
**/
xy Maze::get_finish(){
    return this->finish;
}


