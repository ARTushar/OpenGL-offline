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
    static void drawCircle(double radius, int segments);
    static void drawSphere(double radius, int slices, int stacks, int dir);
    static void drawBullet(double length);
    static void drawAxes(double length);
    static void drawGrid();
    static void drawSquare(double length, Point color);
    static void drawCone(double radius, double height, int segments);
    static void drawQuarterCircleXY(double radius, double len, int segments, Point color);
    static void drawPlane(Point center, double width, double height);
};


#endif //INC_1605070_DRAWSHAPE_H
