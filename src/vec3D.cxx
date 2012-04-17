
#include <cmath>

#include "vec3D.h"

#define PI 3.1415926535898

namespace ep1 {

GLdouble Vec3D::length () const {
  return sqrt(x_*x_ + y_*y_);
}

GLdouble Vec3D::angle_to (const Vec3D& rhs) const {
  Vec3D diff = rhs - *this;
  return atan2(diff.y_, diff.x_)*180.0/PI;
}

} // namespace ep1

