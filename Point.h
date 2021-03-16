//
// Created by tushar on 3/14/21.
//

#ifndef INC_1605070_POINT_H
#define INC_1605070_POINT_H


#include <cmath>

class Point{
public:
    double x, y, z;
    Point(){}
    Point(double x, double y, double z) : x(x), y(y), z(z){}
    double dot(const Point & rhs) {
      return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    double distance(const Point & rhs) {
      return sqrt(pow(x-rhs.x, 2) + pow(y-rhs.y, 2) + pow(z-rhs.z, 2));
    }
    Point operator * (double a) {
      return {x*a, y*a, z*a};
    }
    Point operator + (Point a) {
      return {x + a.x, y + a.y, z + a.z};
    }
    Point operator - (Point a) {
      return {x - a.x, y - a.y, z - a.z};
    }

    bool operator<(const Point &rhs) const {
      if (x < rhs.x)
        return true;
      if (rhs.x < x)
        return false;
      if (y < rhs.y)
        return true;
      if (rhs.y < y)
        return false;
      return z < rhs.z;
    }

    bool operator>(const Point &rhs) const {
      return rhs < *this;
    }

    bool operator<=(const Point &rhs) const {
      return !(rhs < *this);
    }

    bool operator>=(const Point &rhs) const {
      return !(*this < rhs);
    }

    bool operator==(const Point &rhs) const {
      return x == rhs.x &&
             y == rhs.y &&
             z == rhs.z;
    }

    bool operator!=(const Point &rhs) const {
      return !(rhs == *this);
    }
};


#endif //INC_1605070_POINT_H
