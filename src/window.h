
#ifndef EP1_WINDOW_H_
#define EP1_WINDOW_H_

#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>
#include <tr1/memory>

#include "object.h"
#include "camera.h"

#define WIN_REFRESH 16 /* += 60 fps */
#define MILI 1e-3

namespace ep1 {

/// Represents a graphic window.
class Window {
  public:
    /// Reference-counting smart pointer for window objects.
    typedef std::tr1::shared_ptr<Window>  Ptr;
    /// Destructor.
    ~Window () {}
    /// Initializes the window.
    /** Even if created, a window is only displayed if it has been initialized
     ** before. */
    void init (double w, double h, double d);
    /// Gets the window's resolution ratio.
    double ratio () const { return 1.0*width_/height_; }
    /// Gets a reference to the window's camera.
    Camera& camera() { return camera_; }
    /// Sets this window as the current one, if needed.
    void set_current ();
    /// Adds an object to be drawn in the window.
    /** @param obj The object to de added. */
    void add_object (const Object::Ptr& obj);
    /// Creates a new window object.
    /** @param caption - The window's caption. */
    static Ptr create (const std::string& caption,
                       int width = 500, int height = 500) {
      Ptr created(new Window(caption, width, height));
      windows_[created->id_] = created;
      return created;
    }
  private:
    /// Glut window's id.
    int                       id_;
    /// Viewport width.
    int                       width_;
    /// Viewport height.
    int                       height_;
    /// Stop the timerfunc
    int                       stop_;
    /// Draw cones
    int                       draw_cone_;
    /// The window's camera into the scene.
    Camera                    camera_;
    /// Objects to be drawn.
    std::vector<Object::Ptr>  objects_;
    /// Indicates which mouse buttons are currently pressed.
    bool                      buttons_[3];
    /// Last mouse position detected.
    std::pair<int,int>        mouse_pos_;
    /// Reference base for all created windows.
    static std::tr1::unordered_map<int, Ptr> windows_;
    /// Constructor.
    /** @param caption - The window's caption. */
    explicit Window (const std::string& caption, int width, int height);
    /// Retrieves the current window.
    static Ptr current_window();
    /// Display callback function for all windows.
    static void display ();
    /// Idle callback function for all windows.
    static void timer_func (int value);
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

