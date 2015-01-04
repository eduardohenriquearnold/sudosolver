#include "Solver.h"

bool Solver::validGrid(SudokuIterator& grdO)
{
        //Check all conditions (for each 'axis') 0-row; 1-column; 2-group;
        bool valid = true;
        
        for (int axis(0); axis<3; axis++)
        {
                SudokuIterator grd = grdO.changeType(axis);
                for (SudokuIterator it = grd.first(); it != grd.end(); it++)
                        if (*it == *grd && it != grd)
                                valid = false;
        }
        
        return valid; 
}

bool Solver::solveBT()
{
	//Enumerate empty cells and sets iterator on first execution
	if (emptyGrids.empty())
	{
	        for (int i(0); i<size(); i++)
		        for (int j(0); j<size(); j++)
		                if (operator()(i,j) == 0)
                                        emptyGrids.push_back(getIterator(i, j, 2));
                                        
                itEG = emptyGrids.begin();
        }        
		
	//Start solving		
        while (itEG != emptyGrids.end())
	{        
	        bool vGrid=false;
	        
	        for (int val=(**itEG)+1; val<=size() && !vGrid; val++)
	        {
	                **itEG = val;
	                vGrid = validGrid(*itEG);
                }
                
                //Check if Grid is correctly filled
                if (vGrid)
                        itEG++;
                else
                {
                        if (itEG == emptyGrids.begin())
                                //Sudoku has no solution from here further
                                return false;
                        else
                        {
                                **itEG = 0;
                                itEG--;
                        }
                }
	}
	
	//Solution was found. Shift iterator back in case another solution is needed.
	itEG--;
	return true;
}

int Solver::countSolutions()
{
        int count = 0;
        
        while(solveBT())
                count++;
                
        return count;
}

void Solver::restore()
{
        //Sets empty grids to zero again
        for (vector<SudokuIterator>::iterator it = emptyGrids.begin(); it != emptyGrids.end(); it++)
                **it = 0;
                
        //Clear empty grids -> force them to be created again, in case grids are modified
        emptyGrids.clear();
}

