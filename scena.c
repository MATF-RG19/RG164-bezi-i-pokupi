#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
//#include "test.h"

static void onDisplay(void);
static void onKeyboard(unsigned char key,int x,int y);
static void onReshape(int width,int height);
//static void onTimer(void);

static void drawPlayer();

static int _width,_height;

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(100,100);
	
	glutCreateWindow("Bezi i pokupi");
	
	
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
	
	//glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            60,
            _width/(float)_height,
            1, 5);
            glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            1, 2, 3,
            0, 0, 0,
            0, 1, 0
        );
	
	drawPlayer();
	glutSwapBuffers();
}

static void onKeyboard(unsigned char key,int x,int y){
	switch(key){
		case 27:
			exit(0);
			break;
		default:
			fprintf(stderr,"Greska pogresno dugme\n");
			exit(1);
			break;
	}
}
	
static void onReshape(int width,int height){
	_width=width;
	_height=height;
    //glutPostRedisplay();
}

static void drawPlayer(){
	glTranslatef(-1,-1,0);
	glPushMatrix();
	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef(0,0.3,0);
	glutSolidSphere(0.1,100,100);
	glPopMatrix();
	glPushMatrix();
	
	glScalef(0.3,0.3,0.3);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}
