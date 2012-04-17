
#include <cstdio>
#include <cmath>

#include "vec3D.h"

#define PI 3.1415926535898

namespace ep1 {

GLdouble Vec3D::length () const {
  return sqrt(x_*x_ + y_*y_ + z_*z_);
}

GLdouble Vec3D::angle_to (const Vec3D& rhs) const {
  Vec3D diff = rhs.normalized() - this->normalized();
  return atan2(diff.y_, diff.x_)*180.0/PI;
}

Vec3D Vec3D::normalized () const {
  if (*this == Vec3D(0.0, 0.0, 0.0)) return *this;
  Vec3D norm = (*this)/length();
  return norm;
}

void Vec3D::dump () const {
  printf("<%lf, %lf, %lf>\n", x_, y_, z_);
}

} // namespace ep1

