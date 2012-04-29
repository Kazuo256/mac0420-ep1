
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
  //Vec3D diff = pos_ - target_;
  //pos_ = target_ + diff*(1.0/pow(2.0, d));
  sphere_pos_.set_z(sphere_pos_.z()*(1.0/pow(2.0, d)));
}

void Camera::set_ortho (double ratio) {
  perspective_ = false;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double max_dimension = std::max(view_.x(), view_.y());
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

void Camera::use () const {
  glTranslated(0.0, 0.0, -sphere_pos_.z());
  glRotated(-sphere_pos_.y(), 1.0, 0.0, 0.0);
  glRotated(sphere_pos_.x(), 0.0, 1.0, 0.0);
  glTranslated(-target_.x(), -target_.y(), -target_.z());
  /*
  gluLookAt(pos_.x(), pos_.y(), pos_.z(),
            target_.x(), target_.y(), target_.z(),
            0.0, 1.0, 0.0);
            */
}

} // namespace ep1

