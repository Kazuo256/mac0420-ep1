
/*#define MACOSX*/
#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "window.h"

namespace ep1 {

using std::tr1::unordered_map;

/* triângulo inicial */
static GLfloat v[4][3] = {
  {-0.5, 0, 0},
  {0.5, 0, 0},
  {0, 0.866, 0.5},
  {0, 0.288, 0.866}
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
    GLfloat b[3];
    
    n = 0;

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    
    /* calcular o baricentro de v1v2v3v4 */
    for (i=0; i<3; i++)
        b[i] = (v[0][i] + v[1][i] + v[2][i] + v[3][i]) / 4;
 
    glMatrixMode(GL_MODELVIEW);   
    glLoadIdentity();
    glTranslatef(-b[0],-b[1],-b[2]);
    
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
static void triangulo(GLfloat *v1, GLfloat *v2, GLfloat *v3)
{
     /* desenha um triângulo */
     glVertex3fv(v1); 
     glVertex3fv(v2);  
     glVertex3fv(v3);
}

/* subdivide triângulo */
static void divide_triangulo(GLfloat *v1, GLfloat *v2, GLfloat *v3, int n)
{
    int j;
    GLfloat v12[3], v23[3], v13[3];
    if (n > 0)
    {
        for(j=0; j<3; j++) v12[j]=(v1[j]+v2[j])/2;
        for(j=0; j<3; j++) v23[j]=(v2[j]+v3[j])/2;
        for(j=0; j<3; j++) v13[j]=(v1[j]+v3[j])/2;
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

void Window::display()
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
       tetraedro(n);
    glEnd();        
    glFlush();
}

} // namespace ep1

