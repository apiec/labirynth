#include "MazeMenu.h"
#include "MazeSolver.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

MazeMenu::MazeMenu(){
    maze_instance = NULL;
}

MazeMenu::~MazeMenu(){
    //dtor
}

void MazeMenu::main_menu(){

    /*
    const int possible_inputs = 10;
    char* inputs = new char[possible_inputs];
    for(int i = 0; i < possible_inputs; i++){
        inputs[i] = '0' + i;
    }
    */
    std::string input = "";
    bool stop = false;

    std::cout << "LABIRYNTH\n";
    while(!stop){
        std::cout
        << "Main Menu:\n"
        << "1. Generate the maze\n"
        << "2. Read the maze from a txt file\n"
        << "9. EXIT\n";

        input = "";
        getline(std::cin, input);
        switch(atoi(input.c_str())){
            case 1 :
                generation_menu();
                break;
            case 2 :
                txt_menu();
                break;
            case 9 :
                stop = true;
                break;


            default :
                std::cout << "PLEASE CHOOSE A VALID OPTION\n";
        }
    }
}

void MazeMenu::generation_menu(){
    //setup
    std::cout
    << "What size do you want the maze to be?\n"
    << "Dimensions must be in the range 3 - 200\n"
    ;
    std::string val_nm = "height";
    int h_inp = read_int(3, 200, "height");
    int w_inp = read_int(3, 200, "width");

    std::cout << "Do you want your maze to have multiple possible paths within it? [y/n]\n";
    char inp = ' ';
    while(inp != 'y' && inp != 'n'){
        std::cin.get(inp);
        inp = tolower(inp);
    }
    bool check = (inp == 'y');
    this->maze_instance = new MazeSolver(h_inp, w_inp, check);
    maze_loaded_menu();

    delete maze_instance;
    maze_instance = NULL;
}

void MazeMenu::txt_menu(){
    std::string filename = read_filename();
    this->maze_instance = new MazeSolver(filename);
    maze_loaded_menu();
    delete maze_instance;
    maze_instance = NULL;
}

void MazeMenu::maze_loaded_menu(){
    if(!maze_instance) return;
    bool stop = false;
    while(!stop){
        std::cout
        << "Maze menu\n"
        << "1. Display the maze\n"
        << "2. Display the maze and the solution\n"
        << "3. Display the binary version of the maze\n"
        << "4. Print the maze to a .txt file\n"
        << "9. EXIT\n";
        std::string input = "";
        while(input.empty()){
            getline(std::cin, input);
        }
        switch(atoi(input.c_str())){
            case 1 :
                this->maze_instance->print_maze();
                break;
            case 2 :
                this->maze_instance->print_maze_solution();
                if(!this->maze_instance->get_solution_found()){
                    std::cout << "No path found.\n";
                }
                break;
            case 3 :
                this->maze_instance->print_maze_grid();
                break;
            case 4 :
                this->maze_instance->print_maze_totxt(read_filename());
                break;

            case 9 :
                stop = true;
                break;

            default :
                std::cout << "PLEASE CHOOSE A VALID OPTION\n";
        }
    }

}

int MazeMenu::read_int(int low_bound, int high_bound, std::string val_name){
    std::string input = "";
    int to_return = low_bound - 1;
    bool incorrect_input = false;
    while(to_return < low_bound || to_return > high_bound){
        if(incorrect_input){
            std::cout << "Please choose a valid number (" << low_bound << "-" << high_bound << ")\n";
        }
        std::cout << val_name << ": ";
        getline(std::cin, input);
        to_return = atoi(input.c_str());
        incorrect_input = true;
    }
    return to_return;
}

std::string MazeMenu::read_filename(){
    std::string filename = "";
    std::cout << "Give a file name:\n";
    while(filename.empty()){
        std::cin >> filename;
    }
    size_t fn_sz = filename.size();
    std::string suffix = ".txt";
    if(filename.substr(fn_sz - suffix.size(), fn_sz) != suffix){
        filename += suffix;
    }
    return filename;
}
