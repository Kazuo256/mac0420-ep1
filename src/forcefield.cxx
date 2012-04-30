
#include "forcefield.h"

namespace ep1 {

using std::vector;

void ForceField::load (vector<Vec3D>::iterator it) {
  int x, y, z;
 
  max_force_ = min_force_ = *it;
  for (z = 0; z < depth_; z++)
    for (y = 0; y < height_; y++) 
      for (x = 0; x < width_; x++) {
        if (it->length() > max_force_.length())
          max_force_ = *it;
        else if (it->length() < min_force_.length())
          min_force_ = *it;
        forces_[z][y][x] = Vec3D(it->x(), -it->y(), -it->z());
        ++it;
      }
}

} // namespace ep1

