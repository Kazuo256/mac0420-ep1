
#include "simulation.h"
#include "utils.h"

namespace ep1 {

using std::string;
using std::vector;

void Simulation::add_forces () {

}

void Simulation::add_particles () {

}

void Simulation::init (const string& info_file) {
  vector<Vec3D> infos = utils::LoadForceFieldInfo(info_file.c_str());
  size_ = infos[0];
  dists_ = infos[1];
  field_ = ForceField(size_.x(), size_.y(), size_.z());
  field_.load(infos.begin()+2);
  win_->init(size_.x(), size_.y(), size_.z());
  win_->camera().enframe(Vec3D(
    (size_.x()-1)*dists_.x()/2.0,
    -(size_.y()-1)*dists_.y()/2.0,
    -(size_.z()-1)*dists_.z()/2.0
  ));
  add_forces();
  add_particles();
}

} // namespace ep1

