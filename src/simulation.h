
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

/// Represents a particle simulation.
class Simulation {
  public:
    /// Reference-counting smart pointer for simulation objects.
    typedef std::tr1::shared_ptr<Simulation> Ptr;
    /// Creates a new Simulation object.
    /** @param win    The window used to display the simulation.
     ** @param ratio  Size ratio used to render teh simulation elements.
     ** @return Simulation::Ptr A smart-pointer to a simulation object.
     */
    static Ptr create (const Window::Ptr& win, double ratio) {
      return Ptr(new Simulation(win, ratio));
    }
    /// Initializes the simulation from the given information file.
    /** The information file must follow the specification found in
     ** <b>EP1-2012.pdf</b>.
     ** @param info_file Path to the simulation information file.
     */
    void init (const std::string& info_file);
    void toggle_forces ();
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
    void update_particle (Object& particle);
    void check_movement (Vec3D& move, const Vec3D& pos) const;
};

} // namespace ep1

#endif

