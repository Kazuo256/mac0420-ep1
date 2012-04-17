
#include <cstdio>

#include "getglut.h"
#include "vec3D.h"
#include "object.h"
#include "window.h"

namespace ep1 {

using std::tr1::unordered_map;

/* triângulo inicial */
static Vec3D v[4] = {
  Vec3D(-0.5, 0.0, 0.0),
  Vec3D(0.5, 0.0, 0.0),
  Vec3D(0.0, 0.866, 0.5),
  Vec3D(0.0, 0.288, 0.866)
};
   
/* número de subdivisões */                   
int n;

unordered_map<int, Window::Ptr> Window::windows_;

Window::Window (const std::string& caption) {
  id_ = glutCreateWindow(caption.c_str());
}

static void init_opengl()
{
    int i;
    Vec3D b;
    
    n = 0;

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    
    /* calcular o baricentro de v1v2v3v4 */
    b = (v[0] + v[1] + v[2] + v[3])/4.0;
//    for (i=0; i<3; i++)
//        b[i] = (v[0][i] + v[1][i] + v[2][i] + v[3][i]) / 4;
 
    glMatrixMode(GL_MODELVIEW);   
    glLoadIdentity();
    glTranslated(-b.x(),-b.y(),-b.z());
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0,0.0,0.0);
}

void Window::init () {
  glutSetWindow(id_);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  init_opengl();
}

Window::Ptr Window::current_window() {
  return windows_[glutGetWindow()];
}

void Window::reshape(int w, int h)
{
   int x = 0, y = 0;
   if (w > h) {
         x = (w - h) / 2;
         w = h;
   } else if (w < h) {
         y = (h - w) / 2; 
         h = w;
   }
   
   glViewport((GLint)x, (GLint)y, (GLint)w, (GLint)h); 
}

void Window::mouse(int btn, int state, int x, int y)
{
   if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   	  n++;
   if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
   	  n > 0 ? n-- : n;
   	  
   glutPostRedisplay();
}

/* desenha um triângulo */
static void triangulo(const Vec3D& v1,
                      const Vec3D& v2,
                      const Vec3D& v3) {
  /* desenha um triângulo */
  printf("hey %lf %lf %lf.\n", v1.x(), v1.y(), v1.z());
  printf("hey %lf %lf %lf.\n", v2.x(), v2.y(), v2.z());
  printf("hey %lf %lf %lf.\n", v3.x(), v3.y(), v3.z());
  glVertex3dv(v1.val()); 
  glVertex3dv(v2.val());
  glVertex3dv(v3.val());
}

/* subdivide triângulo */
static void divide_triangulo(const Vec3D& v1,
                             const Vec3D& v2,
                             const Vec3D& v3,
                             int n) {
  int j;
  Vec3D v12, v23, v13;
  if (n > 0) {
    v12 = (v1+v2)/2.0;
    v23 = (v2+v3)/2.0;
    v13 = (v1+v3)/2.0;
//    for(j=0; j<3; j++) v12[j]=(v1[j]+v2[j])/2;
//    for(j=0; j<3; j++) v23[j]=(v2[j]+v3[j])/2;
//    for(j=0; j<3; j++) v13[j]=(v1[j]+v3[j])/2;
    divide_triangulo(v1, v12, v13, n-1);
    divide_triangulo(v12, v2, v23, n-1);
    divide_triangulo(v13, v23, v3, n-1);
  }
  /* ao final da recursão, desenha triângulo */
  else(triangulo(v1, v2, v3));
}

static void tetraedro(int n)
{
    glColor3f(1.0,0.0,0.0);
    divide_triangulo(v[0], v[3], v[2], n);
    glColor3f(0.0,1.0,0.0);
    divide_triangulo(v[3], v[1], v[2], n);
    glColor3f(0.0,0.0,1.0);
    divide_triangulo(v[0], v[1], v[3], n);
    glColor3f(0.0,0.0,0.0);
    divide_triangulo(v[0], v[1], v[2], n);
}

static void draw () {
  puts("DRAW");
  glutWireCube(0.1);
}

void Window::display() {   
  Object obj = Object(
    Object::Renderer(draw),
    Vec3D(0.5, 0.5, 0.0),
    Vec3D(1.0, 1.0, 1.0),
    Vec3D::ypr(0.0, 0.0, 45.0)
  );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  obj.render();
  //glBegin(GL_TRIANGLES);
  //  tetraedro(n);
  //glEnd();        
  glutSwapBuffers();
}

} // namespace ep1

