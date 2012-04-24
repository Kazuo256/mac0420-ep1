
#ifndef EP1_VEC3D_H_
#define EP1_VEC3D_H_

#include <cstring>

namespace ep1 {

class Vec3D {
  public:
    explicit Vec3D (double x = 0.0, double y = 0.0, double z = 0.0) :
      x_(x), y_(y), z_(z) {}
    Vec3D (const double val[3]) :
      x_(val[0]), y_(val[1]), z_(val[2]) {}
    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }
    const double* val() const { return val_; }
    void set_x(double x) { x_ = x; }
    void set_y(double y) { y_ = y; }
    void set_z(double z) { z_ = z; }
    void set_val(const double val[3]) {
      memcpy(val_, val, 3*sizeof(double));
    }
    bool operator == (const Vec3D& rhs) const;
    Vec3D operator - () const;
    Vec3D operator + (const Vec3D& rhs) const;
    Vec3D operator - (const Vec3D& rhs) const;
    double operator * (const Vec3D& rhs) const;
    /** Vetorial product. */
    Vec3D operator / (const Vec3D& rhs) const;
    Vec3D operator * (double rhs) const;
    Vec3D operator / (double rhs) const;
    double length () const;
    double angle_to (const Vec3D& rhs) const;
    Vec3D normalized () const;
    void dump() const;
    static Vec3D X () { return Vec3D(1.0, 0.0, 0.0); }
    static Vec3D Y () { return Vec3D(0.0, 1.0, 0.0); }
    static Vec3D Z () { return Vec3D(0.0, 0.0, 1.0); }
    static Vec3D ypr (double yaw, double pitch, double roll);
    static Vec3D dir (const Vec3D& v, const Vec3D& up = Vec3D::Y()); 
  private:
    union {
      struct {
        double x_, y_, z_;
      };
      double val_[3];
    };
};

inline bool Vec3D::operator == (const Vec3D& rhs) const {
  return x_ == rhs.x_ &&
         y_ == rhs.y_ &&
         z_ == rhs.z_;
}

inline Vec3D Vec3D::operator - () const {
  return Vec3D(-x_, -y_, -z_);
}

inline Vec3D Vec3D::operator + (const Vec3D& rhs) const {
  return Vec3D(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
}

inline Vec3D Vec3D::operator - (const Vec3D& rhs) const {
  return *this + (-rhs);
}

inline double Vec3D::operator * (const Vec3D& rhs) const {
  return x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_;
}

inline Vec3D Vec3D::operator / (const Vec3D& rhs) const {
  return Vec3D(y_*rhs.z_ - z_*rhs.y_,
               z_*rhs.x_ - x_*rhs.z_,
               x_*rhs.y_ - y_*rhs.x_);
}

inline Vec3D Vec3D::operator * (double rhs) const {
  return Vec3D(x_*rhs, y_*rhs, z_*rhs);
}

inline Vec3D Vec3D::operator / (double rhs) const {
  return Vec3D(x_/rhs, y_/rhs, z_/rhs);
}

} // namespace ep1

#endif

