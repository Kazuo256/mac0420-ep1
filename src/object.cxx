
#include "getglut.h"

#include "object.h"

namespace ep1 {

static void rotate_to_dir (const Vec3D& v) {
  Vec3D axis = Vec3D::Z() / v;
  GLdouble angle = Vec3D::Z().angle_to(v);
  glRotated(angle, axis.x(), axis.y(), axis.z());
}

void Object::render () const {
  glLoadIdentity();
  glTranslated(position_.x(), position_.y(), position_.z());
  glScaled(size_.x(), size_.y(), size_.z());
  rotate_to_dir(direction_);
  renderer_();
}

}

