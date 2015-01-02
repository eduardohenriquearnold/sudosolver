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
                
                
                //Try to solve it
                //s.solve();               

                //Display result
                cout << s;
        }
        catch (string e)
        {
                cout << "Error: " + e << endl;
        }
        

}
