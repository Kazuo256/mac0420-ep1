
#ifndef EP1_VEC3D_H_
#define EP1_VEC3D_H_

#include "getglut.h"
#include <cstring>

namespace ep1 {

class Vec3D {
  public:
    explicit Vec3D (GLdouble x, GLdouble y, GLdouble z) :
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
    void set_val(const GLdouble val[3]) { memcpy(val_, val, 3*sizeof(GLdouble)); }
  private:
    union {
      struct {
        GLdouble x_, y_, z_;
      };
      GLdouble val_[3];
    };
};

} // namespace ep1

#endif

