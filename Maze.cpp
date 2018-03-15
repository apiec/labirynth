#include "Maze.h"

#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>

#include "MyList.h"

int Maze::initiate_maze_grid(){
    //initiating maze_grid with 0s
    maze_grid = new bool*[height];

    for(int i = 0; i < height; i++){
        maze_grid[i] = new bool[width];
        std::memset(maze_grid[i], 0, width);
    }
    return 0;
}

int Maze::add_wallstolist(xy cell, std::vector<xy>& wall_list){
    //add walls of a cell to a wall_list
    //check if the neighbor isn't on the edge
    //and add it to the list if it's a wall
    if(cell.x + 1 < height - 1){
        xy tmp = cell;
        tmp.x++;
        if(maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    if(cell.x - 1 > 0){
        xy tmp = cell;
        tmp.x--;
        if(maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    if(cell.y + 1 < width - 1){
        xy tmp = cell;
        tmp.y++;
        if(maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    if(cell.y - 1 > 0){
        xy tmp = cell;
        tmp.y--;
        if(maze_grid[tmp.x][tmp.y] == 0){
            wall_list.push_back(tmp);
        }
    }
    return 0;
}

bool Maze::can_bepassage(xy tocheck){
    /**
    * check if the given point can be a passage
    **/
    int passage_count = 0;
    int corner_count = 0;

    int x = tocheck.x;
    int y = tocheck.y;

    //checks the 3x3 grid around the point
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if(maze_grid[x+i][y+j] == 1 && (i != 0 || j != 0 )){
                if(abs(i) == 1 && abs(j) == 1){
                    corner_count++;
                }else{
                    passage_count++;
                }
            }
        }
    }
    int passage_threshold = treelike ? 1 : 2;
    if(passage_count > passage_threshold || corner_count > 1)
        return false;
    /*
    if(treelike && (passage_count > 1 || corner_count > 1))
        return false;
    else if(!treelike && (passage_count > 2 || corner_count > 1))
        return false;
    */
    return true;
}

int Maze::generate_maze(){
    /**
    * generates the maze using randomized Prim's algorithm
    **/
    initiate_maze_grid();
    std::vector<xy> wall_vec;

    //pick a random point
    xy pt;
    pt.x = rand() % (height - 2) + 1;   //we only want a point from the inside of the maze
    pt.y = rand() % (width - 2) + 1;    //therefore the rand % (dim - 2) + 1

    //adding the random point to the maze;
    maze_grid[pt.x][pt.y] = 1;
    //adding the starting point walls to the wall_vec
    add_wallstolist(pt, wall_vec);
    //iterating until there are walls in the list
    while(!wall_vec.empty()){
        //choosing a random wall in the list
        int position = rand() % wall_vec.size();
        xy wall = wall_vec[position];
        //checking if wall can be made into a passage
        if(can_bepassage(wall)){
            //making the wall into a passage
            maze_grid[wall.x][wall.y] = 1;
            add_wallstolist(wall, wall_vec);
        }
        wall_vec.erase(wall_vec.begin() + position);
    }
    random_startfinish();
    return 0;
}

int Maze::generate_maze(std::string filename){
    /**
    * reads the maze from a txt file, treats all '#' as walls
    * 's' is a start, 'e' is an end
    **/

    std::ifstream f(filename.c_str());
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
    width = max_line_size;
    height = (int)lines.size();
    initiate_maze_grid();

    //setting some values
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
                        maze_grid[i][j] = 0;
                        break;

                    case strt :
                        start.x = i;
                        start.y = j;
                        maze_grid[i][j] = 1;
                        break;

                    case fnsh :
                        finish.x = i;
                        finish.y = j;
                        maze_grid[i][j] = 1;
                        break;

                    default :
                        maze_grid[i][j] = 1;
                }
            }else{
                maze_grid[i][j] = 1;
            }
        }
    }

    random_startfinish();

    return 0;
}


int Maze::random_startfinish(){
    //picks a random point that is a passage from opposite corners of the maze
/*
    int par = std::min(height, width)/std::min(height, width) + 1; //a parameter
    int x1 = rand() % (height / par) + 1;
    int x2 = height - rand()%(height / par) - 1;
    int y1 = rand() % (width / par) + 1;
    int y2 = width - rand()%(width / par) - 1;
  */
    int x1 = 0;
    int x2 = height - 1;
    int y1 = 0;
    int y2 = width - 1;

    if(rand()%2){
        if(start.x < 0) start.x = x1;
        if(finish.x < 0) finish.x = x2;
    }else{
        if(start.x < 0) start.x = x2;
        if(finish.x < 0) finish.x = x1;
    }
    if(rand()%2){
        if(start.y < 0) start.y = y1;
        if(finish.y < 0) finish.y = y2;
    }else{
        if(start.y < 0) start.y = y2;
        if(finish.y < 0) finish.y = y1;
    }
    find_nearest_passage(start);
    find_nearest_passage(finish);
    return 0;
}

int Maze::find_nearest_passage(xy &point){
    /**
    *   searches for a passage closest to the given point
    *   if it finds one it substitutes point's coordinates
    *   to those of the found passage and returns true
    *   if it doesn't find a passage it returns false
    **/
    int search_radius = 1;
    int x = point.x;
    int y = point.y;
    while(maze_grid[x][y] == 0){
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

//prints out the maze_grid
int Maze::print_maze_grid(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            std::cout << maze_grid[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    return 0;
}

//prints out the maze_grid as a readable maze
int Maze::print_maze(){
    char wall = 219;
    char passage = ' ';
    char frame = '#';
    //print out the frame
    for(int i = -1; i < width + 1; i++){
        std::cout << frame;
    }
    std::cout << "\n";
    //actually printing out the maze with the frame
    for(int i = 0; i < height; i++){
        std::cout << frame;
        for(int j = 0; j < width; j++){
            if(i == start.x && j == start.y){
                std::cout << 's';
            }else if(i == finish.x && j == finish.y){
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

//prints the maze to txt
int Maze::print_maze_totxt(std::string filename){

    std::ofstream txt_write(filename.c_str());
    if(!txt_write.is_open())
        return -1;

    // 178
    char wall = '#';
    char passage = ' ';
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
           if(i == start.x && j == start.y){
                txt_write << 's';
            }else if(i == finish.x && j == finish.y){
                txt_write << 'e';
            }else{
                if(maze_grid[i][j] == 0){
                    txt_write << wall;
                }else{
                    txt_write << passage;
                }
            }
        }
        txt_write << "\n";
    }

    txt_write.close();
    return 0;
}


bool** Maze::get_maze_grid(){
    return maze_grid;
}
int Maze::get_height(){
    return height;
}
int Maze::get_width(){
    return width;
}
xy Maze::get_start(){
    return start;
}
xy Maze::get_finish(){
    return finish;
}

void Maze::initiate_startfinish(){
    start.x = -1;
    start.y = -1;
    finish.x = -1;
    finish.y = -1;
}

//default constructor
Maze::Maze(bool is_treelike){
        width = 100;
        height = 40;
        initiate_startfinish();
        treelike = is_treelike;
        initiate_maze_grid();
        generate_maze();
}

//constructor with width and height as parameters
Maze::Maze(int h, int w, bool is_treelike): width(w), height(h) {
        initiate_startfinish();
        treelike = is_treelike;
        initiate_maze_grid();
        generate_maze();
}

Maze::Maze(std::string mazetxt){
    initiate_startfinish();
    generate_maze(mazetxt);
}

//deconstructor
Maze::~Maze(){
        //deleting maze_grid
        for(int i = 0; i < height; i++){
            delete[] maze_grid[i];
        }
        delete[] maze_grid;
}
