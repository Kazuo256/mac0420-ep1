/*
 * Programa gerador do triângulo de Sierpinski em 3d
 * utilizando GLUT e OpenGL
 *
 * MAC-420/5744 Computação Gráfica
 *
 * Modificação 1: Utilizar z-buffer para remoção de superfícies escondidas
 * Modificação 2: Translação do baricentro para origem
 */

#include "ep1.h"

int main(int argc, char **argv) {
  ep1::init(argc, argv);
  ep1::run();
  return 0;
}

