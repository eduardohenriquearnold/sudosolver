#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include "Solver.h"

using namespace std;

void help()
{
                cout << "Sudoku Solver and Generator." << endl
                     << "Use -s FILENAME to solve." << endl
                     << "Use -g SIZE CLUES to generate a unique solution puzzle." << endl
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
        else
        {
                cout << "Invalid option. " << endl;
                help();
        }
                
        /*SudokuIterator it = s.getIterator(2,3,2).last();
        while (it != it.end())
        {
                cout << *it << endl;
                it--;
        }
        cout << endl;*/


}
