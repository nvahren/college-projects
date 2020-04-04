#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "segment.h"
#include "dot.h"
#include <deque>
#include <ctime>

using namespace std;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( source, NULL, destination, &offset );
}

SDL_Surface * optimizeImage(string filename)
{
	SDL_Surface * tempImage = NULL;
	SDL_Surface * optimized = NULL;
	
	tempImage = IMG_Load(filename.c_str());

	if(tempImage != NULL)
	{
		optimized = SDL_DisplayFormat(tempImage);
		SDL_FreeSurface(tempImage);

		if( optimized != NULL )
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 255, 255, 255 ); 
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

int main( int argc, char* args[] ){

	SDL_Surface* snakeimg = NULL;
	SDL_Surface* dotimg = NULL;
	SDL_Surface* screen = NULL;
	SDL_Event event;
	int complete = 0;
	int delay = 800;
	int score = 0;
	
	segment s0;
	dot d0;
	deque<segment> snake;
	
	snake.push_back( s0 );
	snake.push_back( s0 );
	snake.push_back( s0 );
	
	int i;
	int direction = 1;
	int dotMoved;
	int nx, ny;
	
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode( 660, 660, 32, SDL_SWSURFACE );
	snakeimg = SDL_LoadBMP( "dot.bmp" );
	dotimg = SDL_LoadBMP( "dot.bmp" );
	
	srand( time(0) );

	while( !complete ){
	
		while( SDL_PollEvent( &event ) ){		
			if( event.type == SDL_QUIT ){
				complete = 1;
				break;
			}else if(event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
					case SDLK_RIGHT:
						if (direction != 3){
							direction = 1;
						}
						break;
					case SDLK_UP:
						if (direction != 4){
							direction = 2;
						}
						break;
					case SDLK_LEFT:
						if (direction != 1){
							direction = 3;
						}
						break;
					case SDLK_DOWN:
						if (direction != 2){
							direction = 4;
						}
						break;
					case SDLK_ESCAPE:
						complete = 1;
						break;
				}
			}
		}
		for( i = snake.size(); i > 0; i-- ){
			snake[i].setx( snake[i-1].getx() );
			snake[i].sety( snake[i-1].gety() );
		}
		switch (direction){
			case 1:
				snake[0].setx( snake[0].getx()+1 );
				snake[0].sety( snake[0].gety() );
				break;
			case 2:
				snake[0].setx( snake[0].getx() );
				snake[0].sety( snake[0].gety()-1 );
				break;
			case 3:
				snake[0].setx( snake[0].getx()-1 );
				snake[0].sety( snake[0].gety() );
				break;
			case 4:
				snake[0].setx( snake[0].getx() );
				snake[0].sety( snake[0].gety()+1 );
				break;
		}
		
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
		
		d0.draw(dotimg, screen);
		
		for( i = 0; i < snake.size(); i++ ){
			snake[i].draw(snakeimg, screen);
		}
		
		for( i = 1; i < snake.size(); i++ ){
			if (snake[i].getx() == snake[0].getx() && snake[i].gety() == snake[0].gety()){
				complete = 1;
			}
		}
		
		if( snake[0].getx() < 0 || snake[0].getx() > 32 ){
			complete = 1;
		}
		
		if( snake[0].gety() < 0 || snake[0].gety() > 32 ){
			complete = 1;
		}
		
		if( snake[0].getx() == d0.getx() && snake[0].gety() == d0.gety() ){
			dotMoved = 0;
			while( !dotMoved ){
				nx = rand() % 32;
				ny = rand() % 32;
				dotMoved = 1;
			
				for( i = 0; i < snake.size(); i++ ){
					if( snake[i].getx() == nx && snake[i].gety() == ny ){
						dotMoved = 0;
					}
				}	
			}
			
			d0.setx( nx );
			d0.sety( ny );
			snake.push_back( s0 );
			if (delay >= 50){
				delay -= 0.1*delay;
			}
			score++;
			
		}
		
		if( !complete ){
			SDL_Flip( screen );
			SDL_Delay( delay );
		}
		
	}
	
	SDL_Delay( 2000 );
	
	SDL_FreeSurface( snakeimg );
	
	SDL_Quit();
	
	return 0;
}
