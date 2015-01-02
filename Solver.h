#include <vector>
#include "Sudoku.h"

class Solver : public Sudoku
{
	private:
		vector<SudokuIterator> emptyCells;
		bool validGrid(SudokuIterator&);
		
	public:
		void solve();
};

