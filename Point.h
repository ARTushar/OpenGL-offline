//
// Created by tushar on 3/14/21.
//

#ifndef INC_1605070_POINT_H
#define INC_1605070_POINT_H


class Point{
public:
    double x, y, z;
    Point(){}
    Point(double x, double y, double z) : x(x), y(y), z(z){}
    Point operator * (double a) {
      return {x*a, y*a, z*a};
    }
    Point operator + (Point a) {
      return {x + a.x, y + a.y, z + a.z};
    }
    Point operator - (Point a) {
      return {x - a.x, y - a.y, z - a.z};
    }
};


#endif //INC_1605070_POINT_H
