
#ifndef EP1_CAMERA_H_
#define EP1_CAMERA_H_

#include "vec3D.h"

namespace ep1 {

class Camera {
  public:
    Camera () :
      perspective_(false) {}
    void set_pos (const Vec3D& pos) { pos_ = pos; }
    void set_target (const Vec3D& target) { target_ = target; }
    void move (const Vec3D& d) {
      pos_ += d;
      target_ += d;
    }
    void closein (double d);
    void set_view (double width, double height, double depth) {
      view_ = Vec3D(width, height, depth);
    }
    void enframe (const Vec3D& target);
    void set_ortho (double ratio);
    void set_perspective (double ratio);
    void toggle_projection (double ratio);
    void adjust (double ratio);
    void use () const;
  private:
    Vec3D           view_;
    Vec3D           pos_, target_;
    bool            perspective_;
};

} // namespace ep1

#endif

