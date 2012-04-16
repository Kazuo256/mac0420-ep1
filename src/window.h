
#ifndef EP1_WINDOW_H_
#define EP1_WINDOW_H_

#include <string>
#include <tr1/unordered_map>
#include <tr1/memory>

namespace ep1 {

/** Represents a graphic window. */
class Window {
  public:
    typedef std::tr1::shared_ptr<Window> Ptr;
    /** Destructor. */
    ~Window () {}
    /** Initializes the window.
     ** Even if created, a window is only displayed if it has been initialized
     ** before. */
    void init ();
    /** Creates a new window object.
     ** @param caption - The window's caption. */
    static Ptr create(const std::string& caption) {
      Ptr created(new Window(caption));
      windows_[created->id_] = created;
      return created;
    }
  private:
    /** Glut window's id. */
    int id_;
    /** Reference base for all created windows. */
    static std::tr1::unordered_map<int, Ptr> windows_;
    /** Constructor.
     ** @param caption - The window's caption. */
    explicit Window (const std::string& caption);
    /** Retrieves the current window. */
    static Ptr current_window();
    /** Display callback function for all windows. */
    static void display ();
    /** Reshape callback function for all windows. */
    static void reshape (int w, int h);
    /** Mouse callback function for all windows. */
    static void mouse (int btn, int state, int x, int y);
};

} // namespace ep1

#endif

