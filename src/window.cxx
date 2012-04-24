
#include <cstdio>

#include "getglut.h"
#include "vec3D.h"
#include "window.h"

namespace ep1 {

using std::vector;
using std::tr1::unordered_map;

unordered_map<int, Window::Ptr> Window::windows_;

Window::Window (const std::string& caption) :
  camera_pos_(0.0, 0.0, 1.0),
  camera_target(0.0, 0.0, 0.0) {
  id_ = glutCreateWindow(caption.c_str());
}

/*
static void set_ortho () {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
}

static void set_perspective () {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 256.0);
}
*/

static void init_opengl (Window& win) {
  int i;
  Vec3D b;
  
  glEnable(GL_DEPTH_TEST);
  //win.set_ortho();
  win.set_perspective();

  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glLineWidth(2.0);
}

void Window::init () {
  glutSetWindow(id_);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  init_opengl(*this);
}

void Window::add_object(const Object::Ptr& obj) {
  objects_.push_back(obj);
}

void Window::set_ortho () {
  perspective_ = false;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
}

void Window::set_perspective () {
  perspective_ = true;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 0.5, 2.0);
  glMatrixMode(GL_MODELVIEW);
}

void Window::toggle_projection () {
  if (glutGetWindow() != id_)
    glutSetWindow(id_);
  if (perspective_)
    set_ortho();
  else
    set_perspective();
  glutPostRedisplay();
}

Window::Ptr Window::current_window() {
  return windows_[glutGetWindow()];
}

void Window::reshape(int w, int h) {
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

void Window::mouse (int btn, int state, int x, int y) {
   if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   	  ;
   if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
   	  ;
   	  
   glutPostRedisplay();
}

void Window::keyboard (unsigned char key, int x, int y) {
  Ptr win = current_window();
  if (!win) puts("BAD APPLE");
  switch (key) {
    case '\t':
      win->toggle_projection();
      break;
    default: break;
  }
}

void Window::display () {
  // Get the current window.
  Ptr win = current_window();
  // Prepare for drawing the scene.
  glMatrixMode(GL_MODELVIEW);   
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Position the camera.
  //glTranslated(0.0, 0.0, -2.0);
  gluLookAt(win->camera_pos_.x(), win->camera_pos_.y(), win->camera_pos_.z(),
            win->camera_target.x(), win->camera_target.y(), win->camera_target.z(),
            0.0, 1.0, 0.0);
  // Render all objects.
  vector<Object::Ptr>::iterator it;
  for (it = win->objects_.begin(); it != win->objects_.end(); ++it) {
    glPushMatrix();
    (*it)->render();
    glPopMatrix();
  }
  // Swap buffer to display result.
  glutSwapBuffers();
}

} // namespace ep1

