#include "Sudoku.h"

int Sudoku::size()
{
	return s;
}

void Sudoku::size(int sz)
{
	//Empty table
	table.clear();
	
	//Check conditions: higher sero and perfect square
	if (sz>0 && pow(int(pow(sz,1./2)),2)==sz)
		s = sz;
	else
		throw string("Invalid sudoku table size");
		
	//Fill table
	for (int i(0); i<sz; i++)
		table.push_back(vector<int>(s, 0));
}

int& Sudoku::operator()(int i, int j)
{
	if (i<s && j<s)
		return table[i][j];
	else
		throw string("Invalid sudoku table position");
}

SudokuIterator Sudoku::getIterator(int i, int j, int type)
{
        return SudokuIterator(this, i, j, type);
}


///////////////
//STREAM
//////////////

istream& operator>> (istream& in, Sudoku& s)
{
	//Get size
	int sz;
	in >> sz >> ws;
	s.size(sz);
	
	//Fill table
	int v;
	for (int j(0); j<s.size(); j++)
		for (int i(0); i<s.size(); i++)
		{
			in >> v >> ws;
			s(i,j) = v;
		}
	
	return in;			
}

ostream& operator<< (ostream& out, Sudoku& s)
{
	//Output size
	out << s.size() << endl;
	
	//Output table
	for (int j(0); j<s.size(); j++)
	{
		for (int i(0); i<s.size(); i++)
			out << s(i,j) << " ";
			
		out << endl;	
	}
	
	return out;
			
}


///////////////
//ITERATOR
//////////////

SudokuIterator SudokuIterator::changeType(int t)
{
        return SudokuIterator(s, i, j, t);
}

SudokuIterator SudokuIterator::first()
{
		
	if (type==0)
		return SudokuIterator(s, i, 0, type);
	else if(type==1)
		return SudokuIterator(s, 0, j, type);
	else
	{
		int i1 = int(i / NumElemPerGroup) * NumElemPerGroup;
		int j1 = int(j / NumElemPerGroup) * NumElemPerGroup;
		return SudokuIterator(s, i1, j1, type);
	}
}

SudokuIterator SudokuIterator::last()
{
	if (type==0)
		return SudokuIterator(s, i, s->size()-1, type);
	else if(type==1)
		return SudokuIterator(s, s->size()-1, j, type);
	else
	{
		int i1 = int(i / NumElemPerGroup) * NumElemPerGroup + (NumElemPerGroup-1);
		int j1 = int(j / NumElemPerGroup) * NumElemPerGroup + (NumElemPerGroup-1);
		return SudokuIterator(s, i1, j1, type);
	}
}

SudokuIterator SudokuIterator::next()
{
	if (type==0)
	{
		if (j+1 != s->size())
			return SudokuIterator(s, i, j+1, type);
		else
			return end();
	}
	else if(type==1)
	{
		if (i+1 != s->size())
			return SudokuIterator(s, i+1, j, type);
		else
			return end();
	}
	else
	{
		int i1, j1;
		if ( int(i / NumElemPerGroup) != int((i+1) / NumElemPerGroup))
		{
			i1 = int(i / NumElemPerGroup) * NumElemPerGroup;
			j1 = j+1;

		        if ( int(j / NumElemPerGroup) == int((j+1) / NumElemPerGroup))
			        return SudokuIterator(s, i1, j1, type);
		        else
		                return end();
		}
		else
		{
			i1 = i+1;
			j1 = j;
			
		        return SudokuIterator(s, i1, j1, type);
		}		
	}
	
}

SudokuIterator SudokuIterator::previous()
{
	if (type==0)
	{
		if (j>0)
			return SudokuIterator(s, i, j-1, type);
		else
			return end();
	}
	else if(type==1)
	{
		if (i>0)
			return SudokuIterator(s, i-1, j, type);
		else
			return end();
	}
	else
	{
		int i1, j1;
		if ( int(i / NumElemPerGroup) != int((i-1) / NumElemPerGroup) || i==0)
		{
			i1 = int(i / NumElemPerGroup) * NumElemPerGroup + (NumElemPerGroup-1);
			j1 = j-1;
			
		        if ( int(j / NumElemPerGroup) == int(j1 / NumElemPerGroup) && j1!=-1)
		                return SudokuIterator(s, i1, j1, type);
		        else
		                return end();
		}
		else
		{
			i1 = i-1;
			j1 = j;
			
		        if ( i1 >= 0)
			        return SudokuIterator(s, i1, j1, type);
		        else
		                return end();
		}
		
	}
}

//Past the end element
SudokuIterator SudokuIterator::end()
{
        return SudokuIterator(s, -1, -1, type);
}

SudokuIterator SudokuIterator::operator++(int a)
{
        SudokuIterator it = next();
        i = it.i;
        j = it.j;
        
        return it;
}

SudokuIterator SudokuIterator::operator--(int a)
{
        SudokuIterator it = previous();
        i = it.i;
        j = it.j;
        
        return it;
}

void SudokuIterator::operator=(SudokuIterator& si)
{
        s = si.s;
        NumElemPerGroup = si.NumElemPerGroup;
        
        i = si.i;
        j = si.j;
        type = si.type;
}

bool SudokuIterator::operator==(const SudokuIterator& si)
{
        return (i==si.i) && (j==si.j) && (s == si.s);
}

bool SudokuIterator::operator!=(const SudokuIterator& si)
{
        return !(operator==(si));
}

int& SudokuIterator::operator*()
{
	return (*s)(i, j);
}

