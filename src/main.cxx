
#include <cstdlib>

#include "ep1.h"

int main(int argc, char **argv) {
  // Initialize.
  ep1::init(argc, argv);
  // Run.
  ep1::run();
  // Never reaches here.
  return EXIT_SUCCESS;
}

