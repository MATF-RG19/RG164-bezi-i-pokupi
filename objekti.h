#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
//#include "funkcije.h"
#include "makroipromenljive.h"

bool isInMap(float x,float y);

void chooseRandomXYDiamond();

void drawPlayer();

void movePlayer();

void drawDiamond();

void drawRunner();

void drawBox();

bool istaStranaPraveD(float x1,float y1,float x2,float y2,float x,float y);


