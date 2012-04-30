
#ifndef EP1_FORCEFIELD_H_
#define EP1_FORCEFIELD_H_

#include <vector>
#include <cstdio>
#include "vec3D.h"

namespace ep1 {

class ForceField {
  public:
    explicit ForceField (int width = 0, int height = 0, int depth = 0) :
      width_(width), height_(height), depth_(depth),
      forces_(depth, matrix(height, std::vector<Vec3D>(width, Vec3D()))) {}
    void load (std::vector<Vec3D>::iterator it);
    void set_force (int x, int y, int z, const Vec3D& f) {
      forces_[z][y][x] = f;
    }
    Vec3D force (int x, int y, int z) const {
      if (x < 0 || y < 0 || z < 0 || x >= width_ || y >= height_ || z >= depth_)
        return Vec3D();
      return forces_[z][y][x];
    }
    Vec3D force (Vec3D ref) const {
      int x, y, z;
      x = (int)ref.x();
      y = (int)ref.y();
      z = (int)ref.z();
      return force(x, y, z);
    }
    Vec3D interpolate (const Vec3D& pos) const;
    Vec3D max_force () const { return max_force_; }
    Vec3D min_force () const { return min_force_; }
    int width () const { return width_; }
    int height () const { return height_; }
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

