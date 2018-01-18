// ast_move.cpp
// Horacio Lopez and Yifan Yu
// This is the implementation of the Asteroid class


#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gfx.h"
#include "ast_move.h"
using namespace std;

#define PI 3.14159265

Asteroid::Asteroid(int xcoord, int ycoord, int radius, int deltat)
{	//constructor for an asteroid
	xc = xcoord;
	yc = ycoord;
	r = radius;
	dt = deltat;

	int randAngle = rand() % 360;


	dx =	cos((randAngle) * PI / 180.0);
	dy =  sin((randAngle) * PI / 180.0);
	// cout << dx << endl;
	// cout << dy << endl;

	usleep(deltat);
}
Asteroid::~Asteroid(){}

void Asteroid::travel(int wd, int ht)
{ // asteroid position function
	xc += dx;
	yc += dy;

	// for now, asteroids bounce
	if (yc <= r)
	dy = (-dy);
	if (yc >= ht - r)
	dy = (-dy);
	if (xc <= r)
	dx = (-dx);
	if (xc >= wd - r)
	dx = (-dx);

	if (xc < r) xc = r;
	if (xc > wd - r) xc = wd - r;
	if (yc < r) yc = r;
	if (yc > ht - r) yc = ht - r;
}


void Asteroid::display()
{
	gfx_circle(xc, yc, r);
}

bool Asteroid::didHitShip(int x1, int y1)
{

	if ( pow(pow((x1 - xc),2) + pow((y1 - yc),2),.5) < r)
	return true;
	else
	return false;
}

void Asteroid::didHit(int x1, int y1)
{
	if ( pow(pow((x1 - xc),2) + pow((y1 - yc),2),.5) < r)
	split();
}

void Asteroid::split()
{
	//cout << r << endl;
	if (r > 20) {
		r = r/4;
		int randAngle = rand() % 360;


		dx =	cos((randAngle) * PI / 180.0);
		dy =  sin((randAngle) * PI / 180.0);
	}
	else {
		destroy();
	}
}

//destory and respawn an asteroid
void Asteroid::destroy()
{
	if (rand() % 2){
		xc = rand() % 650;
		yc = 0;
	}
	else
	{
		yc = rand() % 650;
		xc = 0;
	}

	r = 70;
}

int Asteroid::countAst(int number)
{
	number -= 1;
	return number;
}
		//get functions
double Asteroid::getXC()
{
	return xc;
}

double Asteroid::getYC()
{
	return yc;
}

int Asteroid::getR()
{
	return r;
}
