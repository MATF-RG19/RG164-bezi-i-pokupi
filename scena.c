#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
//#include "test.h"

#define TOCKICI_TIMER 0
#define LRUKA_TIMER 1
#define DRUKA_TIMER 2

#define X_MAX_POS 3.57
#define Y_MAX_NEG 3.93
#define Y_MAX_POS 3.48
#define X_MAX_NEG 4.02

#define KORAK_IGRACA 0.05


int brPoeni=0;

int rukeFlag=1;

static void onDisplay(void);
static void onKeyboard(unsigned char key,int x,int y);
static void onReshape(int width,int height);
static void onTimer(int value);

static void drawPlayer();
static void movePlayer();
static void drawDiamond();
static void chooseRandomXYDiamond();

bool isCollision();
bool isInMap(float x,float y){
	if(x >=0 && y<0){
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
	}
	return true;
}

float horisontal=0,vertical=0;

float diamondX,diamondY;

int preX,preY;

//static int _width,_height;

int ongoing=false;

//crtanje koordinatnih osi za test
static void drawLines();

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(100,100);
	
	glutCreateWindow("Bezi i pokupi");
	preX=preY=-500;
	diamondX=-500,diamondY=-500;
	chooseRandomXYDiamond();
	
	glutKeyboardFunc(onKeyboard);
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	glClearColor(0,0,0,0);
	
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}

static void onDisplay(void){
	//ispis("Bilo koja poruka");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//pomocna funkcija za iscrtavanje koordinatnih osa
	
	//glViewport(0,0,width,height);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 0, 3,
            -0.1, -0.1, 0,
            0, 0, -1
        );
	
	drawLines();
	drawDiamond();
	drawPlayer();
	
	glutSwapBuffers();
}

static void onKeyboard(unsigned char key,int x,int y){
	switch(key){
		case 27:
			exit(0);
			break;
		/*case 'g':
		case 'G':*/
		case 'w':
		case 'W':
			//GORE
			vertical+=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 's':
		case 'S':
			//DOLE
			vertical-=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 'a':
		case 'A':
			//LEVO
			horisontal-=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 'd':
		case 'D':
			//DESNO
			horisontal+=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		default:
			break;
	}
	//Provera za svaku od strana levo desno gore dole da li se igrac nalazi jos uvek na mapi
	//Svedeno na proveru da li tacka tj. pozicija igraca na kojoj se on trenutno nalazi pripada nekom od odgovarajucih trouglova
	if(horisontal >=0 && vertical<0){
		if(((vertical+Y_MAX_NEG)*X_MAX_POS-Y_MAX_NEG*horisontal)<0){
			horisontal=0;
			vertical=0;
		}
	}
	if(horisontal>=0 && vertical>=0){
		if(((-1*vertical*X_MAX_POS)-(Y_MAX_POS*(horisontal-X_MAX_POS)))<0){
			horisontal=0;
			vertical=0;
		}
	}
	if(horisontal<0 && vertical>=0){
		if(((-1*X_MAX_NEG*(vertical-Y_MAX_POS))+Y_MAX_POS*horisontal)<0){
			horisontal=0;
			vertical=0;
		}
	}
	if(horisontal<0 && vertical<0){
		if(X_MAX_NEG*vertical+Y_MAX_NEG*(horisontal+X_MAX_NEG)<0){
			horisontal=0;
			vertical=0;
		}
	}
	
	movePlayer();
	printf("%f %f\n",horisontal,vertical);
}
	
static void onReshape(int width,int height){
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            90,
            width/(float)height,
            1, 5);
    
    glutPostRedisplay();
}

static void drawPlayer(){
	GLUquadric* levi=gluNewQuadric();
	//GLUquadric* desni=gluNewQuadric();
	
	glTranslatef(horisontal,vertical,0);
	glPushMatrix();//cela figura
	/*glPushMatrix();//podnozje
	glutTimerFunc(1,onTimer,TOCKICI_TIMER);
	glPushMatrix();
	
	glColor3f(0,1,0);
	glTranslatef(-.18,-0.22,0);
	glRotatef(90,0,1,0);
	gluCylinder(levi,0.1,0.1,0.3,20,20);
	glPopMatrix();
	glPopMatrix();*///kraj podnozja
	glColor3f(1,0,0);
	glPushMatrix();//glava
	glTranslatef(0,0.2,0);
	glutSolidSphere(0.1,100,100);
	glPopMatrix();//kraj glave
	
	glPushMatrix();//telo
	glColor3f(0,1,0);
	GLUquadric* levaRuka=gluNewQuadric();
	GLUquadric* desnaRuka=gluNewQuadric();
	glPushMatrix();//leva ruka
	glRotatef(15,0,0,1);
	//glutTimerFunc(10,onTimer,LRUKA_TIMER);
	glTranslatef(0.1,0,0);
	glRotatef(90,0,1,0);
	gluCylinder(levaRuka,0.035,0.035,0.22,20,20);
	glPopMatrix();//kraj leve ruke
	glPushMatrix();//desna ruka
	//glRotatef(-15,0,0,1);
	//glutTimerFunc(10,onTimer,DRUKA_TIMER);
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
	
}

static void movePlayer(){
	drawPlayer();
	
	glutPostRedisplay();
}

static void drawLines(){
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
}

static void onTimer(int value){
	if(value==TOCKICI_TIMER){
		printf("IPAK SE OKRECE!\n");
		glRotatef(23,1,0,0);
	}
	if(value==LRUKA_TIMER){
		if(rukeFlag){
			glRotatef(15,0,0,1);
			//rukeFlag=!rukeFlag;
		}
		else{
			glRotatef(-15,0,0,1);
		}
	}
	if(value==DRUKA_TIMER){
		if(rukeFlag){
			glRotatef(-15,0,0,1);
			//rukeFlag=!rukeFlag;
		}
		else{
			glRotatef(15,0,0,1);
		}
	}
}

static void drawDiamond(){
	//GLUquadric *diamond=gluNewQuadric();
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



static void chooseRandomXYDiamond(){
	/*if(diamondX >-500 && diamondY>-500){
		preX=diamondX;
		preY=diamondY;
	}*/
	int znakX,znakY;
	float rx,ry,dr;
	while(!isInMap(diamondX,diamondY)){
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
		printf("X:%f,Y:%f\n",diamondX,diamondY);
	}
}


	
bool isCollision(){
	if(fabs(horisontal-diamondX)<0.3 && fabs(vertical-diamondY)<0.3){
		diamondX=diamondY=-500;
		chooseRandomXYDiamond();
		brPoeni++;
		printf("Poeni:%i\n",brPoeni);
		//drawDiamond();
		
		if(brPoeni==10){
			return true;
		}
	}
	return false;
}
