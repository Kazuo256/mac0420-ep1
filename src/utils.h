
#ifndef EP1_UTILS_H_
#define EP1_UTILS_H_

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

#include "vec3D.h"

#define BUFFER_SIZE 256


namespace ep1 {

namespace utils {

/// Loads simulation information from the given file.
/** The resulting vector may be used by the ForceField::load method.
 ** @param file_name Filepath to the file containing simulation information in
 **                  format specified at <b>EP1-2012.pdf</b>.
 ** @return std::vector<ep1::Vec3D> Array of vectors representing the simulation
 **                                 information. */
std::vector<Vec3D> LoadForceFieldInfo (const std::string& file_name);

}

}
#endif
