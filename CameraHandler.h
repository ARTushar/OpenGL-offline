//
// Created by tushar on 3/12/21.
//

#ifndef INC_1605070_CAMERAHANDLER_H
#define INC_1605070_CAMERAHANDLER_H

struct point {
    double x, y, z;
};

class CameraHandler {
private:
    double step;

public:
    point position;
    point look, up, right;

    CameraHandler();
    CameraHandler(point pos, point l, point u, point r, double step);

    void move_forward();
    void move_backward();
    void move_right();
    void move_left();
    void move_up();
    void move_down();

    void rotate_left();
    void rotate_right();
    void rotate_up();
    void rotate_down();
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
