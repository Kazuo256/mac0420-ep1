/*
 * Programa gerador do triângulo de Sierpinski em 3d
 * utilizando GLUT e OpenGL
 *
 * MAC-420/5744 Computação Gráfica
 *
 * Modificação 1: Utilizar z-buffer para remoção de superfícies escondidas
 * Modificação 2: Translação do baricentro para origem
 */

/*#define MACOSX*/
#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include "window.h"

int main(int argc, char **argv) {
  ep1::Window::Ptr win;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  win = ep1::Window::create("Tarefa 3 - 3D Version");
  win->init();
  glutMainLoop();
}

