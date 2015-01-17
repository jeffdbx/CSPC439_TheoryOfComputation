#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

class Conway
{
public:

    // Default ctor.
    Conway();

    //  LoadSimulation
    //
    //  Reads the input .lif file into the coords vector.
    //  @param file_name: a string entered by the user.
    //  @param n: an integer entered by the user that represents the number of simulation iterations.
    //  @param coords: a vector that stores the raw x y coordinates from the .lif file.
    //
    void LoadSimulation(const std::string &file_name, const unsigned int &n_);

    //  RunSimulation
    //
    //  Runs the Conway Game of Life simulation.
    //  @param life_grid: a 2D vector of characters that stores the live ('O') and dead ('.') cells
    //  @param n: an integer that represents the number of iterations to run the simulation.
    //
    void RunSimulation();

    // Default dtor.
    ~Conway() {}

private:

    // enum 'hack'.  The rows and cols would probably be better as arguments passed in on object instantiation,
    // but for the purposes of this assignment I'll keep it as simple as possible.
    enum { GRID_ROWS = 20, GRID_COLS = 60 };
    std::vector<std::vector<char>> life_grid;
    std::vector<std::pair<int, int>> coords, translated_coords;
    unsigned int n;
    bool simulation_loaded;

    //  TranslatePoints
    //
    //  Translates the raw x y LoadSimulation to have an origin at (0,0).
    //  @param coords: a vector of integer pairs that stores the raw x y LoadSimulation from the .lif file.
    //  @param translated_coords: a vector of integer pairs that stores the translated LoadSimulation.
    //	
    void TranslatePoints(const std::vector<std::pair<int, int>> &coords, std::vector<std::pair<int, int>> &translated_coords);

    //  LoadLifeGrid
    //
    //  Loads the life grid with all of the "live" cells.
    //  @param translated_coords: a vector of integer pairs that stores the translated LoadSimulation.
    //  @param life_grid: a 2D vector of characters that stores the live ('O') and dead ('.') cells.
    //
    void LoadLifeGrid(const std::vector<std::pair<int, int>> &translated_coords, std::vector<std::vector<char>> &life_grid);

    //  PrintGrid
    //
    //  Prints the current state of the life grid.
    //  @param life_grid: a 2D vector of characters that stores the live ('O') and dead ('.') cells.
    //
    void PrintGrid(const std::vector<std::vector<char>> &life_grid);

    //  GetMinXY
    //
    //  Finds the minimum non-translated x and y LoadSimulation that were read from the .lif file.
    //  @param coords: a vector of integer pairs that stores the raw x y LoadSimulation from the .lif file.
    //  @return: a pair of x y LoadSimulation that are the minimums.
    //
    std::pair<int, int> GetMinXY(const std::vector<std::pair<int, int>> &coords);

    //  UpdateLifeGrid
    //
    //  Updates the state of the life grid.
    //  @param life_grid: a 2D vector of characters that stores the live ('O') and dead ('.') cells.
    //  @return: a 2D vector of characters with the updated game state.
    //
    std::vector<std::vector<char>> UpdateLifeGrid(const std::vector<std::vector<char>> &life_grid);

    //  CountAliveNeighbors
    //
    //  Counts the number of alive neighbors around the current cell.
    //  @param row: an integer that represents a row in the life grid.
    //  @param col: an integer that represents a column in the life grid.
    //  @param life_grid: a 2D vector of characters that stores the live ('O') and dead ('.') cells.
    //  @return: an integer that represents the number of "live" cells around the cell located at (row, col).
    //
    int CountAliveNeighbors(const int &row, const int &col, const std::vector<std::vector<char>> &life_grid);

    //  InBounds
    //
    //  Checks to see if a cell is within bounds of the life grid array (vector).
    //  @param row: an integer that represents a row in the life grid.
    //  @param col: an integer that represents a column in the life grid.
    //  @return: an bool value that represents if the cell is within bounds of the array or not.
    //
    bool InBounds(const int &row, const int &col);
};


