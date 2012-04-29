
#include <cstdio>
#include <cmath>

#include <algorithm>

#include "vec3D.h"

#define PI 3.1415926535898

namespace ep1 {

double Vec3D::length () const {
  return sqrt(x_*x_ + y_*y_ + z_*z_);
}

double Vec3D::min () const {
  if (x_ < y_)
    if (x_ < z_) return x_;
    else return z_;
  else if (y_ < z_) return y_;
  else return z_;
}

double Vec3D::max () const {
  return std::max(x_, std::max(y_, z_));
}

Vec3D Vec3D::vec_floor () {
  Vec3D ret = (*this);
  ret.x_ = floor(ret.x_);
  ret.y_ = floor(ret.y_);
  ret.z_ = floor(ret.z_);

  return ret;
} 

Vec3D Vec3D::vec_ceil () {
  Vec3D ret = (*this);
  ret.x_ = ceil(ret.x_);
  ret.y_ = ceil(ret.y_);
  ret.z_ = ceil(ret.z_);

  return ret;
}

double Vec3D::angle_to (const Vec3D& rhs) const {
  if (*this == rhs) return 0.0;
  /*
  Vec3D proj = rhs*((*this)*rhs.normalized()),
        dist = *this - proj;
  double angle = atan2(
    dist.length(),
    proj.length()
  );
  return angle;
  */
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

