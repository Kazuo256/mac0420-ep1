
#include <cmath>

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

static double calc_delta (double pos, double vertex) {
  return fabs(vertex - pos);
}

Vec3D ForceField::interpolate (const Vec3D& pos) const {
  Vec3D brn, f00, f01, f10, f11, f0, f1, aux; // brn = bottom_right_near 
  double delta;

  brn = pos.vec_floor();
  aux = brn;
  aux.set_x(aux.x()+1.0);
  delta = calc_delta(pos.x(), brn.x());
   
  f01 = force(brn)*(1-delta)+force(aux)*delta;
  
  brn.set_y(brn.y()+1.0);
  aux.set_y(aux.y()+1.0);
  
  f00 = force(brn)*(1-delta)+force(aux)*delta;
  
  brn.set_z(brn.z()+1.0); 
  aux.set_z(aux.z()+1.0);
  
  f10 = force(brn)*(1-delta)+force(aux)*delta;
  
  brn.set_y(brn.y()-1.0);
  aux.set_y(aux.y()-1.0);
  
  f11 = force(brn)*(1-delta)+force(aux)*delta;
  
  delta = calc_delta(pos.y(), brn.y());
  
  f1 = f01*(1-delta)+f00*delta;
  f0 = f10*delta+f11*(1-delta);

  delta = calc_delta(pos.z(), brn.z());
  
  return f1*delta+f0*(1-delta);
} 

} // namespace ep1

