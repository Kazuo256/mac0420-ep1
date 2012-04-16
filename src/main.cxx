/*
 * Programa gerador do tri�ngulo de Sierpinski em 3d
 * utilizando GLUT e OpenGL
 *
 * MAC-420/5744 Computa��o Gr�fica
 *
 * Modifica��o 1: Utilizar z-buffer para remo��o de superf�cies escondidas
 * Modifica��o 2: Transla��o do baricentro para origem
 */

#include "ep1.h"

int main(int argc, char **argv) {
  ep1::init(argc, argv);
  ep1::run();
  return 0;
}

