
#include <cstdio>
#include <cmath>

#include "vec3D.h"

#define PI 3.1415926535898

namespace ep1 {

double Vec3D::length () const {
  return sqrt(x_*x_ + y_*y_ + z_*z_);
}

double Vec3D::angle_to (const Vec3D& rhs) const {
  if (*this == rhs) return 0.0;
  else return acos(normalized()*rhs.normalized())*180.0/PI;
}

Vec3D Vec3D::normalized () const {
  if (*this == Vec3D(0.0, 0.0, 0.0)) return *this;
  Vec3D norm = (*this)/length();
  return norm;
}

void Vec3D::dump () const {
  printf("<%lf, %lf, %lf>\n", x_, y_, z_);
}

Vec3D Vec3D::ypr (double yaw, double pitch, double roll) {
  return Vec3D(pitch, yaw, roll);
}

Vec3D ortho (const Vec3D& v, const Vec3D& up) {
  Vec3D result;

  result = v/up;
  return result/v;
}

Vec3D Vec3D::dir (const Vec3D& v, const Vec3D& up) {
  Vec3D v_dir, aux, y;
  double yaw, pitch, roll;

  aux = v;
  aux.set_y(0.0);
  pitch = aux.angle_to(v);

  yaw = aux.angle_to(Vec3D::Z());

  aux = ortho(v, up);
  y = ortho(v, Vec3D::Y());
  roll = aux.angle_to(y);
  
  return ypr(yaw, pitch, roll);
}

} // namespace ep1

