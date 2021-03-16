//
// Created by tushar on 3/16/21.
//

#ifndef INC_1605070_BUBBLES_H
#define INC_1605070_BUBBLES_H

#include <vector>
#include "Point.h"
#include "Timer.h"

class Bubble {
public:
    Point position;
    Point velocity;
    bool startMoving;
    bool insideCircle;
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
};


#endif //INC_1605070_BUBBLES_H
