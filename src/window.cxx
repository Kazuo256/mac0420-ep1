
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

Window::Window (const std::string& caption, int width, int height) :
  width_ (width), height_(height), mouse_pos_(0, 0) {
  id_ = glutCreateWindow(caption.c_str());
  buttons_[0] = buttons_[1] = buttons_[2] = false;
}

static void init_opengl (Camera& camera, double ratio) {
  int i;
  Vec3D b;
  
  glEnable(GL_DEPTH_TEST);
  camera.set_ortho(ratio);

  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glLineWidth(2.0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::init (double w, double h, double d) {
  glutSetWindow(id_);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  camera_.set_view(w, h, d);
  init_opengl(camera_, ratio());
  camera_.enframe(Vec3D());
  glutTimerFunc(WIN_REFRESH, timer_func, 1);
}

void Window::add_object(const Object::Ptr& obj) {
  objects_.push_back(obj);
}

void Window::set_current () {
  if (glutGetWindow() != id_)
    glutSetWindow(id_);
}

Window::Ptr Window::current_window () {
  return windows_[glutGetWindow()];
}

void Window::reshape(int w, int h) {
  //int x = 0, y = 0;
  Ptr win = current_window();
  //if (w > h) {
  //  x = (w - h) / 2;
  //  w = h;
  //} else if (w < h) {
  //  y = (h - w) / 2; 
  //  h = w;
  //}
  win->width_ = w;
  win->height_ = h;
  win->camera_.adjust(win->ratio());
  glViewport((GLint)0, (GLint)0, (GLint)w, (GLint)h); 
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
  if (win->buttons_[0])
    win->camera_.move(movement);
  else if (win->buttons_[2])
    win->camera_.zoom(movement.y()*0.1);
  win->mouse_pos_ = std::make_pair(x, y);
  glutPostRedisplay();
}

void Window::keyboard (unsigned char key, int x, int y) {
  Ptr win = current_window();
  switch (key) {
    case '\t':
      win->camera_.toggle_projection(win->ratio());
      break;
    case 'q':
      win->stop_ = 1;
      break;
    case 'w':
      win->stop_ = 0;
      glutTimerFunc(WIN_REFRESH, timer_func, 1);
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
  // Use the camera.
  win->camera_.use();
  //gluLookAt(win->camera_pos_.x(), win->camera_pos_.y(), win->camera_pos_.z(),
  //          win->camera_target_.x(), win->camera_target_.y(),
  //          win->camera_target_.z(),
  //          0.0, 1.0, 0.0);
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
  if (win->stop_ == 0) glutTimerFunc(WIN_REFRESH, timer_func, 1);
  glutPostRedisplay(); 
}

} // namespace ep1

