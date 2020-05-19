#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>

#include <time.h>
#include "makroipromenljive.h"
#include "objekti.h"

void chooseRandomXYBox();
void chooseRandomXYDiamond();

bool isInMap(float x,float y);
bool kolizija(float x1,float y1,float x2,float y2);

bool isCollision();



