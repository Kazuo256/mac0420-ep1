
#ifndef EP1_VEC3D_H_
#define EP1_VEC3D_H_

#include <cstring>

namespace ep1 {

class Vec3D {
  public:
    explicit Vec3D (double x, double y, double z) :
      x_(x), y_(x), z_(z) {}
    Vec3D (const double val[3]) :
      x_(val[0]), y_(val[1]), z_(val[2]) {}
    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }
    const double* val() const { return val_; }
    void set_x(double x) { x_ = x; }
    void set_y(double y) { y_ = y; }
    void set_z(double z) { z_ = z; }
    void set_val(const double val[3]) { memcpy(val_, val, 3*sizeof(double)); }
  private:
    union {
      struct {
        double x_, y_, z_;
      };
      double val_[3];
    };
};

} // namespace ep1

#endif

