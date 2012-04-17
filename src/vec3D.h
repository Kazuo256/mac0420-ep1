
#ifndef EP1_VEC3D_H_
#define EP1_VEC3D_H_

#include "getglut.h"
#include <cstring>

namespace ep1 {

class Vec3D {
  public:
    explicit Vec3D (GLdouble x = 0.0, GLdouble y = 0.0, GLdouble z = 0.0) :
      x_(x), y_(x), z_(z) {}
    Vec3D (const GLdouble val[3]) :
      x_(val[0]), y_(val[1]), z_(val[2]) {}
    GLdouble x() const { return x_; }
    GLdouble y() const { return y_; }
    GLdouble z() const { return z_; }
    const GLdouble* val() const { return val_; }
    void set_x(GLdouble x) { x_ = x; }
    void set_y(GLdouble y) { y_ = y; }
    void set_z(GLdouble z) { z_ = z; }
    void set_val(const GLdouble val[3]) {
      memcpy(val_, val, 3*sizeof(GLdouble));
    }
    Vec3D operator - () const;
    Vec3D operator + (const Vec3D& rhs) const;
    Vec3D operator - (const Vec3D& rhs) const;
    /** Vetorial product. */
    Vec3D operator / (const Vec3D& rhs) const;
    Vec3D operator * (GLdouble rhs) const;
    Vec3D operator / (GLdouble rhs) const;
    GLdouble length () const;
    GLdouble angle_to (const Vec3D& rhs) const;
    Vec3D normalized () const;
    static Vec3D X() { return Vec3D(1.0, 0.0, 0.0); }
    static Vec3D Y() { return Vec3D(0.0, 1.0, 0.0); }
    static Vec3D Z() { return Vec3D(0.0, 0.0, 1.0); }
  private:
    union {
      struct {
        GLdouble x_, y_, z_;
      };
      GLdouble val_[3];
    };
};

inline Vec3D Vec3D::operator - () const {
  return Vec3D(-x_, -y_, -z_);
}

inline Vec3D Vec3D::operator + (const Vec3D& rhs) const {
  return Vec3D(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
}

inline Vec3D Vec3D::operator - (const Vec3D& rhs) const {
  return *this + (-rhs);
}

inline Vec3D Vec3D::operator / (const Vec3D& rhs) const {
  return Vec3D(y_*rhs.z_ - z_*rhs.y_,
               z_*rhs.x_ - x_*rhs.z_,
               x_*rhs.y_ - y_*rhs.x_);
}

} // namespace ep1

#endif

