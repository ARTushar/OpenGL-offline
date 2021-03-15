//
// Created by tushar on 3/14/21.
//

#include "Gun.h"
#include <GL/glut.h>
#include "DrawShape.h"

void Gun::drawGun() {
//  DrawShape::drawSphere(sphereRadius, 100, 100, 0);
  glPushMatrix();
  {
    glRotatef(totalStepsLeft * stepAngle, 0, 0, 1);
    DrawShape::drawSphere(sphereRadius, 100, 30, 1);
    glRotatef(totalStepsUp * stepAngle, 0, 1, 0);
    DrawShape::drawSphere(sphereRadius, 100, 30, 2);
    glTranslatef(cylinderCapDistance, 0, 0);
    DrawShape::drawSphere(cylinderCapRadius, 50, 30, 1);
    DrawShape::drawCylinder(cylinderCapRadius, 50, 200, cylinderHeight, quarterRadius);
    glTranslatef(cylinderHeight + quarterRadius + planeDistance, 0, 0);
  }
  glPopMatrix();
  DrawShape::drawPlane({planeDistanceFromOrigin, 0, 0}, 500, 500);
}

Gun::Gun() {
  sphereRadius = 100;
  cylinderCapRadius = 50;
  cylinderCapDistance = sphereRadius + cylinderCapRadius;
  cylinderHeight = 500;
  quarterRadius = 50;
  planeDistance = 400;
  planeDistanceFromOrigin = sphereRadius + cylinderCapRadius + cylinderHeight + quarterRadius + planeDistance;
  maxRotateAngle = 45;
  totalStepsLeft = 0;
  totalStepsUp = 0;
  stepAngle = 3;
}

void Gun::rotateLeft() {
  if(abs(totalStepsLeft+1) * stepAngle > maxRotateAngle) return;
  totalStepsLeft++;
}

void Gun::rotateRight() {
  if(abs(totalStepsLeft-1) * stepAngle > maxRotateAngle) return;
  printf("%d\n", totalStepsLeft);
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

