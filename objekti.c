#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
//#include "funkcije.h"
#include "makroipromenljive.h"

void drawPlayer(){
	GLUquadric* levaNoga=gluNewQuadric();
	GLUquadric* desnaNoga=gluNewQuadric();
	GLUquadric* levaNogaD=gluNewQuadric();
	GLUquadric* desnaNogaD=gluNewQuadric();
	/*if(vertical>0){
		glPushMatrix();
		glRotatef(45,1,0,0);
		glPopMatrix();
	}*/
	
	//glPushMatrix();//za indikatore
	
	glScalef(1.5,1.5,1.5);//pomocno skaliranje
	if(preind!=-1)
		switch(preind-indikator){
		case 0:break;
		case 1:
		case -3:ugao=-90;break;
		case 2:
		case -2:ugao=180;break;
		case -1:
		case 3:ugao=90;break;
		default: break;
		} 
	else switch(indikator){
		case 1:ugao=-90;break;
		case 2:break;
		case 3:ugao=90;break;
		case 4: ugao=180;break;
		} 
	
	
	glPushMatrix();
	
	glTranslatef(horisontal,vertical,0);
	glRotatef(ugao,0,0,1);
	glPushMatrix();
	glRotatef(90,1,0,0);
	glPushMatrix();//cela figura
	glPushMatrix();//podnozje
	glPushMatrix();//jedna noga
	glPushMatrix();//gornji deo 
	glRotatef(15*rukeFlag,1,0,0);
	glTranslatef(-0.1,-0.1,0);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	gluCylinder(desnaNoga,0.035,0.035,0.22,20,20);
	glPopMatrix();//gornji deo
	glPushMatrix();//donji deo 
	glRotatef(-35*rukeFlag,0,1,0);
	glTranslatef(-0.1,-0.3,0.002);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	glColor3f(1,1,1);
	gluCylinder(desnaNogaD,0.03,0.03,0.15,20,20);
	glPopMatrix();//donji deo 
	glPushMatrix();//stopalo
	glColor3f(1,0.7,0.7);
	glRotatef(90,0,1,0);
	glScalef(0.3,2,0.3);
	glTranslatef(-0.15,-0.3,0);
	glutSolidSphere(0.1,20,20);
	glPopMatrix();//stopalo
	glPopMatrix();//kraj jedne noge
	glPushMatrix();//druga noga
	glPushMatrix();//gornji deo druge noge
	glRotatef(-15*rukeFlag,1,0,0);
	glTranslatef(0.1,-0.1,0);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	
	gluCylinder(levaNoga,0.035,0.035,0.22,20,20);
	glPopMatrix();//gornji deo druge noge
	glPushMatrix();//donji deo druge noge
	glRotatef(35*rukeFlag,0,1,0);
	glTranslatef(0.1,-0.2,0);
	glRotatef(180,0,1,0);
	glRotatef(180,1,0,0);
	glRotatef(90,0,0,1);
	glRotatef(90,0,1,0);
	glColor3f(1,1,1);
	gluCylinder(levaNogaD,0.035,0.035,0.22,20,20);
	glPopMatrix();//donji deo druge noge
	glPopMatrix();//kraj druge noge
	glPopMatrix();//kraj podnozja
	glColor3f(1,0,0);
	glPushMatrix();//glava
	glTranslatef(0,0.3,0);
	glutSolidSphere(0.1,100,100);
	glPopMatrix();//kraj glave
	glPushMatrix();//telo
	glColor3f(0,1,0);
	GLUquadric* levaRuka=gluNewQuadric();
	GLUquadric* desnaRuka=gluNewQuadric();
	glPushMatrix();//leva ruka
	glTranslatef(0.18,0.1,0);
	glRotatef(-45,0,0,1);
	
	//glRotatef(30,1,0,0);
	glRotatef(90,0,1,0);
	gluCylinder(levaRuka,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj leve ruke
	glPushMatrix();//desna ruka
	glTranslatef(-0.18,0.1,0);
	glRotatef(-45,0,0,1);
	
	gluCylinder(desnaRuka,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj desne ruke
	rukeFlag=!rukeFlag;
	//printf("%i\n",rukeFlag);
	//glavni deo tela
	glColor3f(1,1,0);
	glScalef(0.3,0.3,0.3);
	glutSolidSphere(0.6,20,20);
	//kraj glavnog dela tela
	glPopMatrix();//kraj tela
	glPopMatrix();//kraj cele figure
	//glPopMatrix();//za indikatore
	glPopMatrix();
	/*glRotatef(-ugao,1,0,0);
	glRotatef(-90,0,1,0);*/
	
}

void movePlayer(){
	drawPlayer();
	
	glutPostRedisplay();
}

void drawDiamond(){
	//GLUquadric *diamond=gluNewQuadric()
	//glutSolidOctahedron();
	glColor3f(1,0.3,0.3);
	glPushMatrix();//pocetak za ceo diamond
	glTranslatef(diamondX,diamondY,0);
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
}

void drawRunner(){
	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(runnerX,runnerY,0);
	GLUquadric* levaNoga=gluNewQuadric();
	GLUquadric* desnaNoga=gluNewQuadric();
	glScalef(3,3,3);//pomocno skaliranje
	runnerX+=((horisontal-runnerX)/fabs(horisontal-runnerX))*KORAK_IGRACA;
	runnerY+=((vertical-runnerY)/fabs(vertical-runnerY))*KORAK_IGRACA;
	//printf("Runner: %f,%f\n",runnerX,runnerY);
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
	//printf("%i\n",rukeFlag);
	//glavni deo tela
	glColor3f(1,1,0);
	glScalef(0.3,0.3,0.3);
	glutSolidSphere(0.5,20,20);
	//kraj glavnog dela tela
	glPopMatrix();//kraj tela
	glPopMatrix();//kraj cele figure
	glPopMatrix();
	//glutTimerFunc(RUNNER_INTERVAL,onTimer,RUNNER_TIMER);
}

void drawBox(){
	//glColor3f(0.5,0.5,0.2);
	//chooseRandomXYBox();
	//printf("drawBox X:%f,Y:%f\n",boxX,boxY);
	//glScalef(3,3,3);
	glTranslatef(boxX,boxY,0);
	
	glPushMatrix();
	//glRotatef(90,1,0,0);
	//glTranslatef(0,1,0);
	//glColor3f(1,1,1);
	//printf("%i\n",openBox);
	/*if(openBox==1){
	glColor3f(1,1,1);
	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(2.2,0.5,1);
	glutSolidCube(0.2);
	glPopMatrix();
	glutPostRedisplay();
	}
	else{*/
		glColor3f(1,0.5,0.2);
		glPushMatrix();
		if(boxFlag==1){
			glColor3f(1,1,1);
			glTranslatef(-0.2,0,0);
		}
		glutSolidCube(0.2);
		glPopMatrix();
		glPushMatrix();
		if(boxFlag==1){
			glColor3f(1,1,1);
			glTranslatef(.2,0,0);
			
		}
		
		glutSolidCube(0.2);
		glPopMatrix();
		//glutPostRedisplay();
	//}
	//glColor3f(0.5,0.5,0.2);
	/*glPushMatrix();
	glScalef(3,1.2,1.8);
	glutSolidCube(0.2);
	glPopMatrix();*/
	glPopMatrix();
	
}
