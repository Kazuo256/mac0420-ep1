
#ifndef EP1_CAMERA_H_
#define EP1_CAMERA_H_

#include "vec3D.h"

namespace ep1 {

class Camera {
  public:
    Camera () :
      sphere_pos_(0.0, 0.0, 1.0),
      perspective_(false) {}
    void set_target (const Vec3D& target) { target_ = target; }
    void move (const Vec3D& delta) {
      sphere_pos_ += Vec3D::X()*delta.x() + Vec3D::Y()*delta.y();
    }
    void set_view (double width, double height, double depth) {
      view_ = Vec3D(width, height, depth);
    }
    void enframe (const Vec3D& target);
    void zoom (double delta);
    void set_ortho (double ratio);
    void set_perspective (double ratio);
    void toggle_projection (double ratio);
    void adjust (double ratio);
    void place () const;
  private:
    Vec3D view_;
    Vec3D sphere_pos_;
    Vec3D target_;
    bool  perspective_;
};

} // namespace ep1

#endif

