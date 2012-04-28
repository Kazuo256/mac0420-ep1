
#include <cmath>

#include <algorithm>

#include "getglut.h"
#include "camera.h"

namespace ep1 {

void Camera::enframe (const Vec3D& target) {
  pos_ = Vec3D(target.x(), target.y(), target.z() + view_.z());
  target_ = target;
}

void Camera::closein (double d) {
  Vec3D diff = pos_ - target_;
  pos_ = target_ + diff*(1.0/pow(2.0, d));
}

void Camera::set_ortho (double ratio) {
  perspective_ = false;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double max_dimension =
    std::max(std::max(view_.x(), view_.y()), view_.z());
  glOrtho(
    -0.75*max_dimension, 0.75*max_dimension,
    -0.75*max_dimension, 0.75*max_dimension,
    -2.0*max_dimension, 10.0*max_dimension
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

void Camera::use () const {
  gluLookAt(pos_.x(), pos_.y(), pos_.z(),
            target_.x(), target_.y(), target_.z(),
            0.0, 1.0, 0.0);
}

} // namespace ep1

