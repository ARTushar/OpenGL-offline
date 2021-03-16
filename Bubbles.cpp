//
// Created by tushar on 3/16/21.
//

#include <cmath>
#include "Bubbles.h"
#include "DrawShape.h"

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
  for(auto & bubble : bubbles) {
    if(!bubble.insideCircle){
      if(bubble.position.x + bubbleRadius > squareLength){
        bubble.reflectDirection({-1, 0, 0});
      }
      if(bubble.position.x - bubbleRadius < 0){
        bubble.reflectDirection({1, 0, 0});
      }
      if(bubble.position.y + bubbleRadius > squareLength){
        bubble.reflectDirection({0, -1, 0});
      }
      if(bubble.position.y - bubbleRadius < 0){
        bubble.reflectDirection({0, 1, 0});
      }
      if(checkInsideCircle(bubble.position)) {
        bubble.insideCircle = true;
        printf("yo inside the circle!\n");
      }
    } else if(checkOutsideCircle(bubble.position)){
      Point normal = getCircleNormalVector(bubble.position);
      bubble.reflectDirection(normal);
    }
  }
}


Point Bubble::convert_to_unit(Point &a) {
  double val = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
  return  {a.x / val, a.y / val, a.z / val};
}

Bubble::Bubble(Point pos, Point vel) : position(pos), velocity(vel), startMoving(false), insideCircle(false){}

void Bubble::updateVelocity(const Point vel) {
  velocity = vel;
}

void Bubble::updatePosition(double speed) {
  position = position + velocity * speed;
}

Bubble::Bubble() : position({0, 0, 0}), velocity({0, 0, 0}), startMoving(false), insideCircle(false){}

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

Point Bubbles::getCircleNormalVector(Point pos) {
  Point normal = {squareLength / 2, squareLength / 2, 0};
  normal = normal - pos;
  normal = Bubble::convert_to_unit(normal);
  return normal;
}
