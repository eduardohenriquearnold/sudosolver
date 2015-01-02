#include "Solver.h"

bool Solver::validGrid(SudokuIterator& grdO)
{
        //Check all conditions (for each 'axis') 0-row; 1-column; 2-group;
        bool valid = true;
        
        for (int axis(0); axis<3; axis++)
        {
                SudokuIterator grd = grdO.changeType(axis);
                for (SudokuIterator it = grd.first(); it != grd.end(); it++)
                        if ((*it) == (*grd) && it != grd)
                                valid = false;
        }
        
        return valid; 
}

void Solver::solve()
{
	//Enumerate empty cells
	for (int i(0); i<size(); i++)
		for (int j(0); j<size(); j++)
		        if (operator()(i,j) == 0)
                                emptyCells.push_back(getIterator(i, j, 2));
		
	//Start solving
	vector<SudokuIterator>::iterator it = emptyCells.begin();
	
        while (it != emptyCells.end())
	{
	        bool vGrid=false;
	        
	        for (int val=(*(*it))+1; val<size() || vGrid; val++)
	        {
	                *(*it) = val;
	                vGrid = validGrid(*it);
                }
                
                if (vGrid)
                        it++;
                else
                {
                        if (it == emptyCells.begin())
                                throw string("Sudoku does not have a solution");
                        else
                                it--;
                }
	}
	
	cout << "Solved puzzle" << endl;
}
