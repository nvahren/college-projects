#ifndef DOT_H
#define DOT_H

using namespace std;

class dot{

	public:
		dot();
		int getx();
		int gety();
		void setx( int );
		void sety( int );
		void draw(SDL_Surface*, SDL_Surface*);
	
	private:
		int x;
		int y;
};

#endif
