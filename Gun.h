//
// Created by tushar on 3/14/21.
//

#ifndef INC_1605070_GUN_H
#define INC_1605070_GUN_H


class Gun {
private:
    double sphereRadius;
    double cylinderCapRadius;
    double cylinderCapDistance;
    double cylinderHeight;
    double quarterRadius ;
    double planeDistance;
    double planeDistanceFromOrigin;
    double maxRotateAngle;
    double gunLength;
    double stepAngle;
    int totalStepsLeft, totalStepsUp;
public:
    Gun();
    void drawGun();
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
};


#endif //INC_1605070_GUN_H
