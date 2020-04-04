#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "dot.h"

using namespace std;

dot::dot(){

	x = rand()%31;
	y = rand()%31;

}

int dot::getx(){

	return x;

}

int dot::gety(){

	return y;

}

void dot::setx( int nx ){

	x = nx;

}

void dot::sety( int ny ){

	y = ny;

}

void dot::draw( SDL_Surface* source, SDL_Surface* destination ){

	SDL_Rect offset;
	
	offset.x = x*20;
	offset.y = y*20;
	
	SDL_BlitSurface( source, NULL, destination, &offset );

}
