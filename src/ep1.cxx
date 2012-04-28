
#include <cmath>

#include "getglut.h"
#include "window.h"
#include "utils.h"
#include "forcefield.h"

namespace ep1 {

using std::vector;

typedef vector< vector< vector< Vec3D > > > cube;
typedef vector< vector< Vec3D > > matrix;

//static cube info_cube;
static ForceField field;
static Vec3D      max_vec, min_vec, dists;
static double     glyph_size;

void CreateCube (vector<ep1::Vec3D> infos) {
  int x, y, z, nX, nY, nZ, actual_pos;
  nX = infos[0].x();
  nY = infos[0].y();
  nZ = infos[0].z();
 
  dists = infos[1];
  max_vec = infos[2];
  min_vec = infos[2];
  glyph_size = sqrt(infos[1]*infos[1]);
  for (z = 0; z < nZ; z++)
    for (y = 0; y < nY; y++) 
      for (x = 0; x < nX; x++) {
        /*  Actual_pos = The real position that will represent
            the vector we want in infos.*/ 
        actual_pos = z*nY*nX+y*nX+x+2;
        if (infos[actual_pos].length() > max_vec.length())
          max_vec = infos[actual_pos];
        else if (infos[actual_pos].length() < min_vec.length())
          min_vec = infos[actual_pos];
 
        //info_cube[z][y][x] = infos[actual_pos];
        field.set_force(x, y, z, infos[actual_pos]);

      }
}

static void draw () {
  glColor3d(1.0, 1.0, 1.0);
  glutWireCube(.5);
}

static void draw_cone () {
  glColor3d(1.0, 0.50, 0.50);
  glBegin(GL_TRIANGLES);
    glVertex3d(0.0, 0.25, 0.0);
    glVertex3d(0.0, -0.25, 0.0);
    glVertex3d(0.0, 0.0, dists.max());
  glEnd();
  //glutSolidCone(0.25, dists.max(), 10, 10);
  //gluCylinder( gluNewQuadric(), 0.25, 0.0, 1.0, 10, 10);  
}

static void draw_sphere () {
  glColor3d(1.0, 1.00, 1.00);
  gluSphere( gluNewQuadric(), dists.min()/2.0, 10, 10);  
}

Vec3D transform (Vec3D position) {
  Vec3D ret(position.x(), -position.y(), -position.z()); 
  return ret;
} 

double calc_delta (double actual_pos, double vertex) {
  double delta;

  delta = actual_pos - vertex;
  
  return delta;
}

Vec3D calc_delta_pos (Vec3D actual_pos) {
  Vec3D brn, f00, f01, f10, f11, f0, f1, aux; // brt = bottom_right_near 
  double delta;

  brn = actual_pos.vec_floor();
  aux = brn;
  aux.set_x(aux.x()+1);
  delta = calc_delta(actual_pos.x(), brn.x());
   
  f01 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  brn.set_y(brn.y()+1);
  aux.set_y(aux.y()+1);
  f00 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  brn.set_z(brn.z()+1); 
  aux.set_z(aux.z()+1);
  f10 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  brn.set_y(brn.y()-1);
  aux.set_y(aux.y()-1);
  f11 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  
  delta = calc_delta(actual_pos.y(), brn.y());
  f1 = f01*(1-delta)+f11*delta;
  f0 = f10*(1-delta)+f00*delta;

  delta = calc_delta(actual_pos.z(), brn.z());

  return f1*(1-delta)+f0*delta;
}

static void dummy (Object& cone) {}

static void update_sphere (Object& sphere) {
  Vec3D delta_pos, pos;
  pos = transform(sphere.get_position());
  delta_pos = calc_delta_pos(pos);
  sphere.add_in_position(delta_pos);
}

static void add_cones (const Window::Ptr& win, const Vec3D& dist, const Vec3D& numbers) {
  int x, y, z;
 
  for (z = 0; z < numbers.z(); z++ )
    for (y = 0; y < numbers.y(); y++)
      for (x = 0; x < numbers.x(); x++) {
        Vec3D position(dist.x()*x, -1.0*dist.y()*y, -1.0*dist.z()*z);
        Vec3D size(1.0, 1.0, field.force(x,y,z).length()*glyph_size/max_vec.length());
        Vec3D rotation = Vec3D::dir(field.force(x,y,z)); 
        win->add_object(Object::create(Object::Renderer(draw_cone), 
                                       Object::Updater(dummy), 
                                       position, 
                                       size, 
                                       rotation));
      }
} 

static void add_sphere (const Window::Ptr& win, const Vec3D& dist, const Vec3D& numbers) {
  int x, y, z;
 
  for (z = 0; z < numbers.z(); z++ )
    for (y = 0; y < numbers.y(); y++)
      for (x = 0; x < numbers.x(); x++) {
        Vec3D position(dist.x()*x, -1.0*dist.y()*y, -1.0*dist.z()*z);
        Vec3D size(1, 1, 1);
        Vec3D rotation;
        win->add_object(Object::create(Object::Renderer(draw_sphere), 
                                       Object::Updater(update_sphere),  
                                       position, 
                                       size, 
                                       rotation));
      }
}

void init (int argc, char **argv) {
  vector<Vec3D> infos;
  
    
  Window::Ptr win;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  win = Window::create("MAC0420 - EP1");
  if (argc < 2) printf("NOME DO ARQUIVO DEUSES DO CAOS\n");
  else {
    infos = utils::LoadForceFieldInfo(argv[1]);
    //info_cube = cube(infos[0].z(), matrix(infos[0].y(), vector<Vec3D>(infos[0].x())));
    field = ForceField(infos[0].x(), infos[0].y(), infos[0].z());
    CreateCube(infos);
    win->init(infos[0].x(), infos[0].y(), infos[0].z());
    win->add_object(Object::create(Object::Renderer(draw), Object::Updater(dummy)));
    add_cones(win, infos[1], infos[0]);
    add_sphere(win, infos[1], infos[0]);
  }
}

void run () {
  glutMainLoop();
}

}


