
#ifndef EP1_OBJECT_H_
#define EP1_OBJECT_H_

#include <tr1/functional>

#include "getglut.h"
#include "vec3D.h"

namespace ep1 {

class Object {
  public:
    typedef std::tr1::function< void (void) > Renderer;
    explicit Object (const Renderer& renderer,
                     const Vec3D& position = Vec3D(),
                     const Vec3D& size = Vec3D(1.0, 1.0, 1.0),
                     const Vec3D& direction = Vec3D::Z()) :
      renderer_(renderer),
      position_(position),
      size_(size),
      direction_(direction) {}
    void render () const;
  private:
    Renderer  renderer_;
    Vec3D     position_,
              size_,
              direction_;
};

} // namespace ep1

#endif

