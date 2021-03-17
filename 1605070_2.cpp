//
// Created by tushar on 3/16/21.
//

#include<stdio.h>
#include<stdlib.h>
#include <algorithm>
#include<math.h>
#include <vector>
#include <GL/glut.h>
#include <chrono>

#define pi (2*acos(0.0))

class Timer
{
    int timeLimit = 2000;
    std::chrono::time_point<std::chrono::system_clock> startTime, currentTime;

public:
    Timer() = default;

    explicit Timer(const int &timeLimit)
    {
      this->timeLimit = timeLimit;
    }

    void startTimer()
    {
      startTime = std::chrono::high_resolution_clock::now();
    }

    int elapsedMillis()
    {
      currentTime = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    }

    bool timesUp(int time) {
      return elapsedMillis() > time;
    }

    bool timesUp()
    {
      return elapsedMillis() > timeLimit;
    }
};

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
    static void drawSquareXY(Point position, double length, Point color);
    static void drawCircleXY(Point position, double radius, Point color);
};


void DrawShape::drawSquareXY(Point position, double length, Point color) {
  glColor3f(color.x, color.y, color.z);
  glBegin(GL_LINES);{
    glVertex3f(position.x + length / 2, position.y + length / 2, position.z);
    glVertex3f(position.x + length / 2, position.y - length / 2, position.z);

    glVertex3f(position.x - length / 2, position.y - length / 2, position.z);
    glVertex3f(position.x - length / 2, position.y + length / 2, position.z);

    glVertex3f(position.x + length / 2, position.y - length / 2, position.z);
    glVertex3f(position.x - length / 2, position.y - length / 2, position.z);

    glVertex3f(position.x + length / 2, position.y + length / 2, position.z);
    glVertex3f(position.x - length / 2, position.y + length / 2, position.z);
  }glEnd();
}

void DrawShape::drawCircleXY(Point position, double radius, Point color) {
  int i;
  int segments = 50;
  Point points[100];
  glColor3f(color.x, color.y, color.z);
  //generate points
  for(i=0;i<=segments; i++)
  {
    points[i].x = position.x + radius * cos(((double)i/(double)segments)*2*pi);
    points[i].y = position.y + radius * sin(((double)i/(double)segments)*2*pi);
  }
  //draw segments using generated points
  for(i=0;i<segments;i++)
  {
    glBegin(GL_LINES);
    {
      glVertex3f(points[i].x,points[i].y, position.z);
      glVertex3f(points[i+1].x,points[i+1].y, position.z);
    }
    glEnd();
  }
}


class Bubble {
public:
    Point position;
    Point velocity;
    bool startMoving = false;
    bool insideCircle = false;
    std::vector<int> overlappedCirlces;
    Bubble();
    Bubble(Point pos, Point vel);
    void updateVelocity(Point vel);
    void updatePosition(double speed);
    void draw(double radius);
    static Point convert_to_unit(Point &a);
    void reflectDirection(Point n);
};


class Bubbles {
private:
    const int numberOfBubbles = 5;
    std::vector<Bubble> bubbles;
    double speed;
    double maxSpeed, minSpeed;
    double step;
    bool bubblesMoving;
    double bigCircleRadius;
    double bubbleRadius;
    double squareLength;
    void assignInitialBubbles();
    void drawBubbles();
    static Point generateRandomDirection();
    Timer timer;


public:
    Bubbles();
    void animate();
    void increaseSpeed();
    void decreaseSpeed();
    void toggleAnimation();
    void checkBoundaryIntersection();
    void checkInsideCicle();
    void updateBubblesPosition();
    double getSquareLength();

    bool checkInsideCircle(Point pos);

    bool checkOutsideCircle(Point pos);

    Point getCircleNormalVector(Point pos);

    bool checkBubbleBubbleIntersection(int i, int j);

    Point getBubbleBubbleNormalVector(int i, int j);

    bool checkOverlapped(int i);

    void checkNotOverlapped(int i);
};

Bubbles::Bubbles() {
  bubbleRadius = 10;
  bigCircleRadius = 60;
  squareLength = 200;
  assignInitialBubbles();
  speed = 0.1;
  minSpeed = 0.1;
  maxSpeed = 2.5;
  step = 0.1;
  bubblesMoving = true;
  srand(time(nullptr));
  timer.startTimer();
}

void Bubbles::animate() {
  DrawShape::drawSquareXY({squareLength/2, squareLength/2, 0}, squareLength, {0, 1, 0});
  DrawShape::drawCircleXY({squareLength/2, squareLength/2, 0}, bigCircleRadius, {1, 0, 0});
  drawBubbles();
}

void Bubbles::drawBubbles() {
  for(auto & bubble : bubbles){
    if(bubble.startMoving){
      bubble.draw(bubbleRadius);
    }
  }
}

void Bubbles::assignInitialBubbles() {
  for(int i = 0; i < numberOfBubbles; i++) {
    bubbles.push_back(Bubble({bubbleRadius, bubbleRadius, 0}, generateRandomDirection()));
  }
}

Point Bubbles::generateRandomDirection() {
  double x = rand();
  double y = rand();
  double val = sqrt(x * x + y * y);
  x = x / val;
  y = y / val;
  return {x, y, 0};
}

void Bubbles::increaseSpeed() {
  if(speed + step > maxSpeed) return;
  speed += step;
}

void Bubbles::decreaseSpeed() {
  if(speed - step < minSpeed) return;
  speed -= step;
}

void Bubbles::toggleAnimation() {
  bubblesMoving = !bubblesMoving;
}

double Bubbles::getSquareLength() {
  return squareLength;
}

void Bubbles::updateBubblesPosition() {
  if(bubblesMoving){
    for(auto & bubble : bubbles){
      if(!bubble.startMoving) {
        if(timer.timesUp()){
          bubble.startMoving = true;
          timer.startTimer();
        }
      } else {
        bubble.updatePosition(speed);
      }
    }
  }
}

void Bubbles::checkBoundaryIntersection() {
  for(int i = 0; i < numberOfBubbles; i++) {
    if(!bubbles[i].insideCircle){
      if(bubbles[i].position.x + bubbleRadius > squareLength){
        bubbles[i].reflectDirection({-1, 0, 0});
      }
      if(bubbles[i].position.x - bubbleRadius < 0){
        bubbles[i].reflectDirection({1, 0, 0});
      }
      if(bubbles[i].position.y + bubbleRadius > squareLength){
        bubbles[i].reflectDirection({0, -1, 0});
      }
      if(bubbles[i].position.y - bubbleRadius < 0){
        bubbles[i].reflectDirection({0, 1, 0});
      }
      if(checkInsideCircle(bubbles[i].position)) {
        bubbles[i].insideCircle = true;
        printf("yo inside the circle!\n");
        if(checkOverlapped(i)) {
        }
      }
    } else {
      for(int j = 0; j < numberOfBubbles; j++) {
        if(j == i ||
           std::find(bubbles[i].overlappedCirlces.begin(), bubbles[i].overlappedCirlces.end(), j) != bubbles[i].overlappedCirlces.end()) {
          continue;
        }
        if(checkBubbleBubbleIntersection(i, j)){
          Point normal = getBubbleBubbleNormalVector(i, j);
          bubbles[i].reflectDirection(normal);
        }
      }

      if(checkOutsideCircle(bubbles[i].position)){
        Point normal = getCircleNormalVector(bubbles[i].position);
        bubbles[i].reflectDirection(normal);
      }

      checkNotOverlapped(i);
    }
  }
}


Point Bubble::convert_to_unit(Point &a) {
  double val = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
  return  {a.x / val, a.y / val, a.z / val};
}

Bubble::Bubble(Point pos, Point vel) : position(pos), velocity(vel){}

void Bubble::updateVelocity(const Point vel) {
  velocity = vel;
}

void Bubble::updatePosition(double speed) {
  position = position + velocity * speed;
}

Bubble::Bubble() : position({0, 0, 0}), velocity({0, 0, 0}){}

void Bubble::draw(double radius) {
  DrawShape::drawCircleXY(position, radius, {1, 1, 0 });
}

void Bubble::reflectDirection(Point n) {
  double dn = velocity.dot(n);
  Point reflectVector = velocity - n * 2 * dn;
  reflectVector = convert_to_unit(reflectVector);
  updateVelocity(reflectVector);
}


bool Bubbles::checkInsideCircle(Point pos) {
  return pos.distance({squareLength/2, squareLength/2, 0}) <= bigCircleRadius - bubbleRadius;
}

bool Bubbles::checkOutsideCircle(Point pos) {
  return pos.distance({squareLength/2, squareLength/2, 0}) + bubbleRadius > bigCircleRadius;
}

bool Bubbles::checkBubbleBubbleIntersection(int i, int j) {
  return bubbles[i].position.distance(bubbles[j].position) <= 2 * bubbleRadius;
}

Point Bubbles::getCircleNormalVector(Point pos) {
  Point normal = {squareLength / 2, squareLength / 2, 0};
  normal = normal - pos;
  normal = Bubble::convert_to_unit(normal);
  return normal;
}

Point Bubbles::getBubbleBubbleNormalVector(int i, int j) {
  Point normal = bubbles[i].position - bubbles[j].position;
  normal = Bubble::convert_to_unit(normal);
  return normal;
}

bool Bubbles::checkOverlapped(int i) {
  bool overlapped = false;
  for(int j = 0; j < numberOfBubbles; j++) {
    if (i == j) continue;
    if(checkBubbleBubbleIntersection(i, j)){
      printf("overlapped! %d %d\n", i, j);
      bubbles[i].overlappedCirlces.push_back(j);
      overlapped = true;
    }
  }
  return overlapped;
}

void Bubbles::checkNotOverlapped(int i) {
  bubbles[i].overlappedCirlces;
  for(int j = 0; j < bubbles[i].overlappedCirlces.size(); j++) {
    if(!checkBubbleBubbleIntersection(i, bubbles[i].overlappedCirlces[j])){
      printf("not overlapped! %d %d\n", i, bubbles[i].overlappedCirlces[j]);
      bubbles[i].overlappedCirlces.erase(bubbles[i].overlappedCirlces.begin() + j);
    }
  }
}


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