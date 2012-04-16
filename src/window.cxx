
#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "window.h"

namespace ep1 {

using std::map;

map<int, Window*> Window::windows_;

Window::Window (const std::string& caption) {
  id_ = glutCreateWindow(caption.c_str());
}

void Window::init () {
  windows_[id_] = this;
  glutSetWindow(id_);
}

} // namespace ep1

