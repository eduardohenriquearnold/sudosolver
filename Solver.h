#include <vector>
#include "Sudoku.h"

class Solver : public Sudoku
{
	private:
		vector<SudokuIterator> emptyGrids;
		vector<SudokuIterator>::iterator itEG;
		bool validGrid(SudokuIterator&);
		
	public:
	        //Try to find a new solution to the Sudoku using BackTracking Algorithm. If finds one returns true, otherwise false
		bool solveBT();
		
		//Count the number of possible solutions
		int countSolutions();
		
                //Clear empty grids content. Restore the original content before solving if restore is true
		void clearHistory(bool restore=true);
};

