
#include "getglut.h"
#include "window.h"
#include "utils.h"

namespace ep1 {

void init (int argc, char **argv) {
  std::vector<ep1::Vec3D> infos;
 
  if (argc < 2) printf("NOME DO ARQUIVO DEUSES DO CAOS\n");
  else {
    infos = utils::LoadForceFieldInfo(argv[1]);
  }
  Window::Ptr win;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  win = Window::create("Tarefa 3 - 3D Version");
  win->init();
}

void run () {
  glutMainLoop();
}

}


