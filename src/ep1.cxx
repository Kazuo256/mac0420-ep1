
#include "getglut.h"
#include "window.h"

namespace ep1 {

void init (int argc, char **argv) {
  ep1::Window::Ptr win;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  win = ep1::Window::create("Tarefa 3 - 3D Version");
  win->init();
}

void run () {
  glutMainLoop();
}

}


