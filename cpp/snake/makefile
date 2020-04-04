snake: segment.o main.o dot.o
	g++ segment.o main.o dot.o -o snake -lSDL
	
segment.o: segment.cpp segment.h
	g++ -c segment.cpp
	
dot.o: dot.cpp dot.h
	g++ -c dot.cpp
	
main.o: main.cpp segment.h
	g++ -c main.cpp
	
clean:
	rm snake *.o
