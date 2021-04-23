# Sudoku Solver 

An algorithm is implemented to solve the standard sudoku puzzle (9 x 9 grid) and the Hexadoku puzzle (16 x 16 grid) using C++. This algorithm is implemented by considering the backtracking algorithm then it was optimized by reducing the number of node expansions in the sudoku search tree while the backtracking process. Both the 9x9 and 16x16 sudoku puzzles can be solved in under 1 second with the minimum memory usage using this algorithm.

## How it works 

The implementation was initiated by developing a simple backtracking algorithm and optimized the backtracking algorithm by reducing the number of node expansions in the sudoku search tree while the backtracking process. The following mentioned steps are described how the implemented algorithm works. 

1. Initially, for every empty cell (which represent 0), a domain is defined as a set of numbers between 1 and N (N will be 9 or 16 according to grid size) except the numbers which are violated the sudoku rules.
When the modification occurs in the gride, domain values of each cell are updated according to newly assigned values. 
 
2. Creating a recursion function that searches suitable numbers to fill the empty cells on the grid(Backtracking process is implemented here)

     - Selecting the empty cell
In previous approaches, the empty cell which needs to fill next is selected linear manner but this empty cell selection is directly impacted the node expansion during the backtracking process and it will be affected to execution time. Therefore, in this approach, firstly select the cell with the smaller domain. Because if we have a cell with domain size one and the rest of the cells with domain sizes are higher than one. in that case, selecting the cell with domain size one is the best possible selection to reduce the backtracking expansion and it is the correct matching value to that cell. Before proceeding from this step, the algorithm checks whether the selected index is a valid index or not. If it is not a valid one that means all the cells are filled. Then stop the process and return the function with True value. 
     - Selecting a suitable value for the empty cell from its domain,
Once the empty cell is selected. the empty cell is assigned with its domain values one by one in a linear manner. During each value assigning, update the domain values of all the empty cells and check the updated domain values. 

    - Checking the domain value. After assigning the value into an empty cell. domain values of all the empty cells are updated according to the newly assigned value. After that, a function is defined to check the domain of the rest of the unfilled cell become empty. That means the currently updated value is not a correct value for that cell. If we did not avoid this case and move into the next cell, then the search tree expands unnecessarily. 
Therefore we check this case and if there is any empty domain after updating the cell. That assigned number removed and moved to the next iteration. Otherwise, we move into the next empty cell by calling the function recursively Then if a future empty cell does not have a matching domain value. Backtrack to the previously updated cell and removed the updated and moved to the next iteration. This process continues until all the unfiled cells are processed and filed. 




## How to use

This program can be run using a command line, and a solved sudoku puzzle will be written on a text file.

**Input file format**

- Input of this programme is a text file that must contain the input puzzle in the following format
The blank spaces will be denoted by zeros,
The text file must not contain any other characters or unnecessary spaces, tabs etc. Sample input files are available in the input folder.

9x9 Puzzle sample Input

  ```bash
  0 9 0 0 0 0 6 0 0 
  2 0 0 0 0 8 0 0 7 
  0 0 7 0 0 0 0 9 0 
  0 0 8 0 9 0 0 1 0 
  0 5 0 0 0 2 0 0 0 
  6 0 0 3 0 0 0 0 4 
  0 0 1 0 5 0 0 8 0 
  9 0 0 4 0 0 0 0 3 
  0 6 0 0 0 7 1 0 0
  ```

**Compile the Programme**

  ```bash
  g++ Sudoku Solver.cpp -o sudoku
  ```

**Execute the Programme**

  ```bash
 sudoku.exe <input file>
  ```



