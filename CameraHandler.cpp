//
// Created by tushar on 3/12/21.
//

#include <cmath>
#include "CameraHandler.h"

CameraHandler::CameraHandler() {
  position = {100, 100, 0};
  up = {0, 0, 1};
  double val = 1/sqrt(2);
  right = {-val, val, 0};
  look = {-val, -val, 0};
  step = 3;
}

CameraHandler::CameraHandler(point pos, point l, point u, point r, double step):
        position(pos), look(l), up(u), right(r), step(step)
{
}

void CameraHandler::move_forward() {
  position.x += step;
}

void CameraHandler::move_backward() {
  position.x -= step;
}

void CameraHandler::move_right() {
  position.y += step;
}

void CameraHandler::move_left() {
  position.y -= step;
}

void CameraHandler::move_up() {
  position.z += step;
}

void CameraHandler::move_down() {
  position.z -= step;
}

void CameraHandler::rotate_left() {

}

void CameraHandler::rotate_right() {

}

void CameraHandler::rotate_up() {

}

void CameraHandler::rotate_down() {

}

void CameraHandler::tilt_c() {

}

void CameraHandler::tilt_cc() {

}

double CameraHandler::get_posx() {
  return position.x;
}

double CameraHandler::get_posy() {
  return position.y;
}

double CameraHandler::get_posz() {
  return position.z;
}

double CameraHandler::get_lookx() {
  return position.x + look.x;
}

double CameraHandler::get_looky() {
  return position.y + look.y;
}

double CameraHandler::get_lookz() {
  return position.z + look.z;
}

double CameraHandler::get_upx() {
  return position.x + up.x;
}

double CameraHandler::get_upy() {
  return position.y + up.y;
}

double CameraHandler::get_upz() {
  return position.z + up.z;
}
