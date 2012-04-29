
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
static double     glyph_size, ratio;

void CreateCube (vector<ep1::Vec3D> infos) {
  int x, y, z, nX, nY, nZ, actual_pos;
  nX = infos[0].x();
  nY = infos[0].y();
  nZ = infos[0].z();
 
  dists = infos[1];
  max_vec = infos[2];
  min_vec = infos[2];
  // O enunciado diz para usar o comprimento, mas isso mesmo assim permite
  // que os vetores se aglutinem. Uma alternativa é usar o mínimo:
  // glyph_size = infos[1].min();
  glyph_size = infos[1].length();
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
        Vec3D force(
          infos[actual_pos].x(),
          -infos[actual_pos].y(),
          -infos[actual_pos].z()
        );
        field.set_force(x, y, z, force);

      }
}

static void draw_cone () {
  glPushMatrix();
  glTranslated(0.0, 0.0, -.5);
  glColor4d(0.0, 1.00, 0.00, 0.2);
  gluCylinder( gluNewQuadric(), 0.25, 0.0, 1.0, 6, 1);  
  glPopMatrix();
}

static void draw_sphere () {
  glColor4d(1.0, 0.00, 0.00, 0.7);
  gluSphere( gluNewQuadric(), dists.min()/2.0, 6, 6);  
}

Vec3D transform_to_field (Vec3D position) {
  Vec3D ret(position.x(), -position.y(), -position.z()); 
  return ret;
} 

double calc_delta (double actual_pos, double vertex) {
  double delta;

  delta = abs(vertex - actual_pos);
  
  return delta;
}

Vec3D trilinear_interpolation (Vec3D actual_pos) {
  Vec3D brn, f00, f01, f10, f11, f0, f1, aux; // brn = bottom_right_near 
  double delta;

  brn = actual_pos.vec_floor();
  aux = brn;
  aux.set_x(aux.x()+1.0);
  delta = calc_delta(actual_pos.x(), brn.x());
   
  f01 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  
  brn.set_y(brn.y()+1.0);
  aux.set_y(aux.y()+1.0);
  
  f00 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  
  brn.set_z(brn.z()+1.0); 
  aux.set_z(aux.z()+1.0);
  
  f10 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  
  brn.set_y(brn.y()-1.0);
  aux.set_y(aux.y()-1.0);
  
  f11 = field.force(brn)*(1-delta)+field.force(aux)*delta;
  
  delta = calc_delta(actual_pos.y(), brn.y());
  
  f1 = f01*(1-delta)+f00*delta;
  f0 = f10*delta+f11*(1-delta);

  delta = calc_delta(actual_pos.z(), brn.z());
  
  return f1*delta+f0*(1-delta);
}

void calc_new_delta (Vec3D& delta, Vec3D pos) {
  Vec3D final_pos;

  final_pos = delta+pos;
  if (final_pos.x() > field.width()*dists.x() || final_pos.x() < 0.0) 
    delta.set_x(0.0);
  if (-final_pos.y() > field.height()*dists.y() || -final_pos.y() < 0.0) 
    delta.set_y(0.0);
  if (-final_pos.z() > field.depth()*dists.z() || -final_pos.z() < 0.0) 
    delta.set_z(0.0);

}

static void dummy (Object& cone) {}

static void update_sphere (Object& sphere) {
  Vec3D delta_pos, pos_field;
  pos_field = transform_to_field(sphere.get_position());
  delta_pos = trilinear_interpolation(pos_field);
  delta_pos = delta_pos*(WIN_REFRESH*MILI*10);
  calc_new_delta(delta_pos, sphere.get_position());
  sphere.add_in_position(delta_pos);
}

static void add_cones (const Window::Ptr& win, const Vec3D& dist,
                       const Vec3D& numbers) {
  int x, y, z;
 
  for (z = 0; z < numbers.z(); z++ )
    for (y = 0; y < numbers.y(); y++)
      for (x = 0; x < numbers.x(); x++) {
        Vec3D position(dist.x()*x, -1.0*dist.y()*y, -1.0*dist.z()*z);
        Vec3D size(1.0, 1.0, field.force(x,y,z).length()*glyph_size/max_vec.length());
        Vec3D rotation =
          Vec3D::dir(transform_to_field(field.force(x,y,z))); 
        win->add_object(Object::create(Object::Renderer(draw_cone), 
                                       Object::Updater(dummy), 
                                       position, 
                                       size*ratio, 
                                       rotation,
                                       0));
      }
} 

static void add_sphere (const Window::Ptr& win, const Vec3D& dist, const Vec3D& numbers) {
  int x, y, z;
 
  for (z = 0; z < numbers.z(); z++ )
    for (y = 0; y < numbers.y(); y++)
      for (x = 0; x < numbers.x(); x++) {
        Vec3D position(dist.x()*x, -dist.y()*y, -dist.z()*z);
        Vec3D size(1, 1, 1);
        Vec3D rotation;
        win->add_object(Object::create(Object::Renderer(draw_sphere), 
                                       Object::Updater(update_sphere),  
                                       position, 
                                       size*ratio, 
                                       rotation,
                                       1));
      }
}

void init (int argc, char **argv) {
  vector<Vec3D> infos;
  
    
  Window::Ptr win;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
  glutInitWindowSize(500, 500);
  win = Window::create("MAC0420 - EP1");
  ratio = 1;
  if (argc == 3) {
    ratio = atof(argv[2]);
    if (ratio == 0) {
      printf("O programa recebe um ratio como terceiro parametro. Iniciando com ratio = 1.\n");
      ratio = 1;
    }
  }
  if (argc < 2) {
    printf("O programa recebe o nome de um arquivo como entrada padrão.\n");
    exit(0);
  }
  else {
    infos = utils::LoadForceFieldInfo(argv[1]);
    //info_cube = cube(infos[0].z(), matrix(infos[0].y(), vector<Vec3D>(infos[0].x())));
    field = ForceField(infos[0].x(), infos[0].y(), infos[0].z());
    CreateCube(infos);
    win->init(infos[0].x(), infos[0].y(), infos[0].z());
    win->camera().enframe(Vec3D(
      (infos[0].x()-1)*infos[1].x()/2.0,
      -(infos[0].y()-1)*infos[1].y()/2.0,
      -(infos[0].z()-1)*infos[1].z()/2.0
    ));
    add_cones(win, infos[1], infos[0]);
    add_sphere(win, infos[1], infos[0]);
  }
}

void run () {
  glutMainLoop();
}

}


