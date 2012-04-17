
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
                     const Vec3D& position,
                     const Vec3D& direction,
                     const Vec3D& size) :
      renderer_(renderer),
      position_(position),
      direction_(direction),
      size_(size) {}
    void render () const;
  private:
    Renderer  renderer_;
    Vec3D     position_,
              direction_,
              size_;
};

} // namespace ep1

#endif

