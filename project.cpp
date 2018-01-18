// project.cpp
//Yifan Yu and Horacio Lopez

//instructions: press left or right to control the direction of the movement of the vaccum cleaner
//*** I did not change the color of the different shapes because of blinking problem

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "gfx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "ast_move.h"

#define PI 3.14159265

using namespace std;

void drawSpaceship (double xPos, double yPos, int angle, int length, int rad);
void continueLine(double &p1x, double &p1y, int angle, int rad);

void drawBullet(vector<double> &X,vector<double> &Y,vector<double> &Angle, int wd, int ht);
void reverseOrder(vector<int> &A);

int main(int argc, char *argv[])
{
  int leaderscores;
  vector<int> leaderboard;
  if (argc > 3){
    cout << "ERROR" << endl;
    return 1;
  }
  if (argc == 2 || argc == 3){
    //for ifs entered enteries, properly store and capitalize them in a vector
    ifstream ifs;
    ifs.open(argv[1]);
    //display error and quit program for unfound file
    if(!ifs){
      cout << "ERROR" << endl;
      return 1;
    }

    while(!ifs.eof()){
      ifs >> leaderscores;
      leaderboard.push_back(leaderscores);
    }
    leaderboard.pop_back();
    ifs.close();
    // for (auto it = leaderboard.begin(); it < leaderboard.end(); it++)
    //   cout << *it << endl;
  }

  bool hitShip;

  double speed = 1.0;
  int wd = 650, ht = 650;          // window width and height
  srand (time(NULL));
  int randAngle = rand() % 360;
  double dx = 0;                      // basic increment for animation
  double dy = 0;
  double ddx = cos((randAngle) * PI / 180.0);  // basic increment for animation
  double ddy = sin((randAngle) * PI / 180.0);

  int rad = 10;  // circle's starting center, and its radius
  int len = 15;  // a line showing the direction of the circle's movement
  int deltat = 5000;            // pause time
  char c = 0;                   // key that is pressed

  gfx_open(wd + 300, ht, "Asteroids");   // Open a new window for drawing.
  gfx_color(255,255,0);            // Set the current drawing color.

  int xm = 500;    // get mouse click's x coordinate
  int ym = 500;    // get mouse click's y coordinate

  int frames = 0;
  vector<double> BulletX, BulletY, BulletAngle; //Keeptrack of direction and position of bullets
  double speedControl = 1;  //coefficient that modifies speed
  bool gameover = false;

  int score = 0;
  char scoreStr[33] = "0";

  int  dt = rand() % 10000 + 2500;  //randomize asteroid speed
  Asteroid a1(100, 800, 70, dt);  //generate asteroid
  Asteroid a2(700, 100, 70, dt);
  Asteroid a3(100, 500, 70, dt);

  while(c != 'q') {                // keep going until a 'q' is pressed
  if (!gameover)
  frames++;
  gfx_clear();                   // clear the screen

  gfx_text(wd, 20, "score");    //display score
  gfx_text(wd, 30, scoreStr);


  //Generate a new bullet every 200 frames
  if (frames % 200 == 0)
  {BulletX.push_back(xm + dx);
    BulletY.push_back(ym + dy);
    BulletAngle.push_back(randAngle);
    sprintf(scoreStr, "%d", frames);
    score = frames;
  }

  //detects whether a bullet hits an asteroid
  for (int i = 0; i < BulletX.size(); i++)
  {
    a1.didHit(BulletX[i],BulletY[i]);
    a2.didHit(BulletX[i],BulletY[i]);
    a3.didHit(BulletX[i],BulletY[i]);
  }

  hitShip = (a1.didHitShip(xm+dx,ym+dy)|| a2.didHitShip(xm+dx,ym+dy)|| a3.didHitShip(xm+dx,ym+dy));
  if (hitShip) gameover = true;

  // display all objects on the screen
  if (!gameover){
    drawBullet(BulletX, BulletY,BulletAngle, wd, ht);
    drawSpaceship(xm+dx, ym+dy, randAngle, len, rad);
    a1.display();
    a2.display();
    a3.display();
  }
  //display game over
  if (gameover){
    gfx_text(wd/2 - 5, ht/2, "GAMEOVER");

  }
  gfx_flush();
  usleep(deltat);             // pause



  //add acceleration to the spaceship
  dx += speedControl * ddx;                   // change dx
  dy += speedControl * ddy;                  // change dy

  //move the asteroids around
  a1.travel(wd,ht);
  a2.travel(wd,ht);
  a3.travel(wd,ht);

  // dealing with edge situation: reset the position of the object without going out
  if (xm+dx < rad) dx = rad - xm;
  if (xm+dx > wd - rad) dx = wd - rad - xm;
  if (ym + dy < rad) dy = rad - ym;
  if (ym+dy > ht - rad) dy = ht - rad - ym;

  if(gfx_event_waiting()) {      // if there is an event
    c = gfx_wait();
    if (c == 'Q'){  //userinput left arrow key
      randAngle = randAngle - 10;
      ddx = cos((randAngle) * PI / 180.0);
      ddy = sin((randAngle) * PI / 180.0);
    }
    if (c == 'S'){  //userinput right arrow key
      randAngle = randAngle + 10;
      ddx = cos((randAngle) * PI / 180.0);
      ddy = sin((randAngle) * PI / 180.0);

    }
    if (c == 'R'){  //userinput UP arrow key
      if (speedControl <= 1.5)
      speedControl = speedControl + .2; // change speed coefficient
    }
    if (c == 'T'){  //userinput DOWN arrow key
      if (speedControl > 0)
      speedControl = speedControl - .2; // change speed coefficient
    }
    if (c == '9')
    gameover = true;
  }

}

if (argc == 2 || argc == 3){
  leaderboard.push_back(score);
  //for ifs entered enteries, properly store and capitalize them in a vector
  ofstream ofs;
  if (argc == 2)
  ofs.open(argv[1]);
  if (argc == 3)
  ofs.open(argv[2]);

  //sort and display the top ten scores in the argc file
  sort(leaderboard.begin(), leaderboard.end());
  reverseOrder(leaderboard);
  if (leaderboard.size() >= 10)
  {for (int i = 10; i < leaderboard.size(); i++)
    leaderboard.erase((leaderboard.begin()+i));}
    for (int i = 0; i < leaderboard.size(); i++)
    ofs << leaderboard[i] << endl;

  }
}

//Draw the spaceship given its position, direction and size
void drawSpaceship (double xPos, double yPos, int angle, int length, int rad)
{
  double p1x = xPos + cos((angle) * PI / 180.0) * rad;
  double p1y = yPos + sin((angle) * PI / 180.0) * rad;
  double p2x = xPos + cos((angle - 130) * PI / 180.0) * (rad);
  double p2y = yPos + sin((angle - 130) * PI / 180.0) * (rad);
  gfx_line(p1x, p1y, p2x, p2y);
  gfx_line(p2x, p2y, xPos, yPos);
  double p3x = xPos + cos((angle - 230) * PI / 180.0) * (rad);
  double p3y = yPos + sin((angle - 230) * PI / 180.0) * (rad);
  gfx_line(p1x, p1y, p3x, p3y);
  gfx_line(p3x, p3y, xPos, yPos);

}

//extend a line given its previous postion and its angle and the length
void continueLine(double &p1x, double &p1y, int angle, int rad)
{
  double p2x = p1x + cos((angle) * PI / 180.0) * (rad);
  double p2y = p1y + sin((angle) * PI / 180.0) * (rad);
  gfx_line(p1x, p1y, p2x, p2y);
  p1x = p2x;
  p1y = p2y;
}

void drawBullet(vector<double> &X,vector<double> &Y,vector<double> &Angle, int wd, int ht)
{
  for (int i = 0; i < X.size(); i++){
    X[i] += cos((Angle[i]) * PI / 180.0)*3;
    Y[i] += sin((Angle[i]) * PI / 180.0)*3;
    gfx_circle(X[i], Y[i], 3);

    if (X[i] > wd || X[i] < 1  || Y[i] < 1 || Y[i] > ht)
    {
      X.erase (X.begin()+i);
      Y.erase (Y.begin()+i);
      Angle.erase (Angle.begin()+i);
    }
  }
}

//reverse the order of an int vector
void reverseOrder(vector<int> &A)
{
  vector<int> B = A;
  for (int i = 0; i < A.size(); i++)
  B[i] = A[A.size() - 1 - i];
  A = B;
}
