
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
  nX = infos[0].x();
  nY = infos[0].y();
  nZ = infos[0].z();

  for (z = 0; z < nZ; z++)
    for (y = 0; y < nY; y++) 
      for (x = 0; x < nX; x++)
        info_cube[z][y][x] = infos[z*nY*nX+y*nX+x+2];

}

static void draw () {
  glColor3d(1.0, 1.0, 1.0);
  glutWireCube(.5);
}

void init (int argc, char **argv) {
  vector<Vec3D> infos;
  Vec3D teste(1.0, 1.0, 1.0);

  ep1::Vec3D::dir(teste);
  
  if (argc < 2) printf("NOME DO ARQUIVO DEUSES DO CAOS\n");
  else {
    infos = utils::LoadForceFieldInfo(argv[1]);
    info_cube = cube(infos[0].z(), matrix(infos[0].y(), vector<Vec3D>(infos[0].x())));
    CreateCube(infos);
  }  
  Window::Ptr win;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  win = Window::create("MAC0420 - EP1");
  win->init();
  win->add_object(Object::create(Object::Renderer(draw)));
}

void run () {
  glutMainLoop();
}

}


