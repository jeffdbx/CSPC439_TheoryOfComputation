// Jeff Bohlin
// CPSC 439 - Assignment 1
// September 20th, 2014
//
// This program simulates Conway's Game of Life. 
// A full description of the game can be found at: http://en.wikipedia.org/wiki/Conway's_Game_of_Life
//
// ==========
// Game Rules
// ==========
// 
// 1) Any live cell with fewer than two live neighbours dies, as if by needs caused by underpopulation.
// 2) Any live cell with more than three live neighbours dies, as if by overcrowding.
// 3) Any live cell with two or three live neighbours lives, unchanged, to the next generation.
// 4) Any dead cell with exactly three live neighbours cells will come to life.
//

#include "Conway.h"

int main(int argc, char** argv)
{
    // User must supply a filename and an int > 0
    if (argc < 3)   
    {
        std::cerr << "Usage: " << argv[0] << " <filename> <n>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string file_name(argv[1]);
    std::string temp_n(argv[2]);
    int n = stoi(temp_n);               

    // n is the number of iterations to run the simulation
    if (n < 0)                          
    {
        std::cerr << "n must be greater than 0." << std::endl;
        return EXIT_FAILURE;
    }

    Conway conway;
    conway.LoadSimulation(file_name, n);
    conway.RunSimulation();

    return EXIT_SUCCESS;
}

