
cmake_minimum_required (VERSION 2.8)

project (ep1 CXX C)
include_directories (src)

find_package(OpenGL REQUIRED)
if (${OPENGL_FOUND})
  include_directories (${OPENGL_INCLUDE_DIR})
else (${OPENGL_FOUND})
  message (FATAL_ERROR "OpenGL not found!")
endif (${OPENGL_FOUND})

find_package(GLUT REQUIRED)
if (${GLUT_FOUND})
  include_directories (${GLUT_INCLUDE_DIR})
else (${GLUT_FOUND})
  message (FATAL_ERROR "GLUT not found!")
endif (${GLUT_FOUND})

add_executable (ep1
  src/main.cxx
  src/ep1.cxx
  src/simulation.cxx
  src/window.cxx
  src/camera.cxx
  src/forcefield.cxx
  src/object.cxx
  src/vec3D.cxx
  src/utils.cxx
)
target_link_libraries (ep1 ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY})
set_target_properties (ep1 PROPERTIES COMPILE_FLAGS "-ansi -Wall -O2 -U_FORTIFY_SOURCE")

