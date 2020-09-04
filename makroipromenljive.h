//heder za deklaraciju promenljivih, definiciju konstanti, koriscenih u programu

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>

#include <time.h>

#define RUNNER_TIMER 0
#define LRUKA_TIMER 1
#define DRUKA_TIMER 2
#define BOX_TIMER 3

#define X_MAX_POS 0.83
#define Y_MAX_NEG 4.93
#define Y_MAX_POS 2.68
#define X_MAX_NEG 4.93

#define KORAK_IGRACA 0.025
#define RUNNER_INTERVAL 2500
#define BOX_INTERVAL 1000

#define RUNNER_POC -6

#define SIZE 900

#define FILENAME1 "apxbk-uorp0.bmp"

/* Identifikatori tekstura. */
GLuint names[2];

int dFlag;

float gdx,gdy,glx,gly,dlx,dly,ddx,ddy;

float diamondX,diamondY;

int zivot;

int boxFlag,openBox;

float boxX,boxY;

float matrix[16];

int brPoeni;

int rukeFlag;
float ugao;

float horisontal,vertical;

float runnerX,runnerY;

bool ongoing;

int indikator,preind;

bool isWin;

float animationParameter;


