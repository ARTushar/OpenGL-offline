//
// Created by tushar on 3/14/21.
//

#include "Gun.h"
#include <GL/glut.h>
#include "DrawShape.h"
#include <cmath>
#include <algorithm>
#include "constants.h"

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


