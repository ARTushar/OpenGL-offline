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
  step = 2;
  angle = 3;
}

CameraHandler::CameraHandler(Point pos, Point l, Point u, Point r, double step, double angle):
        position(pos), look(l), up(u), right(r), step(step), angle(angle)
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

void CameraHandler::look_left() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) + look * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  look = look * cos(angle * pi / 180) - right * sin(angle * pi / 180);
  look = convert_to_unit(look);

  right = new_right;
}

void CameraHandler::look_right() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) - look * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  look = look * cos(angle * pi / 180) + right * sin(angle * pi / 180);
  look = convert_to_unit(look);

  right = new_right;

}

void CameraHandler::look_up() {
  Point new_look;
  new_look = look * cos(angle * pi / 180) + up * sin(angle * pi / 180);
  new_look = convert_to_unit(new_look);

  up = up * cos(angle * pi / 180) - look * sin(angle * pi / 180);
  up = convert_to_unit(up);

  look = new_look;
}

void CameraHandler::look_down() {
  Point new_look;
  new_look = look * cos(angle * pi / 180) - up * sin(angle * pi / 180);
  new_look = convert_to_unit(new_look);

  up = up * cos(angle * pi / 180) + look * sin(angle * pi / 180);
  up = convert_to_unit(up);

  look = new_look;

}

void CameraHandler::tilt_c() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) - up * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  up = up * cos(angle * pi / 180) + right * sin(angle * pi / 180);
  up = convert_to_unit(up);

  right = new_right;
}

void CameraHandler::tilt_cc() {
  Point new_right;
  new_right = right * cos(angle * pi / 180) + up * sin(angle * pi / 180);
  new_right = convert_to_unit(new_right);

  up = up * cos(angle * pi / 180) - right * sin(angle * pi / 180);
  up = convert_to_unit(up);

  right = new_right;

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
  return up.x;
}

double CameraHandler::get_upy() {
  return up.y;
}

double CameraHandler::get_upz() {
  return up.z;
}

Point CameraHandler::convert_to_unit(Point& a) {
  double val = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
  return  {a.x / val, a.y / val, a.z / val};
}

