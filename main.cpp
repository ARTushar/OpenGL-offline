#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <GL/glut.h>
#include "CameraHandler.h"
#include "constants.h"
#include "DrawShape.h"
#include "Gun.h"

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;


// variable for controlling camera
CameraHandler ch;

// draw variable
Gun gun;

void drawAxes()
{
  if(drawaxes==1)
  {
    DrawShape::drawAxes(2000);
  }
}

void drawSS()
{
  gun.drawGun();
//  DrawShape::drawSquare(20, {1, 0, 0});
//
//  glRotatef(angle,0,0,1);
//  glTranslatef(110,0,0);
//  glRotatef(2*angle,0,0,1);
//  DrawShape::drawSquare(15, {0, 1, 0});
//
//  glPushMatrix();
//  {
//    glRotatef(angle,0,0,1);
//    glTranslatef(60,0,0);
//    glRotatef(2*angle,0,0,1);
//    DrawShape::drawSquare(10, {0, 0, 1});
//  }
//  glPopMatrix();
//
//
//  glRotatef(3*angle,0,0,1);
//  glTranslatef(40,0,0);
//  glRotatef(4*angle,0,0,1);
//  DrawShape::drawSquare(5, {1, 1, 0});
}

void keyboardListener(unsigned char key, int x,int y){
  switch(key){
    case '1':
      ch.look_left();
      break;
    case '2':
      ch.look_right();
      break;
    case '3':
      ch.look_up();
      break;
    case '4':
      ch.look_down();
      break;
    case '5':
      ch.tilt_c();
      break;
    case '6':
      ch.tilt_cc();
      break;
    case 'q':
      gun.rotateLeft();
      break;
    case 'w':
      gun.rotateRight();
      break;
    case 'e':
      gun.rotateUp();
      break;
    case 'r':
      gun.rotateDown();
      break;
    case 'a':
      gun.rotateCylinderUp();
      break;
    case 's':
      gun.rotateCylinderDown();
      break;
    case 'd':
      gun.tiltCylinderLeft();
      break;
    case 'f':
      gun.tiltCylinderRight();
      break;
    default:
      break;
  }
}


void specialKeyListener(int key, int x,int y){
  switch(key){
    case GLUT_KEY_DOWN:		//down arrow key
      ch.move_backward();
      break;
    case GLUT_KEY_UP:		// up arrow key
      ch.move_forward();
      break;
    case GLUT_KEY_RIGHT:
      ch.move_right();
      break;
    case GLUT_KEY_LEFT:
      ch.move_left();
      break;
    case GLUT_KEY_PAGE_UP:
      ch.move_up();
      break;
    case GLUT_KEY_PAGE_DOWN:
      ch.move_down();
      break;

    case GLUT_KEY_INSERT:
      break;

    case GLUT_KEY_HOME:
      break;
    case GLUT_KEY_END:
      break;

    default:
      break;
  }
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
  switch(button){
    case GLUT_LEFT_BUTTON:
      if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
//        drawaxes=1-drawaxes;
        gun.fireBullet();
      }
      break;

    case GLUT_RIGHT_BUTTON:
      //........
      break;

    case GLUT_MIDDLE_BUTTON:
      //........
      break;

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

//  gluLookAt(0,0,200,	0,0,0,	0,1,0);
//    gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
//    gluLookAt(0,0,200,	0,0,0,	0,1,0);
  gluLookAt(ch.get_posx(), ch.get_posy(), ch.get_posz(),
            ch.get_lookx(), ch.get_looky(), ch.get_lookz(),
            ch.get_upx(), ch.get_upy(), ch.get_upz());

  //again select MODEL-VIEW
  glMatrixMode(GL_MODELVIEW);

  /****************************
  / Add your objects from here
  ****************************/
  //add objects

  drawAxes();
//  DrawShape::drawGrid();

  drawSS();

  //drawCircle(30,24);

  //drawCone(20,50,24);

//  drawSphere(30,24,20);

  //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
  glutSwapBuffers();
}


void animate(){
  angle+=0.15;
  //codes for any changes in Models, Camera
  glutPostRedisplay();
}

void init(){
  //codes for initialization
  drawgrid=0;
  drawaxes=1;
  cameraHeight=150.0;
  cameraAngle=1.0;
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

  glutCreateWindow("My OpenGL Program");

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