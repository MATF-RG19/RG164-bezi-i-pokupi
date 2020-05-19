#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
#include "funkcije.h"
#include "makroipromenljive.h"

#include "objekti.h"

void onDisplay(void){
	//Ciscenje bafera
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//pocetak inicijalizacije svetla
	GLfloat light_position[] = { 0, 0, 1, 0 };
    GLfloat light_ambient[] = { 0, 0, 0, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 0.2, 0.2, 0.2, 1 };
    //kraj inicijalizacije svetla
	//pocetak inicijalizacije koeficijenata materijala
    GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.7, 1 };

   
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

    glShadeModel(GL_FLAT);
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(
            0, 0, 3,
            -0.1, -0.1, 0,
            0, 0, -1
        );
	if(zivot==1){
		//boxX=boxY=0;
		glPushMatrix();
		
		drawBox();
		glPopMatrix();
	}
	//drawLines();
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

void onKeyboard(unsigned char key,int x,int y){
	switch(key){
		case 27:
			exit(0);
			break;
		case 'w':
		case 'W':
			//GORE
			preind=indikator;
			indikator=4;
			rukeFlag*=-1;
			vertical+=KORAK_IGRACA;
			horisontal+=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 's':
		case 'S':
			//DOLE
			preind=indikator;
			indikator=2;
			rukeFlag*=-1;
			vertical-=KORAK_IGRACA;
			horisontal-=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 'a':
		case 'A':
			//LEVO
			preind=indikator;
			indikator=1;
			rukeFlag*=-1;
			horisontal-=KORAK_IGRACA;
			vertical+=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		case 'd':
		case 'D':
			//DESNO
			preind=indikator;
			indikator=3;
			rukeFlag*=-1;
			horisontal+=KORAK_IGRACA;
			vertical-=KORAK_IGRACA;
			if(isCollision()){
				printf("Pobeda!\n");
				exit(0);
			}
			break;
		default:
			break;
	}
	printf("Ind %i,Pre %i\n",indikator,preind);
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
	/* *///premestiti uraditi nesto sa ovim zbog rotacije i boljeg prikaza kod kretanja
	movePlayer();
	//printf("%f %f\n",horisontal,vertical);
}
	
void onReshape(int width,int height){
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            90,
            width/(float)height,
            1, 5);
    
    glutPostRedisplay();
}

void onTimer(int value){
	
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
