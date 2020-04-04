aster: main.o ship.o asteroid.o projectile.o power.o SDL_draw.o
	g++ ship.o main.o asteroid.o projectile.o power.o SDL_draw.o -o aster -lSDL
	
ship.o: ship.cpp ship.h
	g++ -c ship.cpp -lm
	
asteroid.o: asteroid.cpp asteroid.h
	g++ -c asteroid.cpp
	
projectile.o: projectile.cpp projectile.h
	g++ -c projectile.cpp -lm
	
power.o: power.cpp power.h
	g++ -c power.cpp -lm
	
main.o: main.cpp ship.h asteroid.h projectile.h
	g++ -c main.cpp
	
SDL_draw.o:
	gcc SDL_draw/SDL_draw.c -c
	
clean:
	rm aster *.o
