#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "gfx.h"

#define WSIZEX 1500
#define WSIZEY 800
#define GRAV 1.622
#define TIME 0.01

#define MASS 30;

struct ship {
  double xloc;
  double yloc;
  double xvel;
  double yvel;
  double angle;
  double omega;
  double size;
  double fuel;
  double mass;
  double thrust;
};

void render_ship(struct ship lander){
  
  gfx_line(lander.xloc+lander.size*cos(lander.angle+1*M_PI/6),lander.yloc+lander.size*sin(lander.angle+1*M_PI/6),
           lander.xloc+lander.size*cos(lander.angle+11*M_PI/6),lander.yloc+lander.size*sin(lander.angle+11*M_PI/6));
  gfx_line(lander.xloc+lander.size*cos(lander.angle+11*M_PI/6),lander.yloc+lander.size*sin(lander.angle+11*M_PI/6),
           lander.xloc+lander.size*cos(lander.angle+9*M_PI/6),lander.yloc+lander.size*sin(lander.angle+9*M_PI/6));
  gfx_line(lander.xloc+lander.size*cos(lander.angle+9*M_PI/6),lander.yloc+lander.size*sin(lander.angle+9*M_PI/6),
           lander.xloc+lander.size*cos(lander.angle+7*M_PI/6),lander.yloc+lander.size*sin(lander.angle+7*M_PI/6));
  gfx_line(lander.xloc+lander.size*cos(lander.angle+7*M_PI/6),lander.yloc+lander.size*sin(lander.angle+7*M_PI/6),
           lander.xloc+lander.size*cos(lander.angle+5*M_PI/6),lander.yloc+lander.size*sin(lander.angle+5*M_PI/6));
  gfx_line(lander.xloc+lander.size*cos(lander.angle+5*M_PI/6),lander.yloc+lander.size*sin(lander.angle+5*M_PI/6),
           lander.xloc+lander.size*cos(lander.angle+3*M_PI/6),lander.yloc+lander.size*sin(lander.angle+3*M_PI/6));
  gfx_line(lander.xloc+lander.size*cos(lander.angle+3*M_PI/6),lander.yloc+lander.size*sin(lander.angle+3*M_PI/6),
           lander.xloc+lander.size*cos(lander.angle+1*M_PI/6),lander.yloc+lander.size*sin(lander.angle+1*M_PI/6));
  gfx_line(lander.xloc+lander.size*cos(lander.angle+M_PI/3),lander.yloc+lander.size*sin(lander.angle+M_PI/3),
           lander.xloc+1.5*lander.size*cos(lander.angle+M_PI/3),lander.yloc+1.5*lander.size*sin(lander.angle+M_PI/3));
  gfx_line(lander.xloc+lander.size*cos(lander.angle-M_PI/3),lander.yloc+lander.size*sin(lander.angle-M_PI/3),
           lander.xloc+1.5*lander.size*cos(lander.angle-M_PI/3),lander.yloc+1.5*lander.size*sin(lander.angle-M_PI/3));
           
}

void render_terrain( int terrain[WSIZEX] ){
  
  int i;
  
  for(i = 2; i < WSIZEX; i++){
    gfx_line(i-1,terrain[i-1],i,terrain[i]);
  }
}

void render_hud(struct ship lander, int alternator){

  double i;

  //Fuel Gauge
  gfx_line(20,20,20,120);
  gfx_line(20,120,40,120);
  gfx_line(40,120,40,20);
  gfx_line(40,20,20,20);
  gfx_line(20,120-lander.fuel,40,120-lander.fuel);
  for (i = 120-lander.fuel; i <= 120; i++){
    gfx_line(20,i,40,i);
  }
  
  //Thrust Meter
  gfx_line(50,20,50,120);
  gfx_line(50,120,70,120);
  gfx_line(70,120,70,20);
  gfx_line(70,20,50,20);
  if (lander.thrust <= 100){
    gfx_line(50,120-lander.thrust,70,120-lander.thrust);
    for (i = 120-lander.thrust; i <= 120; i++){
      gfx_line(50,i,70,i);
    }
  }else{
    for (i = 20; i <= 120; i++){
      gfx_line(50,i,70,i);
    }
    gfx_color(255,0,0);
    gfx_line(51,120-(lander.thrust-100),69,120-(lander.thrust-100));
    for (i = 120-(lander.thrust-100); i <= 119; i++){
      gfx_line(51,i,69,i);
    }
    gfx_color(255,255,255);
  }
  
  //Velocity Meter
  for(i = 0; i<=M_PI/2; i+=0.01){
    gfx_line(80+100*cos(i-0.01),120-100*sin(i-0.01),80+100*cos(i),120-100*sin(i));
    gfx_line(80+5*cos(i-0.01),120-5*sin(i-0.01),80+5*cos(i),120-5*sin(i));
  }
  for(i = 0; i<=M_PI/2; i+=M_PI/8){
    gfx_line(80+95*cos(i),120-95*sin(i),80+100*cos(i),120-100*sin(i));
  }
  gfx_line(80,120,180,120);
  gfx_line(80,120,80,20);
  if(sqrt(pow(lander.xvel,2)+pow(lander.yvel,2))*M_PI/40 < M_PI/2){
    gfx_line(80,120,80+90*cos(sqrt(pow(lander.xvel,2)+pow(lander.yvel,2))*M_PI/40),120-90*sin(sqrt(pow(lander.xvel,2)+pow(lander.yvel,2))*M_PI/40));
  }
  
  //Alert Indicators
  if(lander.fuel < 20 && lander.fuel > 10){
    gfx_color(255,0,0);
    gfx_line(30,104,30,108);
    gfx_line(31,104,31,108);
    gfx_line(30,110,30,111);
    gfx_line(31,110,31,111);
    gfx_color(255,255,255);
  }
  
  if(lander.fuel < 10 && alternator > 0){
    gfx_color(255,0,0);
    gfx_line(30,104,30,108);
    gfx_line(31,104,31,108);
    gfx_line(30,110,30,111);
    gfx_line(31,110,31,111);
    gfx_color(255,255,255);
  }
  
  if(sqrt(pow(lander.xvel,2)+pow(lander.yvel,2))*M_PI/40 < M_PI/2 && sqrt(pow(lander.xvel,2)+pow(lander.yvel,2))*M_PI/40 > 3*M_PI/8){
    gfx_color(255,0,0);
    gfx_line(90,104,90,108);
    gfx_line(91,104,91,108);
    gfx_line(90,110,90,111);
    gfx_line(91,110,91,111);
    gfx_color(255,255,255);
  }
  
  if(sqrt(pow(lander.xvel,2)+pow(lander.yvel,2))*M_PI/40 > M_PI/2 && alternator > 0){
    gfx_color(255,0,0);
    gfx_line(90,104,90,108);
    gfx_line(91,104,91,108);
    gfx_line(90,110,90,111);
    gfx_line(91,110,91,111);
    gfx_color(255,255,255);
  }

}

int main(void){


  
  struct ship lander;
  
  int terrain[WSIZEX];
  int i;
  
  srand(time(0));

  gfx_open(WSIZEX,WSIZEY,"Lunar Lander");

  lander.xloc = rand()%1100+200;
  lander.yloc = rand()%200+50;
  lander.xvel = rand()%6-3;
  lander.yvel = rand()%6-3;
  lander.angle = M_PI/2;
  lander.omega = 0;
  lander.size = 20;
  lander.fuel = rand()%20+80;
  lander.mass = MASS + lander.fuel/4;
  lander.thrust = 0;
  
  int impact = 0;
  int alternator = 0;
  
  terrain[1] = 600;
  for(i = 2; i < WSIZEX; i++){
     terrain[i] = terrain[i-1]+rand()%5-2; 
  }
  
  render_terrain( terrain );
  
  render_ship( lander );
  
  gfx_flush();

  while(!impact){
    //Update properties
    if (lander.yloc < terrain[(int)lander.xloc]-lander.size){
      lander.xvel -= (lander.thrust*cos(lander.angle)/(lander.mass))*TIME;
      lander.yvel += (GRAV - lander.thrust*sin(lander.angle)/(lander.mass))*TIME;
      lander.xloc += lander.xvel*TIME;
      lander.yloc += lander.yvel*TIME;
      lander.angle += lander.omega*TIME;
      
      lander.mass = MASS + lander.fuel/4;
      if (lander.thrust < 100){
        lander.fuel -= lander.thrust/100*TIME;
      }else{
        lander.fuel -= 2*lander.thrust/100*TIME;
      }
      if (lander.fuel <= 0 && lander.thrust > 0){
        lander.thrust -= 10;
      }
      
      alternator++;
      if (alternator >= 6){
        alternator = -6;
      }
    }else{
      impact = 1;
    }
    //Check input
    if (gfx_event_waiting()){
      char c = gfx_wait();
      switch (c){
        case 'Q':
        case 'a':
          lander.omega -= M_PI/24;
          break;
        case 'S':
        case 'd':
          lander.omega += M_PI/24;
          break;
        case 'R':
        case 'w':
          if (lander.thrust < 100 && lander.fuel > 0){
            lander.thrust += 20;
          }else if(lander.thrust < 150){
            lander.thrust += 10;
          }
          break;
        case 'T':
        case 's':
          if (lander.thrust > 0 && lander.thrust <= 100 && lander.fuel > 0){
            lander.thrust -= 20;
          }else if(lander.thrust > 100){
            lander.thrust -= 10;
          }
          break;
      }
    }
    //Render display
    gfx_clear();
    render_terrain( terrain );
    render_ship( lander );
    render_hud( lander, alternator );
    gfx_flush();
    //Pause
    usleep(TIME*1000000);
  }
  
  if(sqrt(pow(lander.xvel,2)+pow(lander.yvel,2))*M_PI/40 < 3*M_PI/8 && lander.angle > 3*M_PI/8 
     && lander.angle < 5*M_PI/8 && lander.omega < M_PI/12 && lander.omega > -M_PI/12){
    gfx_point(lander.xloc+lander.size/2*cos(lander.angle+M_PI/6), lander.yloc-lander.size/2*sin(lander.angle+M_PI/6));
    gfx_point(lander.xloc+lander.size/2*cos(lander.angle-M_PI/6), lander.yloc-lander.size/2*sin(lander.angle-M_PI/6));
    gfx_line(lander.xloc+lander.size/2*cos(lander.angle+3*M_PI/6), lander.yloc-lander.size/2*sin(lander.angle+3*M_PI/6),
             lander.xloc+lander.size/2*cos(lander.angle+5*M_PI/6), lander.yloc-lander.size/2*sin(lander.angle+5*M_PI/6));
    gfx_line(lander.xloc+lander.size/2*cos(lander.angle+5*M_PI/6), lander.yloc-lander.size/2*sin(lander.angle+5*M_PI/6),
             lander.xloc+lander.size/2*cos(lander.angle+7*M_PI/6), lander.yloc-lander.size/2*sin(lander.angle+7*M_PI/6));
    gfx_line(lander.xloc+lander.size/2*cos(lander.angle+7*M_PI/6), lander.yloc-lander.size/2*sin(lander.angle+7*M_PI/6),
             lander.xloc+lander.size/2*cos(lander.angle+9*M_PI/6), lander.yloc-lander.size/2*sin(lander.angle+9*M_PI/6));
    gfx_flush();
  }else{
    while(lander.size >= 1){
      gfx_clear();
      lander.size--;
      render_terrain( terrain );
      render_ship( lander );
      gfx_flush();
      usleep(TIME*1000000);
    }
    gfx_clear();
    render_terrain( terrain );
    gfx_flush();
  }
  usleep(3000000);

}
