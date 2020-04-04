#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "gfx.h"

int main(void){

//Define Variables
  float x = 400, y = 400;
  float vx = 0, vy = 0;
  float pi = 3.1415;
  float theta = pi/2;
  float w = 0;
  float a = 2;
  float alpha = 0.01;
  float xprj, yprj;
  float vxprj, vyprj;
  float xast = 100, yast = 100;
  float vxast = 20, vyast = -75;
  float xast2 = 600, yast2 = 100;
  float vxast2 = 23, vyast2 = -10;
  float xast3 = 100, yast3 = 300;
  float vxast3 = -15, vyast3 = -60;
  int score = 0;
  int loop = 1;
  char c;


  printf("\nControls:\n");
  printf("Up Arrow: Accelerate\n");
  printf("Left/Right Arrow: Rotate\n");
  printf("Down Arrow: Teleport\n");
  printf("Space Bar: Shoot\n\n");
  printf("Starting in 3 seconds...\n\n");

  usleep(3000000);
  gfx_open(800,800,"rotate.c");

while(loop){

  gfx_clear();

  //Ship
  gfx_color(255,255,255);
  //Point 1 to 2
  gfx_line(x+20*cos(theta),y-20*sin(theta),x+20*cos(theta+5*pi/6),y-20*sin(theta+5*pi/6));
  //Point 2 to 3
  gfx_line(x+20*cos(theta+5*pi/6),y-20*sin(theta+5*pi/6),x+15*cos(theta+pi),y-15*sin(theta+pi));
  //Point 3 to 4
  gfx_line(x+15*cos(theta+pi),y-15*sin(theta+pi),x+20*cos(theta+7*pi/6),y-20*sin(theta+7*pi/6));
  //Point 4 to 1
  gfx_line(x+20*cos(theta+7*pi/6),y-20*sin(theta+7*pi/6),x+20*cos(theta),y-20*sin(theta));

  //Projectile
  gfx_color(255,255,255);
  gfx_line(xprj,yprj,xprj+1,yprj);
  gfx_line(xprj+1,yprj,xprj+1,yprj+1);
  gfx_line(xprj+1,yprj+1,xprj,yprj+1);
  gfx_line(xprj,yprj+1,xprj,yprj);

  //Asteroid 1
  gfx_color(255,0,255);
  gfx_line(xast-15,yast-15,xast+18,yast-14);
  gfx_line(xast+18,yast-14,xast+20,yast);
  gfx_line(xast+20,yast,xast+10,yast+12);
  gfx_line(xast+10,yast+12,xast-13,yast+18);
  gfx_line(xast-13,yast+18,xast-20,yast-2);
  gfx_line(xast-20,yast-2,xast-15,yast-15);

  //Asteroid 2
  gfx_color(255,128,0);
  gfx_line(xast2-12,yast2-18,xast2+15,yast2-16);
  gfx_line(xast2+15,yast2-16,xast2+20,yast2);
  gfx_line(xast2+20,yast2,xast2+8,yast2+10);
  gfx_line(xast2+8,yast2+10,xast2-15,yast2+15);
  gfx_line(xast2-15,yast2+15,xast2-20,yast2-2);
  gfx_line(xast2-20,yast2-2,xast2-12,yast2-18);

  //Asteroid 3
  gfx_color(255,0,0);
  gfx_line(xast3-15,yast3-15,xast3+15,yast3-16);
  gfx_line(xast3+15,yast3-16,xast3+20,yast3);
  gfx_line(xast3+20,yast3,xast3+12,yast3+10);
  gfx_line(xast3+12,yast3+10,xast3-12,yast3+15);
  gfx_line(xast3-12,yast3+15,xast3-18,yast3-4);
  gfx_line(xast3-18,yast3-4,xast3-15,yast3-15);

  gfx_flush();

  usleep(10000);

  //Update Locations
  x += vx * 0.01;
  y -= vy * 0.01;
  theta += w;
  xprj += vxprj * 0.01;
  yprj -= vyprj * 0.01;
  xast += vxast * 0.01;
  yast -= vyast * 0.01;
  xast2 += vxast2 * 0.01;
  yast2 -= vyast2 * 0.01;
  xast3 += vxast3 * 0.01;
  yast3 -= vyast3 * 0.01;

  //Check Position of Ship
  if (x > 800){
    x = 0;
  }
  if(x < 0){
    x = 800;
  }
  if(y > 800){
    y = 0;
  }
  if(y < 0){
    y = 800;
  }

  //Check Position of Asteroid 1
  if (xast > 800){
    xast = 0;
  }
  if(xast < 0){
    xast = 800;
  }
  if(yast > 800){
    yast = 0;
  }
  if(yast < 0){
    yast = 800;
  }

  //Check Position of Asteroid 2
  if (xast2 > 800){
    xast2 = 0;
  }
  if(xast2 < 0){
    xast2 = 800;
  }
  if(yast2 > 800){
    yast2 = 0;
  }
  if(yast2 < 0){
    yast2 = 800;
  }

  //Check Position of Asteroid 3
  if (xast3 > 800){
    xast3 = 0;
  }
  if(xast3 < 0){
    xast3 = 800;
  }
  if(yast3 > 800){
    yast3 = 0;
  }
  if(yast3 < 0){
    yast3 = 800;
  }

  //Check for Ship Impact
  if (sqrt(pow((x-xast),2)+pow((y-yast),2)) < 25){
    usleep(3000000);
    printf("Score: %d\n\n",score);
    return 0;
  }

  if (sqrt(pow((x-xast2),2)+pow((y-yast2),2)) < 25){
    usleep(3000000);
    printf("Score: %d\n\n",score);
    return 0;
  }

  if (sqrt(pow((x-xast3),2)+pow((y-yast3),2)) < 25){
    usleep(3000000);
    printf("Score: %d\n\n",score);
    return 0;
  }

  //Check for Projectile Impact
  if (sqrt(pow((xprj-xast),2)+pow((yprj-yast),2)) < 25){
    xast = rand() % 600 + 100;
    yast = rand() % 600 + 100;
    score++;
  }

  if (sqrt(pow((xprj-xast2),2)+pow((yprj-yast2),2)) < 25){
    xast2 = rand() % 600 + 100;
    yast2 = rand() % 600 + 100;
    score++;
  }

  if (sqrt(pow((xprj-xast3),2)+pow((yprj-yast3),2)) < 25){
    xast3 = rand() % 600 + 100;
    yast3 = rand() % 600 + 100;
    score++;
  }

  //Check for input
  if (gfx_event_waiting()){
    c = gfx_wait();
    switch(c){
      case 'R':
        vx += a*cos(theta);
        vy += a*sin(theta);
        break;
      case 'T':
        x = rand() % 600 + 100;
        y = rand() % 600 + 100;
        break;
      case 'Q':
        w += alpha;
        break;
      case 'S':
        w -= alpha;
        break;
      case ' ':
        xprj = x + 20*cos(theta);
        yprj = y - 20*sin(theta);
        vxprj = vx + 500*cos(theta);
        vyprj = vy + 500*sin(theta);
    }
  }
  c = 0;
}

}
