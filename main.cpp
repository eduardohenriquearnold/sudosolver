#include <iostream>
#include <fstream>
#include <random>
#include <functional>
#include <cstdlib>
#include "Solver.h"

using namespace std;

int main(int argc, char *argv[])
{    
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
                
                //Generate root Sudoku
                Solver s;
                s.size(size);
                
                for (int i=0; i<size; i++)
                        for (int j=0; j<size; j++)
                                s(i,j) = 0;
                                
                s.solveBT(); 
                s.clearHistory(false);

                //Randomly removes clues until reaches the specified amount
                default_random_engine generator;
                uniform_int_distribution<int> distribution(0, size-1);
                auto rndGen = bind ( distribution, generator );

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
                
                cout << "Puzzle generated." << endl;
                cout << s;
                
                
        }
        else
                cout << "Sudoku Solver and Generator." << endl << "Use -s [Filename] to solve." << endl << "Use -g [size] [clues] to generate a unique solution puzzle." << endl << "Created by Eduardo Arnold" << endl;
                
        /*SudokuIterator it = s.getIterator(2,3,2).last();
        while (it != it.end())
        {
                cout << *it << endl;
                it--;
        }
        cout << endl;*/


}
