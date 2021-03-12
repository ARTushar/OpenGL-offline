//
// Created by tushar on 3/12/21.
//
#include <string>

#ifndef INC_1605070_CAMERAHANDLER_H
#define INC_1605070_CAMERAHANDLER_H
#define pi (2*acos(0.0))


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

class CameraHandler {
private:
    double step;
    double angle;
    Point position;
    Point look, up, right;
    static Point convert_to_unit(Point& a);

public:

    CameraHandler();
    CameraHandler(Point pos, Point l, Point u, Point r, double step, double angle);

    void move_forward();
    void move_backward();
    void move_right();
    void move_left();
    void move_up();
    void move_down();

    void look_left();
    void look_right();
    void look_up();
    void look_down();
    void tilt_c();
    void tilt_cc();

    double get_posx();
    double get_posy();
    double get_posz();
    double get_lookx();
    double get_looky();
    double get_lookz();
    double get_upx();
    double get_upy();
    double get_upz();


};


#endif //INC_1605070_CAMERAHANDLER_H
