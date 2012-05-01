
#include <cmath>

#include "getglut.h"
#include "simulation.h"
#include "window.h"
#include "utils.h"
#include "forcefield.h"

namespace ep1 {

using std::vector;

/// Our simulation object.
static Simulation::Ptr simul;

void init (int argc, char **argv) {
  double ratio = 1.0;
  // Init GLUT, also capturing glut-intended arguments.
  glutInit(&argc, argv);
  // Check non-glut arguments.
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
    // Everythin OK, let's do this!
    // Init GLUT.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
    // Define default initial window size.
    Window::init_size(500, 500);
    // Create a window.
    Window::Ptr win = Window::create("MAC0420 - EP1");
    // Create a simulation with that window.
    simul = Simulation::create(win, ratio);
    // Start it.
    simul->init(argv[1]);
  }
}

void run () {
  // Leave it to GLUT.
  glutMainLoop();
}

}


