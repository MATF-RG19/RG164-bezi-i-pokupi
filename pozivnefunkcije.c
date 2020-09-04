//fajl koji implementira funkcije iz pozivnefunkcije.h

#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
#include "funkcije.h"
#include "makroipromenljive.h"

#include "objekti.h"


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
	if(value!=1)
		return;
	//if(animationParameter>=3)
		//return;
	if(value==1){
		//drawRunner();
		runnerX+=((horisontal-runnerX)/fabs(horisontal-runnerX))*KORAK_IGRACA*0.3;
		runnerY+=((vertical-runnerY)/fabs(vertical-runnerY))*KORAK_IGRACA*0.3;
		//printf("RUNNER: (%.4f,%.4f)\n",runnerX,runnerY);
		glutPostRedisplay();
		glutTimerFunc(500,onTimer,1);
	}
}

void onDisplay(void){//callback funkcija za prikazivanje
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
    
    /*if(isWin){
    	glutTimerFunc(10,onTimer,1);
    }*/
    
    gluLookAt(
            0, 0, 3-animationParameter,
            -0.1,-0.1,0,//(-0.1,-0.1,0)
            0, 0, -1
        );
    /*gluLookAt(
            -1, -1, 0.3,
            0, 0, 0,
            1, 1, 0
        );*///pomocni LookAt
	/*if(zivot==1){
		//boxX=boxY=0;
		glPushMatrix();
		
		
		glPopMatrix();
	}*/
	drawLines();
	//chooseRandomXYDiamond();
	drawDiamond();
	glutTimerFunc(500,onTimer,1);
	drawRunner();
	//glutTimerFunc(10,onTimer,1);
	drawPlayer();
	if(kolizija(horisontal,vertical,diamondX,diamondY)){
		brPoeni++;
		diamondX=diamondY=-500;
		printf("Poeni:%i,%i\n",brPoeni,brPoeni==3);
		if(brPoeni==3){
			printf("Pobedili ste!\n");
			exit(0);
		}
		chooseRandomXYDiamond();
		drawDiamond();
	}
	
	if(kolizija(horisontal,vertical,runnerX,runnerY)){
		
		runnerX=runnerY=RUNNER_POC;
		zivot--;
	}
	if(zivot==0){
		printf("izgubili ste\n");
		exit(0);
	}
	glMultMatrixf(matrix);

    /* Primjenjuje se translacija koja ce centrirati scenu. */
    glTranslatef(-3, -2.5, 0);

    /* Crtaju se vrata kuce. */
    
    /* Crta se zid kuce. */
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(-14, -14);
        glVertex3f(-7, -7, -0.3);

        glTexCoord2f(28, 0);
        glVertex3f(14, 0, -0.3);

        glTexCoord2f(28, 10);
        glVertex3f(28, 7, -0.3);

        glTexCoord2f(0, 14);
        glVertex3f(0, 7, -0.3);
    glEnd();

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);
	glutSwapBuffers();
}

void onKeyboard(unsigned char key,int x,int y){
	switch(key){
		case 27:
			exit(0);
			glDeleteTextures(2, names);
			break;
		case 'w':
		case 'W':
			//GORE
			preind=indikator;
			indikator=4;
			rukeFlag*=-1;
			vertical+=KORAK_IGRACA;
			horisontal+=KORAK_IGRACA;
			/*if(isCollision()){
				printf("Pobeda\n");
			}*/
			break;
		case 's':
		case 'S':
			//DOLE
			preind=indikator;
			indikator=2;
			rukeFlag*=-1;
			vertical-=KORAK_IGRACA;
			horisontal-=KORAK_IGRACA;
			/*if(isCollision()){
				printf("Pobeda\n");
			}*/
			break;
		case 'a':
		case 'A':
			//LEVO
			preind=indikator;
			indikator=1;
			rukeFlag*=-1;
			horisontal-=KORAK_IGRACA;
			vertical+=KORAK_IGRACA;
			/*if(isCollision()){
				printf("Pobeda\n");
			}*/
			break;
		case 'd':
		case 'D':
			//DESNO
			preind=indikator;
			indikator=3;
			rukeFlag*=-1;
			horisontal+=KORAK_IGRACA;
			vertical-=KORAK_IGRACA;
			/*if(isCollision()){
				printf("Pobeda\n");
			}*/
			break;
		default:
			break;
	}
	//printf("Ind %i,Pre %i\n",indikator,preind);
	//Provera za svaku od strana levo desno gore dole da li se igrac nalazi jos uvek na mapi
	//Svedeno na proveru da li tacka tj. pozicija igraca na kojoj se on trenutno nalazi pripada nekom od odgovarajucih trouglova
		
	if(horisontal >=0 && vertical<0){
		
		if(istaStranaPrave(0,0,0,-4.6,3.9,0.6)==false){
			horisontal=vertical=0;
		}
	}
	if(horisontal>=0 && vertical>=0){
		if(istaStranaPrave(3.5,0,0,3.5,0,0)==false){
			horisontal=vertical=0;
		}
	}
	if(horisontal<0 && vertical>=0){
		if(istaStranaPrave(-4.6,0,0,0,0.33,3.68)==false){//-1.2,0
			horisontal=0;
			vertical=0;
		}
	}
	if(horisontal<0 && vertical<0){
		if(istaStranaPrave(-4.42,0,0,-4.37,0,0)==false){
			horisontal=0;
			vertical=0;
		}
	}
	
	//gore || levo || dole || desno
	
	
	if(preind!=-1)
		switch(preind-indikator){
		//case 0:break;
		case 1:
		case -3:ugao+=-90;break;
		case 2:
		case -2:ugao+=180;break;
		case -1:
		case 3:ugao+=90;break;
		default: break;
		} 
	else switch(indikator){
		case 1:ugao=-90;break;
		case 2:ugao=0;break;
		case 3:ugao=90;break;
		case 4: ugao=180;break;
		} 
	
	
	
	movePlayer();
	
	printf("X:%f Y:%f\n",horisontal,vertical);
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

