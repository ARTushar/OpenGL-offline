//
// Created by tushar on 3/16/21.
//

#include <cmath>
#include <algorithm>
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
