#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

static void onDisplay(void);
static void onKeyboard(unsigned char key,int x,int y);
//static void onTimer(void);

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024,1024);
	glutInitWindowPosition(100,100);
	
	glutCreateWindow("Bezi i pokupi");
	
	glutKeyboardFunc(onKeyboard);
	glutDisplayFunc(onDisplay);
	
	glutSwapBuffers();
	
	glutMainLoop();
	return 0;
}

static void onDisplay(void){
	glClearColor(0,0,0,0);
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
	
