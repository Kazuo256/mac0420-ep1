
#ifndef EP1_WINDOW_H_
#define EP1_WINDOW_H_

#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>
#include <tr1/memory>

#include "object.h"
#include "camera.h"

#define WIN_REFRESH 16 /* more or less 60 fps */
#define MILI 1e-3

namespace ep1 {

/// Represents a graphic window.
class Window {
  public:
    /// Reference-counting smart pointer for window objects.
    typedef std::tr1::shared_ptr<Window>        Ptr;
    /// Keyboard event handler.
    typedef std::tr1::function<void (int, int)> KeyEvent;
    /// Initializes the window.
    /** Even if created, a window is only displayed if it has been initialized
     ** before. */
    void init (double w, double h, double d);
    /// Gets the window's resolution ratio.
    /** @return double The window's resolution ratio. */
    double ratio () const { return 1.0*width_/height_; }
    /// Gets a reference to the window's camera.
    /** @return Camera& A reference to the window's camera. */
    Camera& camera() { return camera_; }
    /// Sets this window as the current one, if needed.
    void set_current ();
    /// Adds an event to a keyboard input.
    /** @param key    Character key associated to the given event.
     ** @param event  The event that happens when the given key is pressed. */
    void register_keyevent (unsigned char key, KeyEvent event);
    /// Adds an object to be drawn in the window.
    /** @param obj The object to be added. */
    void add_object (const Object::Ptr& obj);
    /// Defines the initial window size.
    static void init_size(int w, int h);
    /// Creates a new window object.
    /** @param caption - The window's caption. */
    static Ptr create (const std::string& caption) {
      Ptr created(new Window(caption));
      windows_[created->id_] = created;
      return created;
    }
  private:
    // Glut window's id.
    int                       id_;
    // Viewport width.
    int                       width_;
    // Viewport height.
    int                       height_;
    // Stop the timerfunc
    int                       stop_;
    // The window's camera into the scene.
    Camera                    camera_;
    // Objects to be drawn.
    std::vector<Object::Ptr>  objects_;
    // Indicates which mouse buttons are currently pressed.
    bool                      buttons_[3];
    // Last mouse position detected.
    std::pair<int,int>        mouse_pos_;
    // Keyboard events.
    std::vector<KeyEvent>     key_events_;
    // Initial window size.
    static int                init_width_, init_height_;
    // Reference base for all created windows.
    static std::tr1::unordered_map<int, Ptr> windows_;
    /// Constructor. See Window::create.
    explicit Window (const std::string& caption);
    /// Retrieves the current window.
    /** @return Window::Ptr Smart-pointer to the current window. */
    static Ptr current_window();
    /// Display callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void display ();
    /// Idle callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void timer_func (int value);
    /// Reshape callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void reshape (int w, int h);
    /// Mouse callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void mouse (int btn, int state, int x, int y);
    /// Mouse motion callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void motion (int x, int y);
    /// Keyboard callsback function for all windows.
    /** Signature follows GLUT specifications. */
    static void keyboard (unsigned char key, int x, int y);
};

} // namespace ep1

#endif

