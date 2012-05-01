
#include <cstdio>

#include "getglut.h"
#include "object.h"

namespace ep1 {

static void rotate_to_dir (const Vec3D& v) {
  glRotated(v.y(), 0.0, 1.0, 0.0); // yaw
  glRotated(v.x(), 1.0, 0.0, 0.0); // pitch
  glRotated(v.z(), 0.0, 0.0, 1.0); // roll
}

void Object::add_in_position (Vec3D add) {
  position_ += add;
}

void Object::render () const {
  if (!visible_) return;
  glTranslated(position_.x(), position_.y(), position_.z());
  rotate_to_dir(rotation_);
  glScaled(size_.x(), size_.y(), size_.z());
  renderer_();
}

void Object::dump () const {
  position_.dump();
}

void Object::update () {
  updater_(*this);
}

}

