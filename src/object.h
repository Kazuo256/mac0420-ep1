
#ifndef EP1_OBJECT_H_
#define EP1_OBJECT_H_

#include <tr1/functional>
#include <tr1/memory>

#include "vec3D.h"

namespace ep1 {

class Object {
  public:
    typedef std::tr1::function<void (void)> Renderer;
    typedef std::tr1::shared_ptr<Object>    Ptr;
    void render () const;
    static Ptr create (const Renderer& renderer,
                       const Vec3D& position = Vec3D(),
                       const Vec3D& size = Vec3D(1.0, 1.0, 1.0),
                       const Vec3D& rotation = Vec3D()) {
      return Ptr(new Object(renderer, position, size, rotation));
    }
  private:
    Renderer  renderer_;
    Vec3D     position_,
              size_,
              rotation_;
    explicit Object (const Renderer& renderer,
                     const Vec3D& position = Vec3D(),
                     const Vec3D& size = Vec3D(1.0, 1.0, 1.0),
                     const Vec3D& rotation = Vec3D()) :
      renderer_(renderer),
      position_(position),
      size_(size),
      rotation_(rotation) {}
};

} // namespace ep1

#endif

