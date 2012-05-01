
#ifndef EP1_OBJECT_H_
#define EP1_OBJECT_H_

#include <tr1/functional>
#include <tr1/memory>

#include "vec3D.h"

namespace ep1 {

/// Represents a renderable object.
class Object {
  public:
    /// Type used to store the rendering function of the object.
    /** It can store either pointer to functions or callable objects that
     ** satisfy the given signature. */
    typedef std::tr1::function<void (void)> Renderer;
    /// Type used to store the update function of the object.
    /** It can store either pointer to functions or callable objects that
     ** satisfy the given signature. */
    typedef std::tr1::function<void (Object&)> Updater;
    /// Reference-counting smart pointer for renderable objects.
    typedef std::tr1::shared_ptr<Object>    Ptr;
    Vec3D size () const { return size_; }
    /// Renders this object.
    /** Must be called whithin a glut display callback. */
    void render () const;
    /// Update this object.
    /** Must be called whithin a glut display callback. */
    void update ();
    /// Add a vector in the position of the object.
    void add_in_position (Vec3D add);
    /// Return the position vector.
    Vec3D get_position () const { return position_; }
    /// Return the object type.
    int get_type () const;
    /// Dump object info.
    void dump () const;
    /// Creates a new renderable object and returns it as a smart pointer.
    /** This guarantees that the user will never have to worry about freeing
     ** its memory.
     ** @param renderer The object's rendering function.
     ** @param position The object's position.
     ** @param size The object's size in the 3 axis.
     ** @param rotation The object's rotation in yaw-pitch-roll format.
     ** @return Object::Ptr Reference-counting smart pointer to the new
     **                     object. */
    static Ptr create (const Renderer& renderer,
                       const Updater& updater,                     
                       const Vec3D& position = Vec3D(),
                       const Vec3D& size = Vec3D(1.0, 1.0, 1.0),
                       const Vec3D& rotation = Vec3D(),
                       const int type = 0,
                       const unsigned id = 0) {
      return Ptr(new Object(renderer, updater, position, size, rotation, type, id));
    }
  private:
    /// 0 = Cone, 1 = Sphere
    int       type_;
    unsigned  id_;
    /// This object's rendering function.
    Renderer  renderer_;
    /// This object's rendering function.
    Updater   updater_;
    /// The object's position.
    Vec3D     position_;
    /// The objects size in the 3 axis.
    Vec3D     size_;
    /// The objects rotation in the yaw-pitch-roll format.
    Vec3D     rotation_;
    /// Constructor.
    /** @param renderer The object's rendering function.
     ** @param position The object's position.
     ** @param size The object's size in the 3 axis.
     ** @param rotation The object's rotation in yaw-pitch-roll format. */
    explicit Object (const Renderer& renderer,
                     const Updater updater,
                     const Vec3D& position = Vec3D(),
                     const Vec3D& size = Vec3D(1.0, 1.0, 1.0),
                     const Vec3D& rotation = Vec3D(),
                     const int type = 0,
                     const unsigned id = 0) :
      type_(type),
      id_(id),
      renderer_(renderer),
      updater_(updater),
      position_(position),
      size_(size),
      rotation_(rotation) {}
};

} // namespace ep1

#endif

