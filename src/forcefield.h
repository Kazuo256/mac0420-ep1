
#ifndef EP1_FORCEFIELD_H_
#define EP1_FORCEFIELD_H_

#include <vector>
#include <cstdio>
#include "vec3D.h"

namespace ep1 {

/// Represents a force field.
class ForceField {
  public:
    /// Constructor.
    /** @param width  The field width.
     ** @param height The field height.
     ** @param depth  The field depth. */
    explicit ForceField (int width = 0, int height = 0, int depth = 0) :
      width_(width), height_(height), depth_(depth),
      forces_(depth, matrix(height, std::vector<Vec3D>(width, Vec3D()))) {}
    /// Load the forces from the given stream of vectors.
    /** @param it Iterator to a stream of force vectors. */
    void load (std::vector<Vec3D>::iterator it);
    /// Gets the force at the given position.
    /** Forces outside the field default to zero.
     ** @param x X-coordinate of the force.
     ** @param y Y-coordinate of the force.
     ** @param z Z-coordinate of the force.
     ** @return Vec3D Force at the given position. */
    Vec3D force (int x, int y, int z) const {
      if (x < 0 || y < 0 || z < 0 || x >= width_ || y >= height_ || z >= depth_)
        return Vec3D();
      return forces_[z][y][x];
    }
    /// Gets the force at the given position, truncated to integral coordinates.
    /** @param ref Position whose floor'd coordinates lead to the wanted
     **            force.
     ** @return Vec3D Force at the given truncated position. */
    Vec3D force (Vec3D ref) const {
      int x, y, z;
      x = (int)ref.x();
      y = (int)ref.y();
      z = (int)ref.z();
      return force(x, y, z);
    }
    /// Gets the interpolated force at the given position.
    /** Uses trilinear interpolation.
     ** @param pos A position within the force field.
     ** @result Vec3D The interpolated force at the given position. */
    Vec3D interpolate (const Vec3D& pos) const;
    /// Gets the biggest force within the field.
    /** @return Vec3D The biggest force within the field. */
    Vec3D max_force () const { return max_force_; }
    /// Gets the smallest force within the field.
    /** @return Vec3D The smallest force within the field. */
    Vec3D min_force () const { return min_force_; }
    /// Gets the field's width.
    /** @return int The field's width. */
    int width () const { return width_; }
    /// Gets the field's height.
    /** @return int The field's height. */
    int height () const { return height_; }
    /// Gets the field's depth.
    /** @return int The field's depth. */
    int depth () const { return depth_; }
  private:
    typedef std::vector< std::vector<Vec3D> > matrix;
    typedef std::vector< matrix >             cube;
    int   width_, height_, depth_;
    cube  forces_;
    Vec3D max_force_, min_force_;
};

} // namespace ep1

#endif

