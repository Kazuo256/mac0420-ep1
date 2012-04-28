
#ifndef EP1_WINDOW_H_
#define EP1_WINDOW_H_

#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>
#include <tr1/memory>

#include "object.h"

namespace ep1 {

/// Represents a graphic window.
class Window {
  public:
    /// Reference-counting smart pointer for window objects.
    typedef std::tr1::shared_ptr<Window> Ptr;
    /// Destructor.
    ~Window () {}
    /// Initializes the window.
    /** Even if created, a window is only displayed if it has been initialized
     ** before. */
    void init (double w, double h, double d);
    /// Starts the objects update.
    void update_objects ();
    /// Adds an object to be drawn in the window.
    /** @param obj The object to de added. */
    void add_object (const Object::Ptr& obj);
    /// Activates orthgonal projection.
    void set_ortho ();
    /// Activates perspective projection.
    void set_perspective ();
    /// Toggles between orthogonal and perspective projection.
    void toggle_projection ();
    /// Creates a new window object.
    /** @param caption - The window's caption. */
    static Ptr create (const std::string& caption) {
      Ptr created(new Window(caption));
      windows_[created->id_] = created;
      return created;
    }
  private:
    /// Glut window's id.
    int                       id_;
    /// Space width.
    double                    width_;
    /// Space height.
    double                    height_;
    /// Space depth.
    double                    depth_;
    /// Objects to be drawn.
    std::vector<Object::Ptr>  objects_;
    /// Camera position.
    ep1::Vec3D                camera_pos_;
    /// Camera target.
    ep1::Vec3D                camera_target_;
    /// Camera perspective projection flag.
    bool                      perspective_;
    /// Indicates which mouse buttons are currently pressed.
    bool                      buttons_[3];
    /// Last mouse position detected.
    std::pair<int,int>        mouse_pos_;
    /// Reference base for all created windows.
    static std::tr1::unordered_map<int, Ptr> windows_;
    /// Constructor.
    /** @param caption - The window's caption. */
    explicit Window (const std::string& caption);
    /// Sets this window as the current one, if needed.
    void set_current ();
    /// Retrieves the current window.
    static Ptr current_window();
    /// Display callback function for all windows.
    static void display ();
    /// Reshape callback function for all windows.
    static void reshape (int w, int h);
    /// Mouse callback function for all windows.
    static void mouse (int btn, int state, int x, int y);
    /// Mouse motion callback function for all windows.
    static void motion (int x, int y);
    /// Keyboard callsback function for all windows.
    static void keyboard (unsigned char key, int x, int y);
};

} // namespace ep1

#endif

