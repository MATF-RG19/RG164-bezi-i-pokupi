//heder za pomocne funkcije koriscene u programu

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>

#include <math.h>
#include <time.h>
#include "makroipromenljive.h"
#include "objekti.h"


void chooseRandomXYBox();
void chooseRandomXYDiamond();

bool isInMap(float x,float y);
bool kolizija(float x1,float y1,float x2,float y2);

bool isCollision();

void win();

void drawLines();

bool kolizijaPravaTacka(float x1,float y1,float x2,float y2,float X,float Y);

void inicijalizujTemena();

bool istaStranaPrave(float x1,float y1,float x2,float y2,float x,float y);

bool uKvadratu();

void drawLine(float x1,float y1,float x2,float y2);//pomocna funkcija za iscrtavanje linija
