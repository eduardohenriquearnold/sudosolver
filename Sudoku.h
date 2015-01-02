#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class SudokuIterator;

class Sudoku
{
	private:
		int s;
		vector<vector<int> > table;
		
	public:
		int size();
		void size(int);
		
		int& operator()(int i, int j);
		SudokuIterator getIterator(int i, int j, int type);

};

class SudokuIterator
{
	private:
		Sudoku* s;
		int NumElemPerGroup;
		
		int i, j;
		int type; //0 row; 1 column; 2 block;
		
	public:
		SudokuIterator(Sudoku* s1, int i1, int j1, int t) : s(s1), i(i1), j(j1), type(t) {NumElemPerGroup = pow(s->size(),1./2);};
		SudokuIterator() {};
		
		SudokuIterator changeType(int t);
		
		SudokuIterator first();
		SudokuIterator last();
		SudokuIterator next();
		SudokuIterator previous();
		SudokuIterator end();
		
		SudokuIterator operator++(int);
		SudokuIterator operator--(int);
		
		void operator=(SudokuIterator&);
		bool operator==(const SudokuIterator&);
		bool operator!=(const SudokuIterator&);
		
		int& operator*();
			
};

istream& operator>> (istream&, Sudoku&);
ostream& operator<< (ostream&, Sudoku&);

