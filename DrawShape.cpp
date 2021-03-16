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
