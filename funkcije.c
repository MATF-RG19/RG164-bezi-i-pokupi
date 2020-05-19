#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>

#include <math.h>
#include <time.h>

#include "funkcije.h"
#include "makroipromenljive.h"
#include "objekti.h"

/*void drawLines(){
	
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(6,0,0);//crvena je x osa
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,6,0);//zelena je y osa
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_LINES);//plava je z osa
	glVertex3f(0,0,0);
	glVertex3f(0,0,6);
	glEnd();
	
}*/

bool isInMap(float x,float y){
	/*if(x >=0 && y<0){
		if(((y+Y_MAX_NEG)*X_MAX_POS-Y_MAX_NEG*x)<0){
			return false;
		}
	}
	if(x>=0 && y>=0){
		if(((-1*y*X_MAX_POS)-(Y_MAX_POS*(x-X_MAX_POS)))<0){
			return false;
		}
	}
	if(x<0 && y>=0){
		if(((-1*X_MAX_NEG*(y-Y_MAX_POS))+Y_MAX_POS*x)<0){
			return false;
		}
	}
	if(x<0 && y<0){
		if(X_MAX_NEG*y+Y_MAX_NEG*(x+X_MAX_NEG)<0){
			return false;
		}
	}*/
	return true;
}

bool kolizija(float x1,float y1,float x2,float y2){
	if(fabs(x1-x2)<0.3 && fabs(y1-y2)<0.3)
		return true;
	return false;
}

void chooseRandomXYBox(){
	boxX=boxY=-100;
	int znakX,znakY;
	float rx,ry,dr;
	while(!isInMap(boxX,boxY)){
	srand(time(NULL));
	rx=rand()%4;
	ry=rand()%4;
	dr=(((float)(rand()%1000))/1000);
		printf("rovi je %f,%f,%f\n",rx,ry,dr);
	
	switch(brPoeni%4){
		case 0:
			znakX=1;
			znakY=1;
			break;
		case 1:
			znakX=1;
			znakY=-1;
			break;
		case 2:
			znakX=-1;
			znakY=-1;
			break;
		case 3:
			znakX=-1;
			znakY=1;
			break;
	}
		if(rx==3){
			boxX=znakX*rx-znakX*dr;
			if(ry==3){
				boxY=znakY*ry-znakY*dr;
			}
			else {
				boxX=znakY*ry+znakY*dr;
			}
		}
		else if(ry==3){
			boxY=znakY*ry-znakY*dr;
			boxX=znakX*rx+znakX*dr;
		}
		else{
			boxX=znakX*rx+znakX*dr;
			boxY=znakY*ry+znakY*dr;
		}
		printf("RandomBox X:%f,Y:%f\n",boxX,boxY);
	}
}

void chooseRandomXYDiamond(){
	int znakX,znakY;
	float rx,ry,dr;
	while(!isInMap(diamondX,diamondY)){
	srand(time(NULL));
	rx=rand()%4;
	ry=rand()%4;
	dr=(((float)(rand()%1000))/1000);
		//printf("rovi je %f,%f,%f\n",rx,ry,dr);
	
	switch(brPoeni%4){
		case 0:
			znakX=1;
			znakY=1;
			break;
		case 1:
			znakX=1;
			znakY=-1;
			break;
		case 2:
			znakX=-1;
			znakY=-1;
			break;
		case 3:
			znakX=-1;
			znakY=1;
			break;
	}
		if(rx==3){
			diamondX=znakX*rx-znakX*dr;
			if(ry==3){
				diamondY=znakY*ry-znakY*dr;
			}
			else {
				diamondY=znakY*ry+znakY*dr;
			}
		}
		else if(ry==3){
			diamondY=znakY*ry-znakY*dr;
			diamondX=znakX*rx+znakX*dr;
		}
		else{
			diamondX=znakX*rx+znakX*dr;
			diamondY=znakY*ry+znakY*dr;
		}
		//printf("X:%f,Y:%f\n",diamondX,diamondY);
	}
}

bool isCollision(){
	if(fabs(horisontal-diamondX)<0.3 && fabs(vertical-diamondY)<0.3){
		diamondX=diamondY=-500;
		chooseRandomXYDiamond();
		brPoeni++;
		printf("Poeni:%i\n",brPoeni);
		//drawDiamond();
		
		if(brPoeni==6){
			return true;
		}
	}
	return false;
}