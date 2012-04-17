
#include <cstdio>
#include "getglut.h"

#include "object.h"

namespace ep1 {

static void rotate_to_dir (const Vec3D& v) {
  puts("z norm");
  Vec3D::Z().normalized().dump();
  Vec3D axis = Vec3D::Z() / v;
  GLdouble angle = Vec3D::Z().angle_to(v);
  axis.dump();
  printf("angle %lf\n", angle);
  glRotated(angle, axis.x(), axis.y(), axis.z());
}

void Object::render () const {
  glLoadIdentity();
  glTranslated(position_.x(), position_.y(), position_.z());
  glScaled(size_.x(), size_.y(), size_.z());
  direction_.dump();
  rotate_to_dir(direction_);
  renderer_();
}

}

