#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>

#include <time.h>

#define RUNNER_TIMER 0
#define LRUKA_TIMER 1
#define DRUKA_TIMER 2
#define BOX_TIMER 3

#define X_MAX_POS 3.57
#define Y_MAX_NEG 3.93
#define Y_MAX_POS 3.48
#define X_MAX_NEG 4.02

#define KORAK_IGRACA 0.05
#define RUNNER_INTERVAL 2500
#define BOX_INTERVAL 1000

#define RUNNER_POC -15

float diamondX,diamondY;

int zivot;

int boxFlag,openBox;

float boxX,boxY;

int brPoeni;
void chooseRandomXYBox();
void chooseRandomXYDiamond();
void drawLines();
//void ispis();
bool isInMap(float x,float y);
bool kolizija(float x1,float y1,float x2,float y2);
void drawBox();
