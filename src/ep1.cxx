
#include <cmath>

#include "getglut.h"
#include "simulation.h"
#include "window.h"
#include "utils.h"
#include "forcefield.h"

namespace ep1 {

using std::vector;

Simulation::Ptr simul;

void init (int argc, char **argv) {
  double        ratio = 1.0;
  vector<Vec3D> infos;
  glutInit(&argc, argv);
  if (argc >= 3) {
    ratio = atof(argv[2]);
    if (ratio == 0) {
      puts("O programa recebe um ratio como terceiro parametro. Iniciando com "
           "ratio = 1.");
      ratio = 1;
    }
  }
  if (argc < 2) {
    puts("O programa recebe o nome de um arquivo do qual carregar as "
         "informações da simulação.\n");
    exit(EXIT_FAILURE);
  }
  else {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
    Window::init_size(500, 500);
    Window::Ptr win = Window::create("MAC0420 - EP1");
    simul = Simulation::create(win, ratio);
    simul->init(argv[1]);
  }
}

void run () {
  glutMainLoop();
}

}


