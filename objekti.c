//fajl koji implementira funkcije iz objekti.h

#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
//#include "funkcije.h"
#include "makroipromenljive.h"

//funkcija za iscrtavanje glavnog igraca
void drawPlayer(){
	GLUquadric* levaNoga=gluNewQuadric();
	GLUquadric* desnaNoga=gluNewQuadric();
	GLUquadric* levaRuka=gluNewQuadric();
	GLUquadric* desnaRuka=gluNewQuadric();
	
	glScalef(1+animationParameter,1+animationParameter,1+animationParameter);//pomocno skaliranje
	
	
	glPushMatrix();//glavna translacija
	
	glTranslatef(horisontal,vertical,0);
	
	if(vertical<0){
		glRotatef(-(30+-1*vertical*2),1,0,0);
	}
	
	if(horisontal<-1.1 && vertical>0){
		glScalef((1+horisontal/20),(1+horisontal/20),(1+horisontal/20));
		glRotatef(horisontal*-10,0,1,0);
	}
	
	if(horisontal>1.1){
		glScalef((1+horisontal/20),(1+horisontal/20),(1+horisontal/20));
		glRotatef(horisontal*-10,0,1,0);
	}
	
	if(vertical>2){
		glScalef(2/vertical,2/vertical,2/vertical);
	}
	
	if(vertical<-3){
		glScalef(-3/vertical,-3/vertical,-3/vertical);
	}
	
	glRotatef(-30,0,0,1);//ispravljanje levo-desno
	glPushMatrix();//rotacija za ugao
	glRotatef(ugao,0,0,1);
	glPushMatrix();//stavljanje u prostor
	glRotatef(90,1,0,0);
	glPushMatrix();//cela figura
	
	glPushMatrix();//jedna noga 
	glRotatef(15*rukeFlag,1,0,0);
	glTranslatef(-0.1,-0.1,0);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	gluCylinder(desnaNoga,0.035,0.035,0.15,20,20);
	glPopMatrix();//kraj jedne noge
	
	glPushMatrix();//druga noga
	
	glRotatef(-15*rukeFlag,1,0,0);
	glTranslatef(0.1,-0.1,0);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	
	gluCylinder(levaNoga,0.035,0.035,0.15,20,20);
	glPopMatrix();//kraj druge noge
	
	glColor3f(1,0,0);
	glPushMatrix();//glava
	glTranslatef(0,0.3,0);
	glutSolidSphere(0.1,100,100);
	glPopMatrix();//kraj glave
	glPushMatrix();//leva ruka
	glTranslatef(0.15,0,0);
	glRotatef(-45,0,0,1);
	//glRotatef(-45,1,0,0);
	glRotatef(90,0,1,0);
	gluCylinder(levaRuka,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj leve ruke
	
	glPushMatrix();//desna ruka
	//glRotatef(45,1,0,0);
	//glRotatef(90,0,1,0);
	
	glTranslatef(-0.15,0,0);
	//glRotatef(90,1,0,0);
	glRotatef(45,0,0,1);
	glRotatef(-90,0,1,0);
	gluCylinder(desnaRuka,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj desne ruke
	glPushMatrix();//telo
	glColor3f(0,1,0);
	rukeFlag=!rukeFlag;
	//glavni deo tela
	glColor3f(1,1,0);
	glScalef(0.3,0.3,0.3);
	glutSolidSphere(0.6,20,20);
	glPopMatrix();//kraj tela
	
	glPopMatrix();//kraj cele figure
	
	glPopMatrix();//stavljanje u prostor
	glPopMatrix();//rotacija za ugao
	glPopMatrix();//glavna translacija
	
	
}

//funkcija za kretanje igraca
void movePlayer(){
	drawPlayer();
	
	glutPostRedisplay();
}

bool istaStranaPraveD(float x1,float y1,float x2,float y2,float x,float y){
	if(((x2-x1)*(diamondY-y1)-(y2-y1)*(diamondX-x1))<0)
		return false;
	if(((x1-x)*(diamondY-y)-(diamondX-x)*(y1-y))<0)
		return false;
	if(((-x2+x)*(diamondY-y2)-(-x2+diamondX)*(-y2+y))<0)
		return false;
	return true;
}


bool isInMap(float x,float y){
	if(x >=0 && y<0){
		
		if(istaStranaPraveD(0,0,0,-4.6,3.9,0.6)==false){
			return false;
		}
	}
	if(x>=0 && y>=0){
		if(istaStranaPraveD(3.5,0,0,3.5,0,0)==false){
			return false;
		}
	}
	if(x<0 && y>=0){
		if(istaStranaPraveD(-4.6,0,0,0,0.33,3.68)==false){//-1.2,0
			return false;
		}
	}
	if(x<0 && y<0){
		if(istaStranaPraveD(-4.42,0,0,-4.37,0,0)==false){
			return false;
		}
	}
	return true;
}


void chooseRandomXYDiamond(){
	int znakX,znakY;
	int rx,ry;float dr;
	while(!isInMap(diamondX,diamondY)){
	srand(time(NULL));
	rx=rand()%4;
	ry=rand()%4;
	dr=(((float)(rand()%1000))/1000);
		//printf("rovi je %f,%f,%f\n",rx,ry,dr);
	
	switch(rx){
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
		//printf("DX:%f,DY:%f\n",diamondX,diamondY);
	}
}

//funkcija za iscrtavanje diamonda
void drawDiamond(){
	printf("Usao je \n");
	//diamondX=diamondY=-500;
	//chooseRandomXYDiamond();         
	glColor3f(1,0.3,0.3);
	glPushMatrix();//pocetak za ceo diamond
	glTranslatef(diamondX,diamondY,0);
	glRotatef(90,1,0,0);
	glPushMatrix();//pocetak za prvi diamond
	glTranslatef(-0.1,0,0);
	glRotatef(180,0,1,0);
	
	glScalef(0.15,0.15,0.15);
	glutSolidTetrahedron();
	glPopMatrix();//kraj za prvi diamond
	glPushMatrix();//pocetak za drugi diamond
	//glTranslatef(diamondX,diamondY,0);
	glScalef(0.15,0.15,0.15);
	glutSolidTetrahedron();
	glPopMatrix();//kraj za drugi diamond
	glPopMatrix();//kraj za ceo diamond
	//glutPostRedisplay();
}

void drawRunner(){
	
	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(runnerX,runnerY,0);
	glRotatef(90,1,0,0);
	GLUquadric* levaNoga=gluNewQuadric();
	GLUquadric* desnaNoga=gluNewQuadric();
	//glScalef(3,3,3);//pomocno skaliranje
	
	glPushMatrix();//cela figura
	glPushMatrix();//podnozje
	glPushMatrix();//jedna noga
	glRotatef(35*rukeFlag,1,0,0);
	glTranslatef(-0.1,-0.1,0);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	gluCylinder(desnaNoga,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj jedne noge
	
	glPushMatrix();//druga noga
	glRotatef(-35*rukeFlag,1,0,0);
	glTranslatef(0.1,-0.1,0);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	
	gluCylinder(levaNoga,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj druge noge
	glPopMatrix();//kraj podnozja
	
	glPushMatrix();//glava
	glTranslatef(0,0.2,0);
	glutSolidSphere(0.1,100,100);
	glPopMatrix();//kraj glave
	glPushMatrix();//telo
	GLUquadric* levaRuka=gluNewQuadric();
	GLUquadric* desnaRuka=gluNewQuadric();
	glPushMatrix();//leva ruka
	glRotatef(15,0,0,1);
	glTranslatef(0.1,0,0);
	glRotatef(90,0,1,0);
	gluCylinder(levaRuka,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj leve ruke
	glPushMatrix();//desna ruka
	glTranslatef(-0.3,0,0);
	glRotatef(90,0,1,0);
	gluCylinder(desnaRuka,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj desne ruke
	rukeFlag=!rukeFlag;
	
	glColor3f(1,1,0);
	glScalef(0.3,0.3,0.3);
	glutSolidSphere(0.5,20,20);
	//kraj glavnog dela tela
	glPopMatrix();//kraj tela
	glPopMatrix();//kraj cele figure
	glPopMatrix();

}



