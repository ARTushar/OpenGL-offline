//
// Created by tushar on 3/16/21.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <GL/glut.h>
#include "DrawShape.h"
#include "Bubbles.h"

int drawaxes;
double angle;

// variable for the bubbles animation
Bubbles bubbles;


void keyboardListener(unsigned char key, int x,int y){
  switch(key){
    case 'p':
      bubbles.toggleAnimation();
      break;
    default:
      break;
  }
}

void specialKeyListener(int key, int x,int y){
  switch(key){
    case GLUT_KEY_DOWN:		//down arrow key
      bubbles.decreaseSpeed();
      break;
    case GLUT_KEY_UP:		// up arrow key
      bubbles.increaseSpeed();
      break;
    default:
      break;
  }
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
  switch(button){
    default:
      break;
  }
}

void display(){
  //clear the display
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0,0,0,0);	//color black
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /********************
  / set-up camera here
  ********************/
  //load the correct matrix -- MODEL-VIEW matrix
  glMatrixMode(GL_MODELVIEW);

  //initialize the matrix
  glLoadIdentity();

  //now give three info
  //1. where is the camera (viewer)?
  //2. where is the camera looking?
  //3. Which direction is the camera's UP direction?

  double squareLength = bubbles.getSquareLength();
  gluLookAt(squareLength / 2, squareLength / 2, 100, squareLength / 2, squareLength / 2, 0, 0, 1, 0);

  //again select MODEL-VIEW
  glMatrixMode(GL_MODELVIEW);

  /****************************
  / Add your objects from here
  ****************************/
  //add objects
  bubbles.animate();

  //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
  glutSwapBuffers();
}


void animate(){
  angle+=0.15;
  //codes for any changes in Models, Camera
  // updating position
  bubbles.checkBoundaryIntersection();
  bubbles.updateBubblesPosition();
  glutPostRedisplay();
}

void init(){
  //codes for initialization
  drawaxes=1;
  angle=0;

  //clear the screen
  glClearColor(0,0,0,0);

  /************************
  / set-up projection here
  ************************/
  //load the PROJECTION matrix
  glMatrixMode(GL_PROJECTION);

  //initialize the matrix
  glLoadIdentity();

  //give PERSPECTIVE parameters
  gluPerspective(120,	1,	1,	3000.0);
  //field of view in the Y (vertically)
  //aspect ratio that determines the field of view in the X direction (horizontally)
  //near distance
  //far distance
}

int main(int argc, char **argv){
  glutInit(&argc,argv);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

  glutCreateWindow("Tushar's OpenGL Program 2");

  init();

  glEnable(GL_DEPTH_TEST);	//enable Depth Testing

  glutDisplayFunc(display);	//display callback function
  glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

  glutKeyboardFunc(keyboardListener);
  glutSpecialFunc(specialKeyListener);
  glutMouseFunc(mouseListener);

  glutMainLoop();		//The main loop of OpenGL

  return 0;
}