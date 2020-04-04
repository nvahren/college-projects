#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "segment.h"

using namespace std;

segment::segment(){

	x = 1;
	y = 1;

}

void segment::draw( SDL_Surface* source, SDL_Surface* destination ){

	SDL_Rect offset;
	
	offset.x = x*20;
	offset.y = y*20;
	
	SDL_BlitSurface( source, NULL, destination, &offset );

}

int segment::getx(){

	return x;

}

int segment::gety(){

	return y;

}

void segment::setx( int nx ){

	x = nx;

}

void segment::sety( int ny ){

	y = ny;

}
