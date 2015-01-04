#include <iostream>
#include <fstream>
#include "Solver.h"

using namespace std;

int main(int argc, char *argv[])
{
        try
        {        
                //Open file
                fstream file(argv[1], ios_base::in);       
                
                //Input sudoku        
                Solver s;
                file >> s;                
                
                //Try to solve it and display
                while (s.solveBT())
                        cout << s << endl;         
                
                /*SudokuIterator it = s.getIterator(2,3,2).last();
                while (it != it.end())
                {
                        cout << *it << endl;
                        it--;
                }
                cout << endl;*/

        }
        catch (string e)
        {
                cout << "Error: " + e << endl;
        }
        

}
