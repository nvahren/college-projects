all:	sudoku

sudoku: main.o sudoku.o
	g++ main.o sudoku.o -o sudoku
	
main.o: main.cpp
	g++ -c main.cpp
	
sudoku.o: sudoku.cpp
	g++ -c sudoku.cpp
	
clean:
	rm -f *.o sudoku
