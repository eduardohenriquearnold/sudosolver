CFLAGS=-Wall -std=c++11 
CFLAGS+=$(shell pkg-config --cflags --libs opencv)
SRC=Sudoku.cpp Solver.cpp SudokuImg.cpp OCR.cpp
OBJ=$(subst .cpp,.o,$(SRC))

all: $(OBJ) main.cpp
	g++ $(CFLAGS) $(OBJ) main.cpp -o sudosolver.out

%.o: %.cpp
	g++ $(CFLAGS) -c $< 
	
clean:
	rm -r *.o
	rm -r *.out

