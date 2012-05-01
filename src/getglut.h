////////////////////////////////////////////////////////////////////////////////
/// This file is used to include GLUT and OpenGL headers.
/** To use it in MACOSX computers, just uncomment the obvious line. */

/*#define MACOSX*/
#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

