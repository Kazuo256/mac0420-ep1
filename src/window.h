
#ifndef EP1_WINDOW_H_
#define EP1_WINDOW_H_

#include <string>
#include <map>

namespace ep1 {

class Window {
  public:
    explicit Window (const std::string& caption);
    ~Window () {}
    void init ();
  private:
    int id_;
    static std::map<int, Window*> windows_;
    static void display ();
    static void reshape (int w, int h);
    static void mouse (int btn, int state, int x, int y);
};

} // namespace ep1

#endif

