
#include "getglut.h"
#include "window.h"
#include "utils.h"

namespace ep1 {

using std::vector;

typedef vector< vector< vector< Vec3D > > > cube;
typedef vector< vector< Vec3D > > matrix;

static cube info_cube;

void CreateCube (vector<ep1::Vec3D> infos) {
  int x, y, z, nX, nY, nZ;
  nX = infos[1].x();
  nY = infos[1].y();
  nZ = infos[1].z();

  for (z = 0; z < infos[0].z(); z++)
    for (y = 0; y < infos[0].y(); y++) 
      for (x = 0; x < infos[0].x(); x++)
        info_cube[z][y][x] = infos[z*nY*nX+y*nX+x];
}

void init (int argc, char **argv) {
  vector<Vec3D> infos;
 
  if (argc < 2) printf("NOME DO ARQUIVO DEUSES DO CAOS\n");
  else {
    infos = utils::LoadForceFieldInfo(argv[1]);
    info_cube = cube(infos[0].z(), matrix(infos[0].y(), vector<Vec3D>(infos[0].x())));
    CreateCube(infos);
    printf("V.x %f  ", info_cube[0][0][0].x());
    printf("V.y %f  ", info_cube[0][0][0].y());
    printf("V.z %f\n", info_cube[0][0][0].z());
    
    printf("V.x %f  ", info_cube[0][0][2].x());
    printf("V.y %f  ", info_cube[0][0][2].y());
    printf("V.z %f\n", info_cube[0][0][2].z());

    printf("V.x %f  ", info_cube[15][15][15].x());
    printf("V.y %f  ", info_cube[15][15][15].y());
    printf("V.z %f\n", info_cube[15][15][15].z());

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


