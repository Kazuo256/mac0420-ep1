
#ifndef EP1_FORCEFIELD_H_
#define EP1_FORCEFIELD_H_

#include <vector>

#include "vec3D.h"

namespace ep1 {

class ForceField {
  public:
    explicit ForceField (int width, int height, int depth) :
      width_(width), height_(height), depth_(depth),
      forces_(depth, matrix(height, std::vector<Vec3D>(width, Vec3D()))) {}
    void set_force (int x, int y, int z, const Vec3D& f) {
      forces_[z][y][x] = f;
    }
    Vec3D force (int x, int y, int z) const {
      return forces_[z][y][x];
    }
    int width () const { return width_; }
    int height () const { return height_; }
    int depth () const { return depth_; }
  private:
    typedef std::vector< std::vector<Vec3D> > matrix;
    typedef std::vector< matrix >             cube;
    int   width_, height_, depth_;
    cube  forces_;
};

} // namespace ep1

#endif

