
#include <cstdio>

#include "getglut.h"
#include "vec3D.h"
#include "window.h"

namespace ep1 {

using std::vector;
using std::tr1::unordered_map;

unordered_map<int, Window::Ptr> Window::windows_;

Window::Window (const std::string& caption) {
  id_ = glutCreateWindow(caption.c_str());
}

static void init_opengl()
{
    int i;
    Vec3D b;
    
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
 
    glMatrixMode(GL_MODELVIEW);   
    glLoadIdentity();
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0,1.0,1.0);
}

void Window::init () {
  glutSetWindow(id_);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  init_opengl();
}

void Window::add_object(const Object::Ptr& obj) {
  objects_.push_back(obj);
}

Window::Ptr Window::current_window() {
  return windows_[glutGetWindow()];
}

void Window::reshape(int w, int h)
{
   int x = 0, y = 0;
   if (w > h) {
         x = (w - h) / 2;
         w = h;
   } else if (w < h) {
         y = (h - w) / 2; 
         h = w;
   }
   
   glViewport((GLint)x, (GLint)y, (GLint)w, (GLint)h); 
}

void Window::mouse(int btn, int state, int x, int y)
{
   if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   	  ;
   if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
   	  ;
   	  
   glutPostRedisplay();
}

void Window::display() {
  Ptr win = current_window();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  vector<Object::Ptr>::iterator it;
  for (it = win->objects_.begin(); it != win->objects_.end(); ++it)
    (*it)->render();
  glutSwapBuffers();
}

} // namespace ep1

