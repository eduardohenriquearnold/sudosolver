CFLAGS=-Wall -std=c++11
SRC=Sudoku.cpp Solver.cpp
OBJ=$(subst .cpp,.o,$(SRC))

all: $(OBJ) main.cpp
	g++ $(CFLAGS) $(OBJ) main.cpp -o main.out

%.o: %.cpp
	g++ $(CFLAGS) -c $< 
	
clean:
	rm *.a
	rm *.out

