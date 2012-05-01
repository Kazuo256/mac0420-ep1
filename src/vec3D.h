
#ifndef EP1_VEC3D_H_
#define EP1_VEC3D_H_

#include <cstring>

namespace ep1 {

class Vec3D {
  public:
    /// Constructor.
    /** @param x X-coordinate of the vector
     ** @param y Y-coordinate of the vector
     ** @param z Z-coordinate of the vector */
    explicit Vec3D (double x = 0.0, double y = 0.0, double z = 0.0) :
      x_(x), y_(y), z_(z) {}
    /// Construcor.
    /** @param val Arrays of double with size 3 containing the vector
     **            coordinates. */
    Vec3D (const double val[3]) :
      x_(val[0]), y_(val[1]), z_(val[2]) {}
    /// Gets the x-coordinate of the vector.
    /** @return double The x-coordinate of the vector. */
    double x () const { return x_; }
    /// Gets the y-coordinate of the vector.
    /** @return double The y-coordinate of the vector. */
    double y () const { return y_; }
    /// Gets the z-coordinate of the vector.
    /** @return double The z-coordinate of the vector. */
    double z () const { return z_; }
    /// Gets a read-only array of the vector's coordinates.
    /** @return const double[3] Read-only array of the vector's coordinates. */
    const double* val () const { return val_; }
    /// Sets the x-coordinate of the vector.
    /** @param x The new x-coordinate of the vector. */
    void set_x (double x) { x_ = x; }
    /// Sets the y-coordinate of the vector.
    /** @param y The new y-coordinate of the vector. */
    void set_y (double y) { y_ = y; }
    /// Sets the z-coordinate of the vector.
    /** @param z The new z-coordinate of the vector. */
    void set_z (double z) { z_ = z; }
    /// Sets all the vector's coordinates.
    /** @param val A 3-sized array with the new coordinates' value. */
    void set_val (const double val[3]) {
      memcpy(val_, val, 3*sizeof(double));
    }
    /// Sets all the vector's coordinates.
    /** @param x The new x-coordinate of the vector.
     ** @param y The new y-coordinate of the vector.
     ** @param z The new z-coordinate of the vector. */
    void set (double x, double y, double z) {
      x_ = x; y_ = y; z_ = z;
    }
    /// Checks if two vectors are the same.
    /** @param rhs Another vector.
     ** @return bool True if they are the same, false otherwise. */
    bool operator == (const Vec3D& rhs) const;
    /// Unary minus.
    Vec3D operator - () const;
    /// Addition.
    Vec3D operator + (const Vec3D& rhs) const;
    /// In-place addition.
    Vec3D& operator += (const Vec3D& rhs);
    /// Subtraction.
    Vec3D operator - (const Vec3D& rhs) const;
    /// Scalar product.
    double operator * (const Vec3D& rhs) const;
    /// Vectorial product.
    Vec3D operator / (const Vec3D& rhs) const;
    /// Product with scalar.
    Vec3D operator * (double rhs) const;
    /// Division by scalar.
    Vec3D operator / (double rhs) const;
    /// Calculates the length of this vector.
    /** @return double The length of this vector. */
    double length () const;
    /// Calculates the biggest component of this vector.
    /** @return double The biggest component of this vector. */
    double min () const;
    /// Calculates the smallest component of this vector.
    /** @return double The smallest component of this vector. */
    double max () const;
    /// Generates a vector with the floor values of this vector.
    /** @return Vec3D a vector with the floor values of this vector. */
    Vec3D vec_floor () const;
    /// Generates a vector with the ceil values of this vector.
    /** @return Vec3D a vector with the ceil values of this vector. */
    Vec3D vec_ceil () const;
    /// Calculates the absolute angle between two vectors.
    /** @param rhs Another vector.
     ** @return double The absolute angle between this and the ther vector. */
    double angle_to (const Vec3D& rhs) const;
    /// Makes a normalized version of this vector.
    /** @return Vec3D Normalized version of this vector. */
    Vec3D normalized () const;
    /// Dumps vector's information.
    void dump() const;
    /// X-axis canonical vector.
    /** @return Vec3D The (1,0,0) vector. */
    static Vec3D X () { return Vec3D(1.0, 0.0, 0.0); }
    /// Y-axis canonical vector.
    /** @return Vec3D The (0,1,0) vector. */
    static Vec3D Y () { return Vec3D(0.0, 1.0, 0.0); }
    /// Z-axis canonical vector.
    /** @return Vec3D The (0,0,1) vector. */
    static Vec3D Z () { return Vec3D(0.0, 0.0, 1.0); }
    /// Makes a vector in the yaw-pitch-roll format.
    /** These can be used to define an ep1::Object transformation.
     ** @param yaw Yaw angle.
     ** @param pitch Pitch angle.
     ** @param roll Roll angle.
     ** @return Vec3D Corresponding vector in the yaw-pitch-roll format. */
    static Vec3D ypr (double yaw, double pitch, double roll);
    /// Makes a vector in the yaw-pitch-roll format from a directional vector.
    /** This is used to make rotation vectors out of direction vectors. The up
     ** vector is a required infomation.
     ** @param v  A directional vector (does not need to be normalized)
     ** @param up The up vector (normalized) of the intended rotation.
     ** @return Vec3D Corresponding rotation vector in the yaw-pitch-woll
     **               format. */
    static Vec3D dir (const Vec3D& v, const Vec3D& up = Vec3D::Y()); 
  private:
    union {
      struct { double x_, y_, z_; };
      struct { double val_[3]; };
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

inline Vec3D& Vec3D::operator += (const Vec3D& rhs) {
  x_ += rhs.x_;
  y_ += rhs.y_;
  z_ += rhs.z_;
  return *this;
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

