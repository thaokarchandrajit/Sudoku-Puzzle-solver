// Author: Chandrajit Thaokar 
// A Backtracking program  in C++ to solve Sudoku problem 
#include <iostream>
#include <fstream>
#include <sstream>


// EMPTY denotes the  empty cells in the sudoku grid
const int EMPTY  = 0;
 
// N denotes the  size of Sudoku grid. Size of the grid will be NxN
const int N = 9;
 

/* This boolean function searches through the grid to find a location that
   is still EMPTY. If it is found then 'row' and 'col' are set 
   to the EMPTY location and true is returned. If no locations are
   EMPTY false is returned */

bool FindEmptyLocation(int grid[N][N], int& row, int& col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == EMPTY)
                return true;
    return false;
}
 

 
/* This boolean function indicates whether any assigned entry
   in the specified row matches the given number. */
bool PresentInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* This boolean fucntion indicates whether any assigned entry
   in the specified column matches the given number. */
bool PresentInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* This boolean function indicates whether any assigned entry
   within the specified 3x3 box matches the given number. */
bool PresentInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}
 
/* This boolean function indicates whether it will violate the constraints to assign
   num to the given row,col location. */
bool isSafe(int grid[N][N], int row, int col, int num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !PresentInRow(grid, row, num) &&
           !PresentInCol(grid, col, num) &&
           !PresentInBox(grid, row - row%3 , col - col%3, num);
}

/* This function takes the partially solved grid and tries to designate values 
   to all the EMPTY locations while making sure that all the sudoku solution
   constraints are satisfied ( NO repeat entries across rows, columns or 3 x 3 box) */

bool Solve(int grid[N][N])
{
    int row, col;
 
    // If there are no EMPTY locations, solution is reached!!
    if (!FindEmptyLocation(grid, row, col))
       return true; 
 
    // Try digits 1 through 9
    for (int num = 1; num <= 9; num++)
    {
        // Check to see if its safe to assign 'num' to the location
        if (isSafe(grid, row, col, num))
        {
            // Assign num provisionally
            grid[row][col] = num;
 
            // If true, we have reached solution!
            if (Solve(grid))
                return true;
 
            // Otherwise reassign EMPTY value and try again
            grid[row][col] = EMPTY;
        }
    }
    return false; // This results in backtracking
}
 

 

int main()
{
    
	int grid[N][N];
	

	// Get the unsolved sudoku input file
	std::cout << std::endl;
	std::cout << "Please input the name of the unsolved sudoku file with the extension: ";
	
	std::string input;
	std::cin >> input;

	std::ifstream file(input);

	if(!file.good())
	{
		std::cout << std::endl;
		std::cout << "File does not exist! Please specify correct filename.";
		std::cout << std::endl;
		return 1;
	}
	
	// Parse the input from the input file.
	for(int row = 0; row < N; row++)
    {
        std::string line;
        std::getline(file, line);
        if ( !file.good() )
            break;
		
        std::stringstream iss(line);

        for (int col = 0; col < N; col++)
        {
            std::string val;
            std::getline(iss, val, ',');

            std::stringstream convertor(val);
            convertor >> grid[row][col];
		
        }
    }

	std::cout << std::endl;

	// Try to solve the puzzle. If successful, write the solution to a file.
    if (Solve(grid) == true)
	{
		std::cout << std::endl;
		std::string output_file;
		output_file = "Solution.csv";
		std::ofstream output(output_file);
		
			for (int row = 0; row < N; row++)
			{
				for (int col = 0; col < N; col++)
					{
						output << grid[row][col] << ",";
				    }
                output << "\n";
			}
			
			output.close();
			std::cout << "Solution exists! Please check the output file \'" << output_file << "\'.";
			std::cout << std::endl;
	}    
	    
    else
         std::cout << "No solution exists" << std::endl;
 
    return 0;
}