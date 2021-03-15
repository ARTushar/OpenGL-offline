//
// Created by tushar on 3/14/21.
//

#include <GL/glut.h>
#include "DrawShape.h"
#include "constants.h"
#include <cmath>

void DrawShape::drawCylinder(double radius, int slices, int stacks, double height, double arcRadius) {
  Point points[350][350];
  int i,j;
  double h, r;
  double totalAngle = 2*pi;
  double offsetAngle = 0;
  //generate circle in yz plane
  for(j=0;j<=slices;j++)
  {
    points[0][j].y=radius*cos(offsetAngle + ((double)j/(double)slices)*totalAngle);
    points[0][j].z=radius*sin(offsetAngle + ((double)j/(double)slices)*totalAngle);
    points[0][j].x=0;
  }
  int done = 0;
  for(i=1; i <= stacks; i++)
  {
    h = i * height / stacks;
    for(int j = 0; j < slices; j++) {
      points[i][j].x = h;
      points[i][j].y = points[i-1][j].y;
      points[i][j].z = points[i-1][j].z;
    }
    done++;
  }

  int newStacks = stacks / 4;

  // cylinderExtensionCircles
  for(i = 0; i <= newStacks;i++)
  {
    r = radius + arcRadius - arcRadius *cos(((double)i/(double)newStacks)*(pi/2));
    h = height + i * arcRadius / newStacks;
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
  for(i=0;i<stacks + newStacks;i++)
  {
    glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
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

void DrawShape::drawBullet(double length) {

}


void DrawShape::drawCircle(double radius, int segments) {
  int i;
  Point points[100];
  glColor3f(0.7,0.7,0.7);
  //generate points
  for(i=0;i<=segments;i++)
  {
    points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
    points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
  }
  //draw segments using generated points
  for(i=0;i<segments;i++)
  {
    glBegin(GL_LINES);
    {
      glVertex3f(points[i].x,points[i].y,0);
      glVertex3f(points[i+1].x,points[i+1].y,0);
    }
    glEnd();
  }
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
    glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
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

void DrawShape::drawGrid() {
  int i;
  glColor3f(0.6, 0.6, 0.6);  //grey
  glBegin(GL_LINES);
  {
    for (i = -8; i <= 8; i++) {

      if (i == 0)
        continue;  //SKIP the MAIN axes

      //lines parallel to Y-axis
      glVertex3f(i * 10, -90, 0);
      glVertex3f(i * 10, 90, 0);

      //lines parallel to X-axis
      glVertex3f(-90, i * 10, 0);
      glVertex3f(90, i * 10, 0);
    }

  }

}

void DrawShape::drawSquare(double length, Point color) {
  glColor3f(color.x, color.y, color.z);
  glBegin(GL_QUADS);{
    glVertex3f( length, length, 2);
    glVertex3f( length, -length, 2);
    glVertex3f(-length, -length, 2);
    glVertex3f(-length, length, 2);
  }glEnd();
}

void DrawShape::drawCone(double radius, double height, int segments) {
  int i;
  double shade;
  Point points[100];
  //generate points
  for(i=0;i<=segments;i++)
  {
    points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
    points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
  }
  //draw triangles using generated points
  for(i=0;i<segments;i++)
  {
    //create shading effect
    if(i<segments/2)shade=2*(double)i/(double)segments;
    else shade=2*(1.0-(double)i/(double)segments);
    glColor3f(shade,shade,shade);

    glBegin(GL_TRIANGLES);
    {
      glVertex3f(0,0,height);
      glVertex3f(points[i].x,points[i].y,0);
      glVertex3f(points[i+1].x,points[i+1].y,0);
    }
    glEnd();
  }
}

void DrawShape::drawQuarterCircleXY(double radius, double len, int segments, Point color) {
  int i;
  Point points[200];
  //generate points
  for(i=0;i<=segments;i++)
  {
    points[i].x=radius*cos(((double)i/(double)segments)*pi/2);
    points[i].y=radius*sin(((double)i/(double)segments)*pi/2);
  }
  //draw segments using generated points
  for(i=0;i<segments;i++)
  {
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_QUADS);
    {
      glVertex3f(points[i].x, points[i].y, len);
      glVertex3f(points[i+1].x, points[i+1].y, len);
      glVertex3f(points[i+1].x, points[i+1].y, -len);
      glVertex3f(points[i].x, points[i].y, -len);
    }
    glEnd();
  }

}
