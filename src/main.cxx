/*
 * Programa gerador do tri�ngulo de Sierpinski em 3d
 * utilizando GLUT e OpenGL
 *
 * MAC-420/5744 Computa��o Gr�fica
 *
 * Modifica��o 1: Utilizar z-buffer para remo��o de superf�cies escondidas
 * Modifica��o 2: Transla��o do baricentro para origem
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

