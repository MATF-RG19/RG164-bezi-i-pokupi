#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
#include "funkcije.h"
#include "makroipromenljive.h"

#include "objekti.h"
#include "pozivnefunkcije.h"



int main(int argc,char** argv){
	ugao=0;
	ongoing=false;
	isWin=false;
	animationParameter=0;
	runnerX=RUNNER_POC;
	runnerY=RUNNER_POC;
	inicijalizujTemena();
	horisontal=-1;
	vertical=-1;
	rukeFlag=1;
	brPoeni=0;
	boxFlag=-1;
	indikator=-1,preind=-1;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SIZE,SIZE);
	glutInitWindowPosition(100,100);
	
	glutCreateWindow("Bezi i pokupi");
	
	diamondX=-500,diamondY=-500;
	chooseRandomXYDiamond();
	//printf("BOX X:%f,Y:%f\n",boxX,boxY);
	//printf("Runner interval%i\n",RUNNER_INTERVAL);
	//chooseRandomXYBox();
	zivot=1;
	chooseRandomXYBox();
	glutKeyboardFunc(onKeyboard);
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	glClearColor(0,0,0,0);
	//glutTimerFunc(1,onTimer,RUNNER_TIMER);
	
	
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}



