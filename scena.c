#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
#include "test.h"



int rukeFlag=1;

static void onDisplay(void);
static void onKeyboard(unsigned char key,int x,int y);
static void onReshape(int width,int height);
static void onTimer(int value);

static void drawPlayer();
static void movePlayer();
static void drawDiamond();

static void drawRunner();

bool isCollision();

float horisontal=0,vertical=0;



float runnerX=RUNNER_POC,runnerY=RUNNER_POC;

//static int _width,_height

bool ongoing=false;


int main(int argc,char** argv){
	brPoeni=0;
	boxFlag=-1;
	openBox=0;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512,512);
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
	
	
		
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}

static void onDisplay(void){
	//ispis("Bilo koja poruka");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//pocetak inicijalizacije svetla
	/*GLfloat light_position[] = { 0, 0, 1, 0 };
    GLfloat light_ambient[] = { 0, 0, 0, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 0.2, 0.2, 0.2, 1 };*/
    //kraj inicijalizacije svetla

    
    /*GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.7, 1 };

   
    GLfloat diffuse_coeffs[] = { 1, 1, 0, 1 };

    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    
   GLfloat shininess = 30;

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glShadeModel(GL_FLAT);*/
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*gluLookAt(
            0, 0, 3,
            -0.1, -0.1, 0,
            0, 0, -1
        );*/
    gluLookAt(
            0, 0, 3,
            -0.1, -0.1, 0,
            0, 0, -1
        );
	//if(boxFlag==1)
		//drawBox();
		//u onDisplay ne sme da stoji drawBox
	/*if((zivot<3 && zivot>0) || zivot==3)
		glutTimerFunc(BOX_INTERVAL,onTimer,BOX_TIMER);*/
	//drawBox();
	if(zivot==1){
		//boxX=boxY=0;
		glPushMatrix();
		
		drawBox();
		glPopMatrix();
	}
	drawLines();
	drawDiamond();
	drawRunner();
	drawPlayer();
	if(kolizija(horisontal,vertical,boxX,boxY)){
		boxFlag=1;
	}
	//if(kolizija(horisontal,vertical,runnerX,runnerY))zivot--;
	if(zivot==0){
		printf("izgubili ste\n");
		exit(0);
	}
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
			rukeFlag*=-1;
			vertical+=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 's':
		case 'S':
			//DOLE
			rukeFlag*=-1;
			vertical-=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 'a':
		case 'A':
			//LEVO
			rukeFlag*=-1;
			horisontal-=KORAK_IGRACA;
			
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 'd':
		case 'D':
			//DESNO
			rukeFlag*=-1;
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
	GLUquadric* levaNoga=gluNewQuadric();
	GLUquadric* desnaNoga=gluNewQuadric();
	//glScalef(3,3,3);//pomocno skaliranje
	glTranslatef(horisontal,vertical,0);
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
	
}

static void movePlayer(){
	drawPlayer();
	
	glutPostRedisplay();
}





static void onTimer(int value){
	
	/*if(value!=RUNNER_TIMER){
		//horisontal,vertical,runnerX,runnerY
		runnerX+=((horisontal-runnerX)/fabs(horisontal-runnerX))*KORAK_IGRACA/3;
		runnerY+=((vertical-runnerY)/fabs(vertical-runnerY))*KORAK_IGRACA/3;
		printf("Runner: %f,%f\n",runnerX,runnerY);
		//drawRunner();
		//glutPostRedisplay();
		//glutTimerFunc(RUNNER_INTERVAL,onTimer,RUNNER_TIMER);
	}*/
	//if(value==BOX_TIMER){
		//boxFlag*=-1;
		//printf("Pozdrav iz box timera\n");
		//printf("BOX X:%f,Y:%f\n",boxX,boxY);
		//glPushMatrix();
	
	//chooseRandomXYBox();
		/*drawBox();
		glPopMatrix();
		glutPostRedisplay();
		glutTimerFunc(BOX_INTERVAL,onTimer,BOX_TIMER);
	}*/
	//else return;
}

static void drawDiamond(){
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

static void drawRunner(){
	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(runnerX,runnerY,0);
	GLUquadric* levaNoga=gluNewQuadric();
	GLUquadric* desnaNoga=gluNewQuadric();
	//glScalef(3,3,3);//pomocno skaliranje
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
