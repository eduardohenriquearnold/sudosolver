SudoSolver
==========

A C++ Sudoku Solver and Generator.

####Description
Uses a backtracking algorithm to find solutions to a given puzzle, thus is able to identify all valid solutions to a given Sudoku. This also enables the algorithm to generate new unique solution puzzles since it is possible to verify if a given puzzle has a single solution.

####Usage
To compile use `make all`.

To obtain all the solutions to a given puzzle, use `./sudosolver.out -s FILENAME` where **FILENAME** is the path to the file containing the puzzle. This file must contain the size of the Puzzle (number of cols/rows), 9 for the standard Sudoku followed by a line break. Next each cell should be described by its number (or 0 if it's a blank cell), with at least one space between cells and a optional line break between rows (to ease the visualization).

To generate a puzzle, use `./sudosolver.out -g SIZE CLUES` where **SIZE** is the number of cols/rows, and **CLUES** is the number of cells that are already filled in. Note that there is a minimum value of **CLUES** that should be filled for a given **SIZE** puzzle in order to produce a unique solution Sudoku. The puzzle will be printed on the **STDOUT**, you can save it to a file to further solving by directing the output of the program to a file with 
`./sudosolver.out -g SIZE CLUES > FILEPATH`.

**Example:**

```
./sudosolver.out -g 9 70 > mySudoku
./sudosolver.out -s mySudoku
```

####Motivation
Since I was young I was fascinated by Sudoku and was keen to learn new algorithms that would allow me to solve the puzzles faster. During this last semester of my exchange program in the UK I had a formal C++ module and decided that this project would be a good opportunity to exercise some of the theory. After concluding the solving part it was extended to generate new puzzles given it was very straightforward from that point.

####License
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 3.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


