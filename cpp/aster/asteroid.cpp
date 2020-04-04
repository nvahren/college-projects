#include "asteroid.h"
#include <cmath>

#define PI M_PI

using namespace std;

asteroid::asteroid(){

	size = 0;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	omega = 0;

}

int asteroid::getSize(){

	return size;

}

double asteroid::getx(){

	return x;

}

double asteroid::gety(){

	return y;
	
}

double asteroid::getvx(){

	return vx;

}

double asteroid::getvy(){

	return vy;
	
}

Uint32 asteroid::getColor(){

	return color;

}

void asteroid::setx( double nx ){

	x = nx;

}

void asteroid::sety( double ny ){

	y = ny;

}

void asteroid::setvx( double nvx ){

	vx = nvx;

}

void asteroid::setvy( double nvy ){

	vy = nvy;

}


void asteroid::move(){

	x += vx;
	y += vy;
	theta += omega;

}

void asteroid::set(int nsize, double nx, double ny, double nvx, double nvy, Uint32 ncolor){

	size = nsize;
	x = nx;
	y = ny;
	vx = nvx;
	vy = nvy;
	color = ncolor;
	double om = rand()%10-5;
	omega = om/20;

}

void asteroid::draw( SDL_Surface* screen ){

	double ax, ay, bx, by, cx, cy, dx, dy, ex, ey, fx, fy;
	
	ax = x+size*20*cos(theta);
	ay = y+size*20*sin(theta);
	bx = x+size*16*cos(theta+PI/3);
	by = y+size*16*sin(theta+PI/3);
	cx = x+size*20*cos(theta+2*PI/3);
	cy = y+size*20*sin(theta+2*PI/3);
	dx = x+size*24*cos(theta+PI);
	dy = y+size*24*sin(theta+PI);
	ex = x+size*20*cos(theta+4*PI/3);
	ey = y+size*20*sin(theta+4*PI/3);
	fx = x+size*20*cos(theta+5*PI/3);
	fy = y+size*20*sin(theta+5*PI/3);
	
	Draw_Line(screen, ax,ay, bx,by, color);
	Draw_Line(screen, bx,by, cx,cy, color);
	Draw_Line(screen, cx,cy, dx,dy, color);
	Draw_Line(screen, dx,dy, ex,ey, color);
	Draw_Line(screen, ex,ey, fx,fy, color);
	Draw_Line(screen, fx,fy, ax,ay, color);

}

int asteroid::check_collision( double nx, double ny ){
	
	if (sqrt(pow((nx-x),2)+pow((ny-y),2)) < size*22 ){
		return 1;
	}
	
	return 0;
	
}
