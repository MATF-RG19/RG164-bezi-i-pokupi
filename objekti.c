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
	//printf("%i\n",rukeFlag);
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
	glRotatef(90,1,0,0);
	GLUquadric* levaNoga=gluNewQuadric();
	GLUquadric* desnaNoga=gluNewQuadric();
	//glScalef(3,3,3);//pomocno skaliranje
	runnerX+=((horisontal-runnerX)/fabs(horisontal-runnerX))*KORAK_IGRACA;
	runnerY+=((vertical-runnerY)/fabs(vertical-runnerY))*KORAK_IGRACA;
	printf("Runner: %f,%f\n",runnerX,runnerY);
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
