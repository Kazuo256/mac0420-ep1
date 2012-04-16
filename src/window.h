
#ifndef EP1_WINDOW_H_
#define EP1_WINDOW_H_

#include <string>
#include <map>

namespace ep1 {

/** Represents a graphic window. */
class Window {
  public:
    /** Constructor.
     ** @param caption - The window's caption. */
    explicit Window (const std::string& caption);
    /** Destructor. */
    ~Window () {}
    /** Initializes the window.
     ** Even if created, a window is only displayed if it has been initialized
     ** before. */
    void init ();
  private:
    /** Glut window's id. */
    int id_;
    /** Reference base for all created and initialized windows. */
    static std::map<int, Window*> windows_;
    /** Display callback function for all windows. */
    static void display ();
    /** Reshape callback function for all windows. */
    static void reshape (int w, int h);
    /** Mouse callback function for all windows. */
    static void mouse (int btn, int state, int x, int y);
};

} // namespace ep1

#endif

