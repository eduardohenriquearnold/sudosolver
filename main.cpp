#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include "Solver.h"
#include "SudokuImg.h"

using namespace std;

void help()
{
                cout << "Sudoku Solver and Generator." << endl
                     << "Use -s FILENAME to solve." << endl
                     << "Use -g SIZE CLUES to generate a unique solution puzzle." << endl
                     << "Use -h to extended help" << endl
                     << "Created by Eduardo Arnold" << endl;
}

int main(int argc, char *argv[])
{    

        if (argc < 2)
        {
                help();
                return 1;
        }
        
        /////////////
        ///SOLVER////
        /////////////
        string option(argv[1]);
        
        if (option == "-s")
        {
                //Open file
                fstream file(argv[2], ios_base::in);       

                //Input sudoku        
                Solver s;
                file >> s;                

                //Try to solve it and display
                cout << "Solutions: " << endl;
                while (s.solveBT())
                        cout << s << endl;         
                
        }        
        else
        /////////////
        ///GENERATOR/
        /////////////
        if (option == "-g")
        {
                int size = atoi(argv[2]);
                int clues = atoi(argv[3]);
                
                //Random interface
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                default_random_engine generator (seed);
                uniform_int_distribution<int> distribution(0, size-1);
                auto rndGen = bind ( distribution, generator );
                
                //Generate random root Sudoku
                Solver s;
                s.size(size);
                
                vector<int> diag;
                for (int i=1; i<=size; i++)
                        diag.push_back(i);
                shuffle(diag.begin(), diag.end(), generator);
                
                        
                for (int i=0; i<size; i++)
                        for (int j=0; j<size; j++)
                                if (i==j)
                                        s(i,j) = diag[i];
                                else
                                        s(i,j) = 0;
                                
                s.solveBT(); 
                s.clearHistory(false);

                //Randomly removes clues until reaches the specified amount
                int c = size*size - clues;
                while (c>0)
                {
                        int i = rndGen();
                        int j = rndGen();

                        if (s(i,j) == 0)
                                continue;
                                
                        //Attemps to remove a grid
                        int temp = s(i,j);
                        s(i,j) =  0;

                        int sols = s.countSolutions();
                        s.clearHistory();
                        
                        //If there is still a unique solution, then grid can be removed
                        if (sols == 1)
                                c--;
                        else
                                s(i,j) = temp;                                 
                }
                
                cout << s;                
        }
        /////////////
        ///EXTENDED HELP
        /////////////
        if (option == "-h")
        {
                cout <<
                        "To obtain all the solutions to a given puzzle, use `./sudosolver.out -s FILENAME` where FILENAME is the path to the file containing the puzzle. This file must contain the size of the Puzzle (number of cols/rows), 9 for the standard Sudoku followed by a line break. Next each cell should be described by its number (or 0 if it's a blank cell), with at least one space between cells and a optional line break between rows (to ease the visualization)."
                     << endl << endl << 
                        "To generate a puzzle, use `./sudosolver.out -g SIZE CLUES` where SIZE is the number of cols/rows, and CLUES is the number of cells that are already filled in. Note that there is a minimum value of CLUES that should be filled for a given SIZE puzzle in order to produce a unique solution Sudoku. The puzzle will be printed on the STDOUT, you can save it to a file to further solving by directing the output of the program to a file with `./sudosolver.out -g SIZE CLUES > FILEPATH`. "
                     << endl << endl << 
                        "Example:" << endl <<                      
                        "./sudosolver.out -g 9 70 > mySudoku" << endl <<
                        "./sudosolver.out -s mySudoku" << endl;

        }
        else
        //////////////////
        ////Process Image
        //////////////////
        if (option == "-i")
        {
                SudokuImg solver;
                solver.parseImage(string(argv[2]));
                cout << "Done" << endl;
        }        
        //No valid option
        else        
        {
                cout << "Invalid option. " << endl;
                help();
        }                
}
