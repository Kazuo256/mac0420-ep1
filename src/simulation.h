
#ifndef EP1_SIMULATION_H_
#define EP1_SIMULATION_H_

#include <string>
#include <vector>

#include "vec3D.h"
#include "window.h"
#include "forcefield.h"

namespace ep1 {

class Simulation {
  public:
    explicit Simulation (const Window::Ptr& win) :
      win_(win) {}
    void init (const std::string& info_file);
  private:
    Vec3D       size_, dists_;
    Window::Ptr win_;
    ForceField  field_;
    void add_forces ();
    void add_particles ();
};

} // namespace ep1

#endif

