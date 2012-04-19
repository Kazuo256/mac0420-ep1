
#ifndef EP1_EP1_H_
#define EP1_EP1_H_

namespace ep1 {

/// Initializes the program.
/** @param argc Frist parameter from main.
 ** @param argv Second parameter from main.
 ** First arguments are for GLUT. The first non-GLUT argument should be the name
 ** of the input file from where the force field will be read. */
void init (int argc, char **argv);

/// Runs the program.
void run ();

} // namespace ep1

#endif

