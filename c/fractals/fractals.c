// Nathan Vahrenberg
// fractals.c

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "gfx.h"

// Functions to Draw Shapes

void draw_triangle ( int x1, int y1, int x2, int y2, int x3, int y3){
  gfx_line(x1, y1, x2, y2);
  gfx_line(x2, y2, x3, y3);
  gfx_line(x3, y3, x1, y1);
}


void draw_square ( int x1, int y1, int x2, int y2){
  gfx_line(x1, y1, x2, y1);
  gfx_line(x2, y1, x2, y2);
  gfx_line(x2, y2, x1, y2);
  gfx_line(x1, y2, x1, y1);
}


void draw_circle ( int x, int y, int r ){
  double i;
  for (i = 0; i < 2*M_PI; i += 0.05){
    gfx_line(
      x + r*cos(i), y - r*sin(i),
      x + r*cos(i+0.05), y - r*sin(i+0.05));
  }
}


// Functions to Create Fractals

void fractal_triangle( int x1, int y1, int x2, int y2, int x3, int y3 ){

  // Base Case
  if ( abs(x2-x1) < 2 ){
    return;
  }

  // Draw Function
  draw_triangle(x1, y1, x2, y2, x3, y3);

  // Recursive Case
  fractal_triangle(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
  fractal_triangle((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
  fractal_triangle((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}


void fractal_square( int x1, int y1, int x2, int y2 ){

  int s = x2 - x1;

  // Base Case
  if ( s < 8 ){
    return;
  }

  // Draw Function
  draw_square(x1, y1, x2, y2);

  // Recursive Case
  fractal_square(x1-s/4, y1-s/4, x1+s/4, y1+s/4);
  fractal_square(x2-s/4, y1-s/4, x2+s/4, y1+s/4);
  fractal_square(x2-s/4, y2-s/4, x2+s/4, y2+s/4);
  fractal_square(x1-s/4, y2-s/4, x1+s/4, y2+s/4);
}


void fractal_spiral_square( int x, int y, int r, double theta ){

  int s = r / 4;

  // Base Case
  if ( r < 1 ){
    return;
  }

  // Draw Function
  draw_square(
    x + r*cos(theta) - s/2, y - r*sin(theta) - s/2,
    x + r*cos(theta) + s/2, y - r*sin(theta) + s/2);

  // Recursive Case
  fractal_spiral_square(x, y, r - 10, theta + M_PI/6);
}


void fractal_lace( int x, int y, int r ){

  // Base Case
  if ( r < 2 ){
    return;
  }

  // Draw Function
  draw_circle(x, y, r);

  // Recursive Case
  fractal_lace(x + r*cos(0), y - r*sin(0), r/3);
  fractal_lace(x + r*cos(M_PI/3), y - r*sin(M_PI/3), r/3);
  fractal_lace(x + r*cos(2*M_PI/3), y - r*sin(2*M_PI/3), r/3);
  fractal_lace(x + r*cos(M_PI), y - r*sin(M_PI), r/3);
  fractal_lace(x + r*cos(4*M_PI/3), y - r*sin(4*M_PI/3), r/3);
  fractal_lace(x + r*cos(5*M_PI/3), y - r*sin(5*M_PI/3), r/3);
}


void fractal_snowflake( int x, int y, int l ){

  // Base Case
  if ( l < 2 ){
    return;
  }

  // Draw Function
  gfx_line(x, y, x + l*cos(0), y - l*sin(0));
  gfx_line(x, y, x + l*cos(2*M_PI/5), y - l*sin(2*M_PI/5));
  gfx_line(x, y, x + l*cos(4*M_PI/5), y - l*sin(4*M_PI/5));
  gfx_line(x, y, x + l*cos(6*M_PI/5), y - l*sin(6*M_PI/5));
  gfx_line(x, y, x + l*cos(8*M_PI/5), y - l*sin(8*M_PI/5));

  // Recursive Case
  fractal_snowflake(x + l*cos(0), y - l*sin(0), l/3);
  fractal_snowflake(x + l*cos(2*M_PI/5), y - l*sin(2*M_PI/5), l/3);
  fractal_snowflake(x + l*cos(4*M_PI/5), y - l*sin(4*M_PI/5), l/3);
  fractal_snowflake(x + l*cos(6*M_PI/5), y - l*sin(6*M_PI/5), l/3);
  fractal_snowflake(x + l*cos(8*M_PI/5), y - l*sin(8*M_PI/5), l/3);
}


void fractal_tree( int x, int y, double theta, int l ){

  // Base Case
  if ( l < 4 ){
    return;
  }

  // Draw Function
  gfx_line(x, y, x + l*cos(theta+M_PI/6), y - l*sin(theta+M_PI/6));
  gfx_line(x, y, x + l*cos(theta-M_PI/6), y - l*sin(theta-M_PI/6));

  // Recursive Case
  fractal_tree(x + l*cos(theta+M_PI/6), y - l*sin(theta+M_PI/6), theta+M_PI/6, 3*l/4);
  fractal_tree(x + l*cos(theta-M_PI/6), y - l*sin(theta-M_PI/6), theta-M_PI/6, 3*l/4);
}


void fractal_fern( int x, int y, double theta, int l, int depth ){

  // Base Case
  if ( l < 2 || depth == 0 ){
    return;
  }

  // Draw Function
  gfx_line(x, y, x + l*cos(theta), y - l*sin(theta));
  gfx_line(x + l*cos(theta), y - l*sin(theta), x + l*cos(theta) + l*cos(theta+M_PI/6), y - l*sin(theta) - l*sin(theta+M_PI/6));
  gfx_line(x + l*cos(theta), y - l*sin(theta), x + l*cos(theta) + l*cos(theta-M_PI/6), y - l*sin(theta) - l*sin(theta-M_PI/6));

  // Recursive Case
  fractal_fern(x + l*cos(theta), y - l*sin(theta), theta, l, --depth);
  fractal_fern(x + l*cos(theta), y - l*sin(theta), theta+M_PI/6, l/4, 4);
  fractal_fern(x + l*cos(theta), y - l*sin(theta), theta-M_PI/6, l/4, 4);
}


void fractal_spiral( int x, int y, int r, double theta){

  double i = theta;
  int rad = r;

  // Base Case
  if ( r < 1 ){
    return;
  }

  // Draw Function
  while( rad > 2 ){
    gfx_point(x + rad*cos(i), y - rad*sin(i));

    // Recursive Case
    fractal_spiral(x + rad*cos(i), y - rad*sin(i), rad/3, i);

    i += M_PI/6;
    rad *= 0.9;
  }
}


// Main Function

int main ( void ){

  // Declare Variables
  char c;

  // Open Graphics Window
  gfx_open(800,800,"Fractals");

  while ( 1 ){

    c = 0;

    if ( gfx_event_waiting() ){
      c = gfx_wait();
    }
    switch ( c ){

      case '1':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_triangle(400, 54, 0, 746, 800, 746);
        break;

      case '2':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_square(200, 200, 600, 600);
        break;

      case '3':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_spiral_square(400, 400, 300, 0);
        break;

      case '4':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_lace(400, 400, 250);
        break;

      case '5':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_snowflake(400, 400, 250);
        break;

      case '6':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_tree(400, 600, M_PI/2, 150);
        break;

      case '7':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_fern(400, 750, M_PI/2, 100, 4);
        break;

      case '8':
        gfx_clear();
        gfx_color(255,255,255);
        fractal_spiral(400, 400, 400, 0);
        break;

      case '0':
        gfx_clear();
        break;

      case 'q':
        return 0;
    }
  }
}
