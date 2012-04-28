
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "getglut.h"
#include "vec3D.h"
#include "window.h"

namespace ep1 {

using std::vector;
using std::tr1::unordered_map;

unordered_map<int, Window::Ptr> Window::windows_;

Window::Window (const std::string& caption) :
  perspective_(false),
  mouse_pos_(0, 0) {
  id_ = glutCreateWindow(caption.c_str());
  buttons_[0] = buttons_[1] = buttons_[2] = false;
}

static void init_opengl (Window& win) {
  int i;
  Vec3D b;
  
  glEnable(GL_DEPTH_TEST);
  win.set_ortho();

  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glLineWidth(2.0);
}

void Window::init (double w, double h, double d) {
  glutSetWindow(id_);
  glutDisplayFunc(display);
  glutTimerFunc(WIN_REFRESH, timer_func, 1);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  width_ = w;
  height_ = h;
  depth_ = d;
  init_opengl(*this);
  camera_pos_ = Vec3D(width_/2.0, -height_/2.0, depth_);
  camera_target_ = Vec3D(width_/2.0, -height_/2.0, -depth_/2.0);
}

void Window::add_object(const Object::Ptr& obj) {
  objects_.push_back(obj);
}

void Window::set_ortho () {
  perspective_ = false;
  set_current();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double max_dimension = std::max(std::max(width_, height_), depth_);
  glOrtho(
    -0.75*max_dimension, 0.75*max_dimension,
    -0.75*max_dimension, 0.75*max_dimension,
    -2.0*max_dimension, 10.0*max_dimension
  );
}

void Window::set_perspective () {
  perspective_ = true;
  set_current();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, depth_*0.1, depth_*10.0);
  glMatrixMode(GL_MODELVIEW);
}

void Window::toggle_projection () {
  if (perspective_)
    set_ortho();
  else
    set_perspective();
  glutPostRedisplay();
}

void Window::set_current () {
  if (glutGetWindow() != id_)
    glutSetWindow(id_);
}

Window::Ptr Window::current_window () {
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
  glutPostRedisplay();
}

void Window::mouse (int btn, int state, int x, int y) {
  Ptr win = current_window();
  bool new_state = (state == GLUT_DOWN);
  switch (btn) {
    case GLUT_LEFT_BUTTON:
      win->buttons_[0] = new_state;
      break;
    case GLUT_MIDDLE_BUTTON:
      win->buttons_[1] = new_state;
      break;
    case GLUT_RIGHT_BUTTON:
      win->buttons_[2] = new_state;
      break;
    default: break;
  }
  win->mouse_pos_ = std::make_pair(x, y);
  glutPostRedisplay();
}

void Window::motion (int x, int y) {
  Ptr win = current_window();
  Vec3D movement(
    x - win->mouse_pos_.first,
    -(y - win->mouse_pos_.second)
  );
  if (win->buttons_[0]) {
    win->camera_pos_ += movement*0.1;
    win->camera_target_ += movement*0.1;
  }
  else if (win->buttons_[2]) {
    Vec3D diff = win->camera_pos_ - win->camera_target_;
    win->camera_pos_ =
      win->camera_target_ + diff*(1.0/pow(2.0, movement.y()*0.1));
  }
  win->mouse_pos_ = std::make_pair(x, y);
  glutPostRedisplay();
}

void Window::keyboard (unsigned char key, int x, int y) {
  Ptr win = current_window();
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
            win->camera_target_.x(), win->camera_target_.y(),
            win->camera_target_.z(),
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

void Window::timer_func (int value) {
  Ptr win = current_window();
  vector<Object::Ptr>::iterator it;

  for (it = win->objects_.begin(); it != win->objects_.end(); ++it) (*it)->update();
  glutTimerFunc(WIN_REFRESH, timer_func, 1);
  glutPostRedisplay(); 
}

} // namespace ep1

