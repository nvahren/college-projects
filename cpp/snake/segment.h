#ifndef SEGMENT_H
#define SEGMENT_H

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class segment{

	public:
		segment();
		void draw(SDL_Surface*, SDL_Surface*);
		int getx();
		int gety();
		void setx(int);
		void sety(int);
	
	private:
		int x;
		int y;

};

#endif
