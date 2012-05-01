
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
    /// Gets the size transformation of this object.
    /** @return Vec3D The size transformation of this object. */
    Vec3D size () const { return size_; }
    /// Toggles object visibility.
    void toggle_visibility () {
      visible_ = !visible_;
    }
    /// Renders this object.
    /** Must be called whithin a glut display callback. */
    void render () const;
    /// Updates this object.
    /** Must be called whithin a glut timed callback. */
    void update ();
    /// Adds a vector to the position of the object.
    /** @param add Vectorial addition to the object's position. */
    void add_to_position (const Vec3D& add) {
      position_ += add;
    }
    /// Gets the object's position transformation.
    /** @return Vec3D The object's position transformation.*/
    Vec3D position () const { return position_; }
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
                       const Vec3D& rotation = Vec3D()) {
      return Ptr(new Object(renderer, updater, position, size, rotation));
    }
  private:
    // Visibility flag.
    bool      visible_;
    // This object's rendering function.
    Renderer  renderer_;
    // This object's rendering function.
    Updater   updater_;
    // The object's position.
    Vec3D     position_;
    // The objects size in the 3 axis.
    Vec3D     size_;
    // The objects rotation in the yaw-pitch-roll format.
    Vec3D     rotation_;
    /// Constructor. See Object::create.
    explicit Object (const Renderer& renderer,
                     const Updater updater,
                     const Vec3D& position,
                     const Vec3D& size,
                     const Vec3D& rotation) :
      visible_(true),
      renderer_(renderer),
      updater_(updater),
      position_(position),
      size_(size),
      rotation_(rotation) {}
};

} // namespace ep1

#endif

