#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <vector>
#include <algorithm>
#include <GL/glut.h>

#define pi (2*acos(0.0))

class Point{
public:
    double x, y, z;
    Point(){}
    Point(double x, double y, double z) : x(x), y(y), z(z){}
    double dot(const Point & rhs) {
      return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    double distance(const Point & rhs) {
      return sqrt(pow(x-rhs.x, 2) + pow(y-rhs.y, 2) + pow(z-rhs.z, 2));
    }
    Point operator * (double a) {
      return {x*a, y*a, z*a};
    }
    Point operator + (Point a) {
      return {x + a.x, y + a.y, z + a.z};
    }
    Point operator - (Point a) {
      return {x - a.x, y - a.y, z - a.z};
    }

    bool operator<(const Point &rhs) const {
      if (x < rhs.x)
        return true;
      if (rhs.x < x)
        return false;
      if (y < rhs.y)
        return true;
      if (rhs.y < y)
        return false;
      return z < rhs.z;
    }

    bool operator>(const Point &rhs) const {
      return rhs < *this;
    }

    bool operator<=(const Point &rhs) const {
      return !(rhs < *this);
    }

    bool operator>=(const Point &rhs) const {
      return !(*this < rhs);
    }

    bool operator==(const Point &rhs) const {
      return x == rhs.x &&
             y == rhs.y &&
             z == rhs.z;
    }

    bool operator!=(const Point &rhs) const {
      return !(rhs == *this);
    }
};


class DrawShape {
public:
    static void drawCylinder(double radius, int slices, int stacks, double height, double arcRadius);
    static void drawSphere(double radius, int slices, int stacks, int dir);
    static void drawAxes(double length);
    static void drawPlane(Point center, double width, double height);
    static void drawSquare(Point position, double length, Point color);
};

void DrawShape::drawCylinder(double radius, int slices, int stacks, double height, double arcRadius) {
  Point points[350][350];
  int i,j;
  double h, r;
  double totalAngle = 2*pi;
  double offsetAngle = 0;

  int done = 0;

//   generate cylinder left cap
  int totalStacksLeft = stacks / 4;
  for(i=0; i <= totalStacksLeft; i++)
  {
    h = radius - radius*cos(((double)i/(double)totalStacksLeft)*(pi/2));
    r= radius*sin(((double)i/(double)totalStacksLeft)*(pi/2));
    for(j=0;j<=slices;j++)
    {
      points[done][j].y=r*cos(((double)j/(double)slices)*totalAngle);
      points[done][j].z=r*sin(((double)j/(double)slices)*totalAngle);
      points[done][j].x=h;
    }
    done++;
  }

  for(i=1; i <= stacks; i++)
  {
    h = radius + i * height / stacks;
    for(int j = 0; j <= slices; j++) {
      points[done][j].x = h;
      points[done][j].y = points[done-1][j].y;
      points[done][j].z = points[done-1][j].z;
    }
    done++;
  }

  int newStacks = stacks / 4;

//   cylinderExtensionCircles
  for(i = 1; i <= newStacks;i++)
  {
    r = radius + arcRadius - arcRadius * cos(((double)i/(double)newStacks)*(pi/2));
    h = radius + height + arcRadius * sin(((double)i/(double)newStacks)*(pi/2));
    for(j=0;j<=slices;j++)
    {
      points[done][j].y=r * cos(((double)j/(double)slices)*totalAngle);
      points[done][j].z=r*sin(((double)j/(double)slices)*totalAngle);
      points[done][j].x=h;
    }
    done++;
  }

  //draw quads using generated points
  int toggle = 0;
  for(i=0;i<done-1;i++)
  {
//    glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
    for(j=0;j<slices;j++)
    {
      glColor3f(1-toggle, 1-toggle, 1-toggle);
      toggle = !toggle;
      glBegin(GL_QUADS);{
        glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
        glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
        glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
        glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
      }glEnd();
    }
  }

}
void DrawShape::drawPlane(Point center, double width, double height) {
  glColor3f(1, 1, 1);
  glBegin(GL_QUADS); {
    glVertex3f(center.x, center.y + width/2, center.z + height/2);
    glVertex3f(center.x, center.y - width/2, center.z + height/2);
    glVertex3f(center.x, center.y - width/2, center.z - height/2);
    glVertex3f(center.x, center.y + width/2, center.z - height/2);
  }glEnd();

}

void DrawShape::drawSphere(double radius, int slices, int stacks, int dir) {
  Point points[200][200];
  int i,j;
  double h,r;
  double totalAngle = 2*pi;
  for(i=0; i <= stacks;i++)
  {
    h=radius*sin(((double)i/(double)stacks)*(pi/2));
    r=radius*cos(((double)i/(double)stacks)*(pi/2));
    for(j=0;j<=slices;j++)
    {
      points[i][j].y=r*cos(((double)j/(double)slices)*totalAngle);
      points[i][j].z=r*sin(((double)j/(double)slices)*totalAngle);
      points[i][j].x=h;
    }
  }
  //draw quads using generated points
  int toggle = 0;
  for(i=0;i<stacks;i++)
  {
//    glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
    for(j=0;j<slices;j++)
    {
      glColor3f(1-toggle, 1-toggle, 1-toggle);
      toggle = !toggle;
      glBegin(GL_QUADS);{
        //right hemisphere
        if(dir != 1){
          glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
          glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
          glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
          glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

        }
        //left hemisphere
        if(dir != 2) {
          glVertex3f(-points[i][j].x,points[i][j].y, points[i][j].z);
          glVertex3f(-points[i][j+1].x,points[i][j+1].y, points[i][j+1].z);
          glVertex3f(-points[i+1][j+1].x,points[i+1][j+1].y, points[i+1][j+1].z);
          glVertex3f(-points[i+1][j].x,points[i+1][j].y, points[i+1][j].z);
        }
      }glEnd();
    }
  }
}


void DrawShape::drawAxes(double length) {
  glColor3f(1, 1, 1);
  glBegin(GL_LINES);{
    glVertex3f( length,0,0);
    glVertex3f(-length,0,0);

    glVertex3f(0,-length,0);
    glVertex3f(0, length,0);

    glVertex3f(0,0, length);
    glVertex3f(0,0,-length);
  }glEnd();
}


void DrawShape::drawSquare(Point position, double length, Point color) {
  glColor3f(color.x, color.y, color.z);
  glBegin(GL_QUADS);{
    glVertex3f( position.x-2, position.y + length / 2, position.z + length / 2);
    glVertex3f( position.x-2, position.y + length / 2, position.z - length / 2);
    glVertex3f( position.x-2, position.y - length / 2, position.z - length / 2);
    glVertex3f( position.x-2, position.y - length / 2, position.z + length / 2);
  }glEnd();
}


class CameraHandler {
private:
    double step;
    double angle;
    Point position;
    Point look, up, right;
    static Point convert_to_unit(Point& a);

public:

    CameraHandler();
    CameraHandler(Point pos, Point l, Point u, Point r, double step, double angle);

    void move_forward();
    void move_backward();
    void move_right();
    void move_left();
    void move_up();
    void move_down();

    void look_left();
    void look_right();
    void look_up();
    void look_down();
    void tilt_c();
    void tilt_cc();

    double get_posx();
    double get_posy();
    double get_posz();
    double get_lookx();
    double get_looky();
    double get_lookz();
    double get_upx();
    double get_upy();
    double get_upz();


};

CameraHandler::CameraHandler() {
  position = {0, -200, 0};
  up = {0, 0, 1};
  double val = 1/sqrt(2);
  right = {1, 0, 0};
  look = {0, 1, 0};
  step = 2;
  angle = 3;
}

CameraHandler::CameraHandler(Point pos, Point l, Point u, Point r, double step, double angle):
        position(pos), look(l), up(u), right(r), step(step), angle(angle)
{
}

void CameraHandler::move_forward() {
  position = position + look * step;
}

void CameraHandler::move_backward() {
  position = position - look * step;
}

void CameraHandler::move_right() {
  position = position +  right * step;
}

void CameraHandler::move_left() {
  position = position -  right * step;
}

void CameraHandler::move_up() {
  position = position + up * step;
}

void CameraHandler::move_down() {
  position = position - up * step;
}

void CameraHandler::look_left() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) + look * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  look = look * cos(angle * pi / 180) - right * sin(angle * pi / 180);
  look = convert_to_unit(look);

  right = new_right;
}

void CameraHandler::look_right() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) - look * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  look = look * cos(angle * pi / 180) + right * sin(angle * pi / 180);
  look = convert_to_unit(look);

  right = new_right;

}

void CameraHandler::look_up() {
  Point new_look;
  new_look = look * cos(angle * pi / 180) + up * sin(angle * pi / 180);
  new_look = convert_to_unit(new_look);

  up = up * cos(angle * pi / 180) - look * sin(angle * pi / 180);
  up = convert_to_unit(up);

  look = new_look;
}

void CameraHandler::look_down() {
  Point new_look;
  new_look = look * cos(angle * pi / 180) - up * sin(angle * pi / 180);
  new_look = convert_to_unit(new_look);

  up = up * cos(angle * pi / 180) + look * sin(angle * pi / 180);
  up = convert_to_unit(up);

  look = new_look;

}

void CameraHandler::tilt_c() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) - up * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  up = up * cos(angle * pi / 180) + right * sin(angle * pi / 180);
  up = convert_to_unit(up);

  right = new_right;
}

void CameraHandler::tilt_cc() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) + up * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  up = up * cos(angle * pi / 180) - right * sin(angle * pi / 180);
  up = convert_to_unit(up);

  right = new_right;

}

double CameraHandler::get_posx() {
  return position.x;
}

double CameraHandler::get_posy() {
  return position.y;
}

double CameraHandler::get_posz() {
  return position.z;
}

double CameraHandler::get_lookx() {
  return position.x + look.x;
}

double CameraHandler::get_looky() {
  return position.y + look.y;
}

double CameraHandler::get_lookz() {
  return position.z + look.z;
}

double CameraHandler::get_upx() {
  return up.x;
}

double CameraHandler::get_upy() {
  return up.y;
}

double CameraHandler::get_upz() {
  return up.z;
}

Point CameraHandler::convert_to_unit(Point& a) {
  double val = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
  return  {a.x / val, a.y / val, a.z / val};
}

class Gun {
private:
    double sphereRadius;
    double cylinderCapRadius;
    double cylinderCapDistance;
    double cylinderHeight;
    double quarterRadius ;
    double planeDistance;
    double planeWidth, planeHeight;
    double planeDistanceFromOrigin;
    double maxRotateAngle;
    double bulletLength;
    double stepAngle;
    int totalStepsLeft, totalStepsUp, totalStepsCylinderUp, totalStepsCylinderLeft;
    Point bulletCurrentPosition;
    std::vector<Point> bullets;

    void drawAllBullets();
public:
    Gun();
    void drawGun();
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
    void rotateCylinderUp();
    void rotateCylinderDown();
    void tiltCylinderLeft();
    void tiltCylinderRight();
    void fireBullet();
};

void Gun::drawGun() {
//  DrawShape::drawSphere(sphereRadius, 100, 100, 0);
  glPushMatrix();
  {
    glRotatef(totalStepsLeft * stepAngle, 0, 0, 1);
    DrawShape::drawSphere(sphereRadius, 100, 30, 1);
    glRotatef(totalStepsUp * stepAngle, 0, 1, 0);
    DrawShape::drawSphere(sphereRadius, 100, 30, 2);
    glTranslatef(sphereRadius, 0, 0);
    glRotatef(totalStepsCylinderUp * stepAngle, 0, 1, 0);
    glPushMatrix();{
      glRotatef(totalStepsCylinderLeft * stepAngle, 1, 0, 0);
      DrawShape::drawCylinder(cylinderCapRadius, 50, 200, cylinderHeight, quarterRadius);
    }
    glPopMatrix();
  }
  glPopMatrix();
  DrawShape::drawPlane({planeDistanceFromOrigin, 0, 0}, planeWidth, planeHeight);
  drawAllBullets();
}

Gun::Gun() {
  sphereRadius = 100;
  cylinderCapRadius = 50;
  cylinderCapDistance = sphereRadius + cylinderCapRadius;
  cylinderHeight = 400;
  quarterRadius = 50;
  planeDistance = 400;
  planeWidth = 500;
  planeHeight = 500;
  planeDistanceFromOrigin = sphereRadius + cylinderCapRadius + cylinderHeight + quarterRadius + planeDistance;
  maxRotateAngle = 45;
  totalStepsLeft = 0;
  totalStepsUp = 0;
  totalStepsCylinderUp = 0;
  totalStepsCylinderLeft = 0;
  bulletLength = 20;
  stepAngle = 3;
  bulletCurrentPosition = {planeDistanceFromOrigin, 0, 0};
}

void Gun::rotateLeft() {
  if(abs(totalStepsLeft+1) * stepAngle > maxRotateAngle) return;
  totalStepsLeft++;
}

void Gun::rotateRight() {
  if(abs(totalStepsLeft-1) * stepAngle > maxRotateAngle) return;
  totalStepsLeft--;

}

void Gun::rotateUp() {
  if(abs(totalStepsUp - 1) * stepAngle > maxRotateAngle) return;
  totalStepsUp--;
}

void Gun::rotateDown() {
  if(abs(totalStepsUp + 1) * stepAngle > maxRotateAngle) return;
  totalStepsUp++;
}

void Gun::rotateCylinderUp() {
  if(abs(totalStepsCylinderUp - 1) * stepAngle > maxRotateAngle) return;
  totalStepsCylinderUp--;
}

void Gun::rotateCylinderDown() {
  if(abs(totalStepsCylinderUp + 1) * stepAngle > maxRotateAngle) return;
  totalStepsCylinderUp++;
}

void Gun::tiltCylinderLeft() {
  if(abs(totalStepsCylinderLeft + 1) * stepAngle > maxRotateAngle) return;
  totalStepsCylinderLeft++;

}

void Gun::tiltCylinderRight() {
  if(abs(totalStepsCylinderLeft - 1) * stepAngle > maxRotateAngle) return;
  totalStepsCylinderLeft--;
}

void Gun::fireBullet() {
  double currentUpAngle = totalStepsUp * stepAngle * pi / 180;
  double currentLeftAngle = totalStepsLeft * stepAngle * pi / 180;
  double currentCylinderUpAngle = totalStepsCylinderUp * stepAngle * pi / 180;

  double y, z;
  y = planeDistanceFromOrigin * tan(currentLeftAngle);
  z = -(sphereRadius * sin(currentUpAngle) +
        (planeDistanceFromOrigin - sphereRadius * cos(currentUpAngle))
        * tan(currentUpAngle + currentCylinderUpAngle));
  printf("%f %f %f\n", planeDistanceFromOrigin, y, z);
  Point found = {planeDistanceFromOrigin, y, z};
  if (std::find(bullets.begin(), bullets.end(), found) != bullets.end()) {
    printf("already fired!\n");
    return;
  } else {
    if (abs(y) > planeWidth / 2 || abs(z) > planeHeight / 2){
      printf("out of plane!\n");
      return;
    }
  }
  printf("gotcha!\n");
  bullets.push_back(found);
}

void Gun::drawAllBullets() {
  for(auto pos: bullets) {
    DrawShape::drawSquare(pos, bulletLength, {1, 0, 0});
  }
}




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
        gun.fireBullet();
      }
      break;

    case GLUT_RIGHT_BUTTON:
      if(state == GLUT_DOWN) {
        drawaxes=1-drawaxes;
      }
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

  drawSS();

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

  glutCreateWindow("Tushar's OpenGL Program");

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