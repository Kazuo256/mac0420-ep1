
#ifndef EP1_SIMULATION_H_
#define EP1_SIMULATION_H_

#include <string>
#include <vector>

#include <tr1/memory>

#include "vec3D.h"
#include "window.h"
#include "forcefield.h"
#include "object.h"

namespace ep1 {

class Simulation {
  public:
    typedef std::tr1::shared_ptr<Simulation> Ptr;
    static Ptr create (const Window::Ptr& win, double ratio) {
      return Ptr(new Simulation(win, ratio));
    }
    void init (const std::string& info_file);
    void toggle_forces ();
    void update_particle (Object& particle);
  private:
    double                    ratio_;
    Vec3D                     size_,
                              dists_;
    Window::Ptr               win_;
    ForceField                field_;
    std::vector<Object::Ptr>  forces_,
                              particles_;
    explicit Simulation (const Window::Ptr& win, double ratio) :
      ratio_(ratio), win_(win) {}
    void add_forces ();
    void add_particles ();
    void check_movement (Vec3D& move, const Vec3D& pos) const;
};

} // namespace ep1

#endif

