
#include <tr1/functional>

#include "getglut.h"
#include "simulation.h"
#include "utils.h"

namespace ep1 {

using std::string;
using std::vector;

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

static void dummy (Object& cone) {}

static void cone () {
  glPushMatrix();
  glTranslated(0.0, 0.0, -.5);
  glColor4d(0.0, 1.00, 0.00, 0.2);
  gluCylinder( gluNewQuadric(), 0.25, 0.0, 1.0, 6, 1);  
  glPopMatrix();
}

void Simulation::add_forces () {
  int x, y, z;
  for (z = 0; z < field_.depth(); z++ )
    for (y = 0; y < field_.height(); y++)
      for (x = 0; x < field_.width(); x++) {
        double size_factor =
          dists_.length()/field_.max_force().length();
        Vec3D position(dists_.x()*x, -dists_.y()*y, -dists_.z()*z);
        Vec3D size(1.0, 1.0,
                   field_.force(x,y,z).length()*size_factor);
        Vec3D rotation = Vec3D::dir(field_.force(x,y,z)); 
        win_->add_object(Object::create(Object::Renderer(cone),
                                       Object::Updater(dummy), 
                                       position, 
                                       size*ratio_, 
                                       rotation,
                                       0));
      }
}

static Vec3D transform_to_field (Vec3D position) {
  Vec3D ret(position.x(), -position.y(), -position.z()); 
  return ret;
} 

void Simulation::check_movement (Vec3D& move, const Vec3D& pos) const {
  Vec3D final_pos;

  final_pos = move+pos;
  if (final_pos.x() > (field_.width()-1)*dists_.x() || final_pos.x() < 0.0)
    move.set_x(0.0);
  if (-final_pos.y() > (field_.height()-1)*dists_.y() || -final_pos.y() < 0.0) 
    move.set_y(0.0);
  if (-final_pos.z() > (field_.depth()-1)*dists_.z() || -final_pos.z() < 0.0) 
    move.set_z(0.0);

}

void Simulation::update_particle (Object& particle) {
  Vec3D delta_pos, pos_field;
  pos_field = transform_to_field(particle.get_position());
  delta_pos = field_.interpolate(pos_field);
  delta_pos = delta_pos*(WIN_REFRESH*MILI*10);
  check_movement(delta_pos, particle.get_position());
  particle.add_in_position(delta_pos);
}

static void sphere (double radius) {
  glColor4d(1.0, 0.00, 0.00, 0.7);
  gluSphere( gluNewQuadric(), radius, 6, 6);  
}

static void updater (Simulation *sim, Object& particle) {
  sim->update_particle(particle);
}

struct particle_updater {
  Simulation* sim_;
  particle_updater(Simulation *sim) : sim_(sim) {}
  void operator () (Object& particle) {
    sim_->update_particle(particle);
  }
};

static Object::Updater make_updater (Simulation* sim) {
  return Object::Updater(particle_updater(sim));
}

void Simulation::add_particles () {
  int x, y, z;
  for (z = 0; z < field_.depth(); z++)
    for (y = 0; y < field_.height(); y++)
      for (x = 0; x < field_.width(); x++) {
        Vec3D position(dists_.x()*x, -dists_.y()*y, -dists_.z()*z);
        Vec3D size(1.0, 1.0, 1.0);
        Vec3D rotation;
        win_->add_object(Object::create(Object::Renderer(
                                        std::tr1::bind(
                                          sphere,
                                          dists_.min()/2.0
                                        )), 
                                        make_updater(this),
                                        position, 
                                        size*ratio_, 
                                        rotation,
                                        1));
      }
}

} // namespace ep1

