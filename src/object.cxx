
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
  glRotated(v.y(), 0.0, 1.0, 0.0);
  glRotated(v.x(), 1.0, 0.0, 0.0);
  glRotated(v.z(), 0.0, 0.0, 1.0);
}

void Object::render () const {
  glLoadIdentity();
  glTranslated(position_.x(), position_.y(), position_.z());
  glScaled(size_.x(), size_.y(), size_.z());
  rotation_.dump();
  rotate_to_dir(rotation_);
  renderer_();
}

}

