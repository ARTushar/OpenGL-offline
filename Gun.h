//
// Created by tushar on 3/14/21.
//

#ifndef INC_1605070_GUN_H
#define INC_1605070_GUN_H


#include "Point.h"
#include <vector>

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


#endif //INC_1605070_GUN_H
