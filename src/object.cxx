
#include <cstdio>

#include "getglut.h"
#include "object.h"

namespace ep1 {

static void rotate_to_dir (const Vec3D& v) {
//  Vec3D axis = Vec3D::Z() / v;
//  GLdouble angle = Vec3D::Z().angle_to(v);
//  axis.dump();
//  printf("angle %lf\n", angle);
//  glRotated(angle, axis.x(), axis.y(), axis.z());
  glRotated(v.y(), 0.0, 1.0, 0.0); // yaw
  glRotated(v.x(), 1.0, 0.0, 0.0); // pitch
  glRotated(v.z(), 0.0, 0.0, 1.0); // roll
}

void Object::add_in_position (Vec3D add) {
  position_ += add;
}

void Object::render () const {
  glTranslated(position_.x(), position_.y(), position_.z());
  rotate_to_dir(rotation_);
  glScaled(size_.x(), size_.y(), size_.z());
  renderer_();
}

void Object::update () {
  updater_(*this);
}

}

