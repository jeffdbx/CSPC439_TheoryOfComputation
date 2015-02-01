#include "Conway.h"

// Ctor.  Initialize the life_grid with GRID_ROWS and GRID_COLS using the enum 'hack'
Conway::Conway() : life_grid(GRID_ROWS, std::vector<char>(GRID_COLS, '.')), simulation_loaded(false)
{
}

// Reads the coordinates from the .lif file into the coords vector.
void Conway::LoadSimulation(const std::string &file_name, const unsigned int &n_)
{
    n = n_;
    std::ifstream fin;
    fin.open(file_name.c_str());

    if (!fin.is_open())
    {
        std::cout << "file not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string trash;
    int x, y;

    std::getline(fin, trash);   // Discard the title of the pattern.
    while (fin >> x >> y) { coords.push_back(std::make_pair(x, y)); }

    fin.close();

    TranslatePoints(coords, translated_coords);
    LoadLifeGrid(translated_coords, life_grid);
}

// Runs the Conway Game of Life simulation.
void Conway::RunSimulation()
{
    if (!simulation_loaded)
    {
        std::cerr << "The .lif file was not loaded properly. Did you call LoadSimulation first?" << std::endl;
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << "TIME STEP " << i << std::endl;
        PrintGrid(life_grid);
        life_grid = UpdateLifeGrid(life_grid);
        std::cout << std::endl;
    }
}

// Translates the raw x y coordinates to have an origin at (0,0).
void Conway::TranslatePoints(const std::vector<std::pair<int, int>> &coords, std::vector<std::pair<int, int>> &translated_coords)
{
    std::pair<int, int> min_x_y = GetMinXY(coords);

    for (auto i : coords)   // C++11
    {   
        // Subtract the smallest x and y values from each coordinate pair.  This places the origin at (0, 0).
        translated_coords.push_back(std::make_pair(i.first - min_x_y.first, i.second - min_x_y.second));
    }
}

// Loads the life grid with all of the "live" cells.
void Conway::LoadLifeGrid(const std::vector<std::pair<int, int>> &translated_coords, std::vector<std::vector<char>> &life_grid)
{
    for (auto i : translated_coords)
    {
        //  Some of the Life patterns are too big for our static grid size,
        //  so we can check for that here. Otherwise an OOB error can occur.
        try
        {   
            // Need to flip x (i.first) and y (i.second) here for some reason.
            life_grid.at(i.second).at(i.first) = 'O';
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "This Conway Life pattern does not fit within our 20 x 60 grid. Choose another." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    simulation_loaded = true;
}

// Prints the current state of the life grid.
void Conway::PrintGrid(const std::vector<std::vector<char>> &life_grid)
{
    // 20 rows X 60 columns
    for (auto rows : life_grid)
    {
        for (auto cols : rows) { std::cout << cols << " "; }
        std::cout << std::endl;
    }
}

// Finds the minimum non-translated x and y coordinates that were read from the .lif file.
std::pair<int, int> Conway::GetMinXY(const std::vector<std::pair<int, int>> &coords)
{
    std::pair<int, int> min_x_y;
    min_x_y.first = min_x_y.second = 0;

    // Check each pair of x and y coordinates
    for (auto i : coords)   // C++11
    {
        if (i.first < min_x_y.first)   { min_x_y.first = i.first; }
        if (i.second < min_x_y.second) { min_x_y.second = i.second; }
    }
    return min_x_y;
}

// Updates the state of the life grid.
std::vector<std::vector<char>> Conway::UpdateLifeGrid(const std::vector<std::vector<char>> &life_grid)
{
    int num_neighbors_alive = 0;
    std::vector<std::vector<char>> updated_life_grid(GRID_ROWS, std::vector<char>(GRID_COLS, '.'));

    for (unsigned int row = 0; row < life_grid.size(); row++)
    {
        for (unsigned int col = 0; col < life_grid.at(row).size(); col++)
        {
            num_neighbors_alive = CountAliveNeighbors(row, col, life_grid);

            // 1) Any live cell with fewer than two live neighbours dies, as if by needs caused by underpopulation.
            if ((life_grid.at(row).at(col) == 'O') && (num_neighbors_alive < 2))
            {
                updated_life_grid.at(row).at(col) = '.';
            }
            // 2) Any live cell with more than three live neighbours dies, as if by overcrowding.
            else if ((life_grid.at(row).at(col) == 'O') && (num_neighbors_alive > 3))
            {
                updated_life_grid.at(row).at(col) = '.';
            }
            // 3) Any live cell with two or three live neighbours lives, unchanged, to the next generation.
            else if ((life_grid.at(row).at(col) == 'O') && ((num_neighbors_alive == 2) || (num_neighbors_alive == 3)))
            {
                updated_life_grid.at(row).at(col) = 'O';
            }
            // 4) Any dead cell with exactly three live neighbours cells will come to life.
            else if ((life_grid.at(row).at(col) == '.') && (num_neighbors_alive == 3))
            {
                updated_life_grid.at(row).at(col) = 'O';
            }
        }
    }
    return updated_life_grid;
}

// Counts the number of alive neighbors around the current cell.
int Conway::CountAliveNeighbors(const int &row, const int &col, const std::vector<std::vector<char>> &life_grid)
{
    int num_neighbors_alive = 0;

    // This could be done iteratively, but for debugging reasons, I kept it as is.
    if (InBounds(row - 1, col - 1))                     // Check upper left cell
    {
        if (life_grid.at(row - 1).at(col - 1) == 'O')   { num_neighbors_alive++; }
    }
    if (InBounds(row - 1, col))                         // Check upper cell
    {
        if (life_grid.at(row - 1).at(col) == 'O')       { num_neighbors_alive++; }
    }
    if (InBounds(row - 1, col + 1))                     // Check upper right cell
    {
        if (life_grid.at(row - 1).at(col + 1) == 'O')   { num_neighbors_alive++; }
    }
    if (InBounds(row, col + 1))                         // Check right cell
    {
        if (life_grid.at(row).at(col + 1) == 'O')       { num_neighbors_alive++; }
    }
    if (InBounds(row + 1, col + 1))                     // Check lower right cell
    {
        if (life_grid.at(row + 1).at(col + 1) == 'O')   { num_neighbors_alive++; }
    }
    if (InBounds(row + 1, col))                         // Check lower cell
    {
        if (life_grid.at(row + 1).at(col) == 'O')       { num_neighbors_alive++; }
    }
    if (InBounds(row + 1, col - 1))                     // Check lower left cell
    {
        if (life_grid.at(row + 1).at(col - 1) == 'O')   { num_neighbors_alive++; }
    }
    if (InBounds(row, col - 1))                         // Check left cell
    {
        if (life_grid.at(row).at(col - 1) == 'O')       { num_neighbors_alive++; }
    }

    return num_neighbors_alive;
}

// Checks to see if a cell is within bounds of the life grid array (vector).
bool Conway::InBounds(const int &row, const int &col)
{
    return ((row >= 0 && row < GRID_ROWS) && (col >= 0 && col < GRID_COLS));
}
