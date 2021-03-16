//
// Created by tushar on 3/14/21.
//
#include <string>
#include "Point.h"
#ifndef INC_1605070_DRAWSHAPE_H
#define INC_1605070_DRAWSHAPE_H


class DrawShape {
public:
    static void drawCylinder(double radius, int slices, int stacks, double height, double arcRadius);
    static void drawSphere(double radius, int slices, int stacks, int dir);
    static void drawAxes(double length);
    static void drawPlane(Point center, double width, double height);
    static void drawSquare(Point position, double length, Point color);
};


#endif //INC_1605070_DRAWSHAPE_H
