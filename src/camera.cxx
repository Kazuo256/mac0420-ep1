
#include <cmath>

#include <algorithm>

#include "getglut.h"
#include "camera.h"

namespace ep1 {

void Camera::enframe (const Vec3D& target) {
  sphere_pos_.set(0.0, 0.0, 2.0*view_.z());
  target_ = target;
}

void Camera::zoom (double d) {
  sphere_pos_.set_z(sphere_pos_.z()*(1.0/pow(2.0, d)));
}

void Camera::set_ortho (double ratio) {
  perspective_ = false;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double max_dimension = std::max(view_.x(), view_.y());
  // I say it in portuguese to make it clear.
  // Eu perguntei no PACA se era ou não pra ajustar o tamanho dos objetos
  // quando ocorresse zoom na visão ortogonal. Como o monitor não respondeu,
  // deixei exatamente como o enunciado pediu: apenas mudo a distância da
  // camera.
  if (ratio >= 1.0)
    glOrtho(
      -ratio*0.75*max_dimension, ratio*0.75*max_dimension,
      -0.75*max_dimension, 0.75*max_dimension,
      -2.0*view_.z(), 10.0*view_.z()
    );
  else
    glOrtho(
      -0.75*max_dimension, 0.75*max_dimension,
      -0.75*max_dimension/ratio, 0.75*max_dimension/ratio,
      -2.0*view_.z(), 10.0*view_.z()
    );
}

void Camera::set_perspective (double ratio) {
  perspective_ = true;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
    60.0, ratio,
    view_.z()*0.1, view_.z()*10.0
  );
  glMatrixMode(GL_MODELVIEW);
}

void Camera::toggle_projection (double ratio) {
  if (perspective_)
    set_ortho(ratio);
  else
    set_perspective(ratio);
  glutPostRedisplay();
}

void Camera::adjust (double ratio) {
  if (perspective_)
    set_perspective(ratio);
  else
    set_ortho(ratio);
}

void Camera::place () const {
  // Adjusts camera zoom.
  glTranslated(0.0, 0.0, -sphere_pos_.z());
  // Signs here are kind of arbitrary. It depends on how you want the camera to
  // move.
  glRotated(-sphere_pos_.y(), 1.0, 0.0, 0.0);
  glRotated(sphere_pos_.x(), 0.0, 1.0, 0.0);
  // Moves to the camera's target.
  glTranslated(-target_.x(), -target_.y(), -target_.z());
}

} // namespace ep1

